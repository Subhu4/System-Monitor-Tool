#include "system_info.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <string>

// ---------- CPU INFO ----------
CPUInfo getCPUInfo() {
    static long prevIdle = 0, prevTotal = 0;

    FILE* file = fopen("/proc/stat", "r");
    if (!file) return {0.0};

    char buffer[1024];
    fgets(buffer, sizeof(buffer), file);
    fclose(file);

    long user, nice, system, idle, iowait, irq, softirq, steal;
    sscanf(buffer, "cpu  %ld %ld %ld %ld %ld %ld %ld %ld",
           &user, &nice, &system, &idle, &iowait, &irq, &softirq, &steal);

    long idleTime = idle + iowait;
    long nonIdle = user + nice + system + irq + softirq + steal;
    long total = idleTime + nonIdle;

    long totalDiff = total - prevTotal;
    long idleDiff = idleTime - prevIdle;

    double cpuUsage = 0.0;
    if (totalDiff != 0)
        cpuUsage = (double)(totalDiff - idleDiff) / totalDiff * 100.0;

    prevTotal = total;
    prevIdle = idleTime;

    return {cpuUsage};
}

// ---------- MEMORY INFO ----------
MemoryInfo getMemoryInfo() {
    FILE* file = fopen("/proc/meminfo", "r");
    if (!file) return {0, 0, 0.0};

    long total = 0, free = 0, buffers = 0, cached = 0;
    char key[128]; long value;
    char unit[32];

    while (fscanf(file, "%127s %ld %31s", key, &value, unit) == 3) {
        if (strcmp(key, "MemTotal:") == 0) total = value;
        else if (strcmp(key, "MemFree:") == 0) free = value;
        else if (strcmp(key, "Buffers:") == 0) buffers = value;
        else if (strcmp(key, "Cached:") == 0) cached = value;
    }
    fclose(file);

    long used = total - free - buffers - cached;
    double usedPercent = (total > 0) ? (double)used / total * 100.0 : 0.0;

    return {total, used, usedPercent};
}

// ---------- PROCESS LIST ----------
std::vector<ProcessInfo> getProcessList() {
    std::vector<ProcessInfo> processes;

    FILE* pipe = popen("ps -eo pid,comm,pcpu,pmem --no-headers", "r");
    if (!pipe) return processes;

    char line[512];
    while (fgets(line, sizeof(line), pipe)) {
        int pid;
        char name[128];
        double cpu, mem;
        if (sscanf(line, "%d %127s %lf %lf", &pid, name, &cpu, &mem) == 4) {
            processes.push_back({pid, std::string(name), cpu, mem});
        }
    }
    pclose(pipe);

    return processes;
}
