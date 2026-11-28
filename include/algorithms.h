#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <vector>
#include "process.h"

// Notice the '&' here. It means "pass by reference" so the updated times are saved!
void calculateFCFS(std::vector<Process>& processes);
void calculateSJF(std::vector<Process>& processes);
#include "process.h"
#include <vector>

void roundRobin(std::vector<Process>& processes, int timeQuantum);

#endif