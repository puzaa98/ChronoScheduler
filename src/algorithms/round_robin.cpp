#include "../../include/algorithms.h"
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <stdexcept>
#include <cstddef>
#include <iomanip>

using namespace std;

vector<GanttBlock> rrGanttBlocks;

void roundRobin(vector<Process>& processes, int timeQuantum)
{
    rrGanttBlocks.clear();

    if (timeQuantum <= 0) throw invalid_argument("Time quantum must be positive.");

    vector<size_t> order;

    for (size_t i = 0; i < processes.size(); i++)
    {
        if (processes[i].arrivalTime < 0 || processes[i].burstTime <= 0)
            throw invalid_argument("Invalid process information.");

        processes[i].remainingTime = processes[i].burstTime;
        processes[i].completionTime = 0;
        processes[i].firstStartTime = -1;
        processes[i].startTime = 0;
        processes[i].responseTime = 0;
        order.push_back(i);
    }

    stable_sort(order.begin(), order.end(), [&](size_t a, size_t b) {
        return processes[a].arrivalTime < processes[b].arrivalTime;
    });

    queue<size_t> readyQueue;
    int currentTime = 0;
    size_t nextProcess = 0;
    
    cout << "\n--- [ROUND ROBIN DECISION EXPLAINER LOG] ---" << endl;

    while (nextProcess < order.size() || !readyQueue.empty())
    {
        if (readyQueue.empty() && nextProcess < order.size())
            currentTime = max(currentTime, processes[order[nextProcess]].arrivalTime);

        while (nextProcess < order.size() && processes[order[nextProcess]].arrivalTime <= currentTime)
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
            currentProcess.startTime = currentTime;
            // First time running => Response Time
            currentProcess.responseTime = currentTime - currentProcess.arrivalTime;
        }

        int executionTime = min(timeQuantum, currentProcess.remainingTime);
        
        GanttBlock block;
        block.pid = currentProcess.id;
        block.start = currentTime;
        block.end = currentTime + executionTime;
        rrGanttBlocks.push_back(block);

        cout << "Time " << currentTime << ": CPU selected P" << currentProcess.id 
             << " (Executing for " << executionTime << " units)." << endl;

        currentProcess.remainingTime -= executionTime;
        currentTime += executionTime;

        while (nextProcess < order.size() && processes[order[nextProcess]].arrivalTime <= currentTime)
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
            currentProcess.turnaroundTime = currentProcess.completionTime - currentProcess.arrivalTime;
            currentProcess.waitingTime = currentProcess.turnaroundTime - currentProcess.burstTime;
        }
    }

    // Print Results
    double totalWT = 0, totalTAT = 0, totalRT = 0;
    cout << "\n--- ROUND ROBIN SCHEDULING RESULTS ---" << endl;
    cout << left << setw(10) << "Process" << setw(10) << "Arrival" << setw(10) << "Burst" 
         << setw(15) << "Completion" << setw(15) << "Turnaround" << setw(10) << "Waiting" 
         << setw(10) << "Response" << endl;

    for (const auto& p : processes) {
        cout << left << "P" << setw(9) << p.id << setw(10) << p.arrivalTime << setw(10) << p.burstTime 
             << setw(15) << p.completionTime << setw(15) << p.turnaroundTime << setw(10) << p.waitingTime 
             << setw(10) << p.responseTime << endl;
        totalWT += p.waitingTime;
        totalTAT += p.turnaroundTime;
        totalRT += p.responseTime;
    }

    cout << "\nAverage Waiting Time: " << (totalWT / processes.size()) << endl;
    cout << "Average Turnaround Time: " << (totalTAT / processes.size()) << endl;
    cout << "Average Response Time: " << (totalRT / processes.size()) << endl;
}