#ifndef PCB_H
#define PCB_H

#include <string>

struct PCB
{
    int processID;
    std::string processName;
    std::string processStatus;
    int commandCounter;
    int cpuRegisters[8];
};

#endif