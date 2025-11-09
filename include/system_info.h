#pragma once
#include <string>
#include <vector>

struct CPUInfo {
    double usage = 0.0; // CPU usage in %
};

struct MemoryInfo {
    long total = 0;      // in KB
    long used = 0;       // in KB
    double usedPercent = 0.0;
};

struct ProcessInfo {
    int pid = 0;
    std::string name;
    double cpuPercent = 0.0;
    double memPercent = 0.0;
};

// Functions to fetch system information
CPUInfo getCPUInfo();
MemoryInfo getMemoryInfo();
std::vector<ProcessInfo> getProcessList();
