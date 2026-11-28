#include "../../include/algorithms.h"
#include <vector>
#include <queue>
#include <algorithm>
#include <stdexcept>
#include <cstddef>

using namespace std;

void roundRobin(vector<Process>& processes, int timeQuantum)
{
    if (timeQuantum <= 0)
    {
        throw invalid_argument("Time quantum must be positive.");
    }

    vector<size_t> order;

    for (size_t i = 0; i < processes.size(); i++)
    {
        if (processes[i].arrivalTime < 0 ||
            processes[i].burstTime <= 0)
        {
            throw invalid_argument("Invalid process information.");
        }

        processes[i].remainingTime = processes[i].burstTime;
        processes[i].completionTime = 0;
        processes[i].firstStartTime = -1;

        order.push_back(i);
    }

    stable_sort(order.begin(), order.end(),
        [&](size_t a, size_t b)
        {
            return processes[a].arrivalTime <
                   processes[b].arrivalTime;
        });

    queue<size_t> readyQueue;

    int currentTime = 0;
    size_t nextProcess = 0;

    while (nextProcess < order.size() ||
           !readyQueue.empty())
    {
        if (readyQueue.empty() &&
            nextProcess < order.size())
        {
            currentTime = max(currentTime,
                processes[order[nextProcess]].arrivalTime);
        }

        while (nextProcess < order.size() &&
               processes[order[nextProcess]].arrivalTime <= currentTime)
        {
            readyQueue.push(order[nextProcess]);
            nextProcess++;
        }

        size_t currentIndex = readyQueue.front();
        readyQueue.pop();

        Process& currentProcess = processes[currentIndex];

        if (currentProcess.firstStartTime == -1)
        {
            currentProcess.firstStartTime = currentTime;
        }

        int executionTime = min(timeQuantum,
                                currentProcess.remainingTime);

        currentProcess.remainingTime -= executionTime;
        currentTime += executionTime;

        while (nextProcess < order.size() &&
               processes[order[nextProcess]].arrivalTime <= currentTime)
        {
            readyQueue.push(order[nextProcess]);
            nextProcess++;
        }

        if (currentProcess.remainingTime > 0)
        {
            readyQueue.push(currentIndex);
        }
        else
        {
            currentProcess.completionTime = currentTime;
        }
    }
}