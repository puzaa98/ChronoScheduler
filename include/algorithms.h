#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <vector>
#include "process.h"

void calculateFCFS(std::vector<Process>& processes);
void calculateSJF(std::vector<Process>& processes);
void roundRobin(std::vector<Process>& processes, int timeQuantum);

struct GanttBlock {
    int pid;
    int start;
    int end;
};

extern std::vector<GanttBlock> rrGanttBlocks;

#endif