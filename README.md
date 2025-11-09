# 🖥️ System Monitor Tool (C++)

A lightweight **real-time system monitoring tool** built in **C++**, similar to the Linux `top` command.  
It displays active processes, CPU usage, memory usage, and allows users to **sort processes** and **terminate them** directly from the interface.

---

## 🎯 Objective
To create a command-line based system monitor that utilizes **system calls** to fetch and display resource usage information in real time.

---

## ✨ Features

| Feature | Description |
|--------|-------------|
| 🧩 Process Monitoring | Displays running processes with their CPU and memory usage. |
| 🔄 Real-Time Updates | Automatically refreshes the data every few seconds. |
| 📊 Sorting Options | Sort processes based on CPU or memory consumption. |
| ❌ Kill Processes | Allows the user to terminate any process by PID. |
| 🎛️ Simple UI | Clean and easy-to-understand CLI layout. |

---

## 📅 Development Timeline

| Day | Task |
|----|------|
| **Day 1** | Designed UI layout and fetched system data using system calls. |
| **Day 2** | Displayed process list with CPU and memory usage. |
| **Day 3** | Implemented sorting functionality (CPU / Memory). |
| **Day 4** | Added option to kill processes using PID. |
| **Day 5** | Added automatic real-time refreshing of displayed data. |

---

## 🛠️ Tech Stack

- **Language:** C++
- **Platform:** Linux / Unix-based system
- **System APIs:** `/proc` filesystem, `sysinfo`, `kill()`, etc.

---

## 🚀 How to Run

1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/system-monitor-tool.git
   cd system-monitor-tool
   g++ -o system_monitor system_monitor.cpp


