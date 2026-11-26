#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <vector>
#include "process.h"

// These are the function declarations that the GUI will call
void calculateFCFS(std::vector<Process> processes);
void calculateSJF(std::vector<Process> processes);

#endif