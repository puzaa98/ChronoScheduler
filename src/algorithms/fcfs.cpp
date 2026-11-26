#include <iostream>
#include <iomanip>
#include "../../include/algorithms.h"

using namespace std;

void calculateFCFS(vector<Process> processes) {
    int currentTime = 0;
    double totalWT = 0;
    double totalTAT = 0;

    cout << "\n--- [FCFS DECISION EXPLAINER LOG] ---" << endl;

    for (size_t i = 0; i < processes.size(); i++) {
        // Check for CPU Idle time
        if (currentTime < processes[i].arrivalTime) {
            cout << "CPU Idle from time " << currentTime << " to " << processes[i].arrivalTime << " (Waiting for P" << processes[i].id << ")." << endl;
            currentTime = processes[i].arrivalTime;
        }

        // Decision Explainer
        cout << "Time " << currentTime << ": CPU selected P" << processes[i].id 
             << " (Burst: " << processes[i].burstTime << "). Reason: First in queue." << endl;

        processes[i].completionTime = currentTime + processes[i].burstTime;
        processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
        processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;

        currentTime = processes[i].completionTime;

        totalWT += processes[i].waitingTime;
        totalTAT += processes[i].turnaroundTime;
    }

    // 1. Print the Table
    cout << "\n--- FCFS SCHEDULING RESULTS ---" << endl;
    cout << left << setw(10) << "Process" << setw(10) << "Arrival" << setw(10) << "Burst" 
         << setw(15) << "Completion" << setw(15) << "Turnaround" << setw(10) << "Waiting" << endl;

    for (const auto& p : processes) {
        cout << left << "P" << setw(9) << p.id << setw(10) << p.arrivalTime << setw(10) << p.burstTime 
             << setw(15) << p.completionTime << setw(15) << p.turnaroundTime << setw(10) << p.waitingTime << endl;
    }

    cout << "\nAverage Waiting Time: " << (totalWT / processes.size()) << endl;
    cout << "Average Turnaround Time: " << (totalTAT / processes.size()) << endl;

    // 2. Print the Text Gantt Chart
    cout << "\n--- GANTT CHART (FCFS) ---" << endl;
    cout << "0 ";
    for (const auto& p : processes) {
        cout << "|  P" << p.id << "  |";
    }
    cout << endl << "  ";
    int timeDisplay = 0;
    for (const auto& p : processes) {
        timeDisplay += p.burstTime; 
        cout << left << setw(7) << timeDisplay;
    }
    cout << endl;
}