🖥️ System Monitor Tool (C++)
📘 Overview

The System Monitor Tool is a terminal-based application built in C++, inspired by the Linux top command.
It displays real-time information about running system processes, CPU load, and memory usage.
This project helps users understand how system resources are managed, and how process monitoring works in an operating system environment.

🎯 Objectives

To design and implement a real-time system monitoring tool using C++.

To understand and utilize system calls in Linux/Ubuntu.

To display system processes dynamically, similar to the top command.

To implement process sorting, killing, and real-time updates.

To gain hands-on experience with C++ system programming and process management.

🧠 Abstract

The System Monitor Tool provides users with an interactive and continuously updating view of system processes and performance metrics.
Built with C++, it uses Linux system calls and file interfaces such as /proc/ to fetch data about CPU usage, RAM consumption, and active processes.
This tool is particularly useful for beginners in operating systems or system-level programming, offering insight into how OS monitoring utilities work internally.

By implementing process listing, sorting, and real-time refresh, the project mirrors functionalities of professional monitoring tools — enabling a deeper understanding of CPU scheduling, memory management, and process control.

⚙️ Features

✅ Displays a list of all active processes
✅ Shows CPU and memory usage per process
✅ Allows sorting by CPU or memory utilization
✅ Supports killing processes via PID
✅ Auto-refreshes data every few seconds for real-time updates
✅ Lightweight and runs directly in terminal

📅 Development Plan (Day-Wise Breakdown)
Day	Task	Description
Day 1	Design UI & Gather Data	Create terminal-based UI layout and collect system data using /proc and system calls.
Day 2	Display Process List	Fetch and show process name, PID, CPU, and memory usage.
Day 3	Add Sorting	Enable sorting processes by CPU or memory usage.
Day 4	Add Kill Process Feature	Implement process termination by PID input.
Day 5	Real-Time Updates	Refresh the data every few seconds dynamically.
🧩 Technologies Used

Language: C++

Platform: Ubuntu / Linux

Libraries Used:

<iostream>, <fstream>, <sstream>

<unistd.h> for process/system calls

<vector>, <algorithm> for sorting

Optional: ncurses for terminal UI

🖥️ Installation & Execution Guide
🔹 Step 1: Clone the Repository
git clone https://github.com/<your-username>/System-Monitor-Tool.git
cd System-Monitor-Tool

🔹 Step 2: Compile the Code
g++ system_monitor.cpp -o system_monitor

🔹 Step 3: Run the Program
./system_monitor

🧰 Output Snapshots

📸 (Paste your screenshots below this section)

Example:

Screenshot 1: Initial Process List

Screenshot 2: Sorting by CPU

Screenshot 3: Killing a Process

Screenshot 4: Real-time Update

🌐 API Integration (Optional)

You can extend this project by connecting to an API for fetching system statistics or remote monitoring.
Use libcurl and nlohmann-json to make HTTP requests and parse responses.

Example API call:

curl_easy_setopt(curl, CURLOPT_URL, "https://api.github.com/users/octocat");

🧩 Future Enhancements

Add graphical visualization using ncurses or Qt

Integrate remote system monitoring via API

Export process data to CSV or JSON

Add user authentication for multi-user environments

📄 Project Report

You can view the full project report (PDF) here:
👉 System Monitor Tool Report (PDF)

🧑‍💻 Author

Arupsa Sahoo
🎓 4th Year, ITER, SOA University
📫 GitHub: https://github.com/ArupsaSahoo

🏁 Conclusion

The System Monitor Tool successfully simulates a real-time process monitoring environment.
It enhances understanding of CPU scheduling, memory usage, and process management, bridging the gap between theoretical operating system concepts and practical implementation.
