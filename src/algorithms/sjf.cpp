#include <iostream>
#include <vector>
#include <iomanip>
#include "../../include/algorithms.h"

using namespace std;

void calculateSJF(vector<Process> processes) {
    int currentTime = 0;
    int completed = 0;
    int n = processes.size();
    double totalWT = 0;
    double totalTAT = 0;
    
    vector<bool> isCompleted(n, false); 
    vector<int> executionOrder;

    cout << "\n--- [SJF DECISION EXPLAINER LOG] ---" << endl;

    while (completed != n) {
        int shortestIndex = -1;
        int minBurst = 999999;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && !isCompleted[i]) {
                if (processes[i].burstTime < minBurst) {
                    minBurst = processes[i].burstTime;
                    shortestIndex = i;
                }
                else if (processes[i].burstTime == minBurst) {
                    if (processes[i].arrivalTime < processes[shortestIndex].arrivalTime) {
                        shortestIndex = i;
                    }
                }
            }
        }

        if (shortestIndex == -1) {
            currentTime++;
            continue;
        }

        int idx = shortestIndex;

        cout << "Time " << currentTime << ": CPU selected P" << processes[idx].id 
             << " (Burst: " << processes[idx].burstTime << "). Reason: Shortest burst time among available processes." << endl;

        processes[idx].completionTime = currentTime + processes[idx].burstTime;
        processes[idx].turnaroundTime = processes[idx].completionTime - processes[idx].arrivalTime;
        processes[idx].waitingTime = processes[idx].turnaroundTime - processes[idx].burstTime;

        totalWT += processes[idx].waitingTime;
        totalTAT += processes[idx].turnaroundTime;

        currentTime = processes[idx].completionTime;
        isCompleted[idx] = true;
        completed++;
        executionOrder.push_back(idx);
    }

    cout << "\n--- SJF SCHEDULING RESULTS ---" << endl;
    cout << left << setw(10) << "Process" << setw(10) << "Arrival" << setw(10) << "Burst" 
         << setw(15) << "Completion" << setw(15) << "Turnaround" << setw(10) << "Waiting" << endl;

    for (const auto& p : processes) {
        cout << left << "P" << setw(9) << p.id << setw(10) << p.arrivalTime << setw(10) << p.burstTime 
             << setw(15) << p.completionTime << setw(15) << p.turnaroundTime << setw(10) << p.waitingTime << endl;
    }

    cout << "\nAverage Waiting Time: " << (totalWT / n) << endl;
    cout << "Average Turnaround Time: " << (totalTAT / n) << endl;

    cout << "\n--- GANTT CHART (SJF) ---" << endl;
    cout << "0 ";
    for (int idx : executionOrder) {
        cout << "|  P" << processes[idx].id << "  |";
    }
    cout << endl << "  ";
    int timeDisplay = 0;
    for (int idx : executionOrder) {
        timeDisplay = processes[idx].completionTime;
        cout << left << setw(7) << timeDisplay;
    }
    cout << endl;
}