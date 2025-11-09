#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <unistd.h>
#include <pwd.h>
#include <dirent.h>
#include <ncurses.h>
#include <signal.h>
#include <chrono>
#include <thread>

using namespace std;

// ======================
// Structure for Process
// ======================
struct Process {
    int pid;
    string user;
    float cpuUsage;
    float memUsage;
    long rss;
    string command;
};

// ======================
// Function to get username from UID
// ======================
string getUserName(int uid) {
    struct passwd *pw = getpwuid(uid);
    return pw ? pw->pw_name : "unknown";
}

// ======================
// Function to get Memory Usage
// ======================
float getMemoryUsage() {
    ifstream meminfo("/proc/meminfo");
    string key;
    long totalMem = 0, freeMem = 0;
    while (meminfo >> key) {
        if (key == "MemTotal:") meminfo >> totalMem;
        else if (key == "MemAvailable:") meminfo >> freeMem;
    }
    return ((float)(totalMem - freeMem) / totalMem) * 100.0;
}

// ======================
// Function to get CPU Usage
// ======================
float getCPUUsage() {
    static long prevIdle = 0, prevTotal = 0;
    ifstream statFile("/proc/stat");
    string cpu;
    long user, nice, system, idle, iowait, irq, softirq, steal;
    statFile >> cpu >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal;

    long idleTime = idle + iowait;
    long totalTime = user + nice + system + idle + iowait + irq + softirq + steal;

    long diffIdle = idleTime - prevIdle;
    long diffTotal = totalTime - prevTotal;
    prevIdle = idleTime;
    prevTotal = totalTime;

    return (1.0 - ((float)diffIdle / diffTotal)) * 100.0;
}

// ======================
// Function to get Process List
// ======================
vector<Process> getProcesses() {
    vector<Process> processes;
    DIR *dir = opendir("/proc");
    if (!dir) return processes;

    struct dirent *entry;
    while ((entry = readdir(dir)) != nullptr) {
        if (!isdigit(entry->d_name[0])) continue;

        int pid = stoi(entry->d_name);
        string statPath = "/proc/" + string(entry->d_name) + "/stat";
        string statusPath = "/proc/" + string(entry->d_name) + "/status";
        string cmdPath = "/proc/" + string(entry->d_name) + "/cmdline";

        ifstream statFile(statPath);
        ifstream statusFile(statusPath);
        ifstream cmdFile(cmdPath);

        if (!statFile || !statusFile) continue;

        string cmd;
        getline(cmdFile, cmd);
        if (cmd.empty()) cmd = "[" + string(entry->d_name) + "]";

        string key;
        int uid = 0;
        long rss = 0;
        while (statusFile >> key) {
            if (key == "Uid:") statusFile >> uid;
            else if (key == "VmRSS:") statusFile >> rss;
        }

        Process p;
        p.pid = pid;
        p.user = getUserName(uid);
        p.cpuUsage = 0.0;
        p.memUsage = 0.0;
        p.rss = rss;
        p.command = cmd;

        processes.push_back(p);
    }

    closedir(dir);
    return processes;
}

// ======================
// Function to display UI
// ======================
void displayUI(vector<Process> &processes, float cpu, float mem, string sortBy) {
    clear();
    mvprintw(0, 0, "SimpleSysMon (q=quit  c=sort by CPU  m=sort by Memory  k=kill)");
    mvprintw(1, 0, "CPU Usage: %.2f%%   Memory Usage: %.2f%%   Sorting by: %s", cpu, mem, sortBy.c_str());
    mvprintw(2, 0, "-----------------------------------------------------------------------");
    mvprintw(3, 0, " PID   USER        %MEM    RSS(KB)   COMMAND");

    int row = 4;
    for (auto &p : processes) {
        mvprintw(row++, 0, " %-5d %-10s %5.2f   %-8ld   %.30s", p.pid, p.user.c_str(), p.memUsage, p.rss, p.command.c_str());
        if (row > LINES - 2) break; // prevent overflow
    }
    refresh();
}

// ======================
// MAIN FUNCTION
// ======================
int main() {
    initscr();
    noecho();
    cbreak();
    nodelay(stdscr, TRUE);

    string sortBy = "CPU";
    while (true) {
        float cpu = getCPUUsage();
        float mem = getMemoryUsage();
        vector<Process> processes = getProcesses();

        // Simulate sorting (we'll just use RSS as memory indicator)
        if (sortBy == "MEM")
            sort(processes.begin(), processes.end(), [](const Process &a, const Process &b) { return a.rss > b.rss; });
        else
            sort(processes.begin(), processes.end(), [](const Process &a, const Process &b) { return a.pid < b.pid; });

        displayUI(processes, cpu, mem, sortBy);

        char ch = getch();
        if (ch == 'q') break;
        if (ch == 'c') sortBy = "CPU";
        if (ch == 'm') sortBy = "MEM";
        if (ch == 'k') {
            echo();
            nodelay(stdscr, FALSE);
            int pidToKill;
            mvprintw(LINES - 2, 0, "Enter PID to kill: ");
            scanw("%d", &pidToKill);
            kill(pidToKill, SIGTERM);
            noecho();
            nodelay(stdscr, TRUE);
        }

        this_thread::sleep_for(chrono::seconds(2)); // refresh every 2s
    }

    endwin();
    return 0;
}
