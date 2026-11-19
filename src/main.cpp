#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
};

void calculateSJF(vector<Process>& processes) {
    int currentTime = 0;
    int completed = 0;
    int n = processes.size();
    double totalWT = 0;
    double totalTAT = 0;
    
    // To keep track of which processes are finished
    vector<bool> isCompleted(n, false); 
    
    // To store the order of execution for the Gantt Chart
    vector<int> executionOrder;

    cout << "\n--- [DECISION EXPLAINER LOG] ---" << endl;

    while (completed != n) {
        int shortestIndex = -1;
        int minBurst = 999999;

        // Find the process with the shortest burst time among arrived processes
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && !isCompleted[i]) {
                if (processes[i].burstTime < minBurst) {
                    minBurst = processes[i].burstTime;
                    shortestIndex = i;
                }
                // Tie-breaker: If burst times are equal, pick the one that arrived first
                else if (processes[i].burstTime == minBurst) {
                    if (processes[i].arrivalTime < processes[shortestIndex].arrivalTime) {
                        shortestIndex = i;
                    }
                }
            }
        }

        // If no process has arrived yet, CPU is idle
        if (shortestIndex == -1) {
            currentTime++;
            continue;
        }

        int idx = shortestIndex;

        // Decision Explainer
        cout << "Time " << currentTime << ": CPU selected P" << processes[idx].id 
             << " (Burst: " << processes[idx].burstTime << "). Reason: Shortest burst time among available processes." << endl;

        // Calculate metrics
        processes[idx].completionTime = currentTime + processes[idx].burstTime;
        processes[idx].turnaroundTime = processes[idx].completionTime - processes[idx].arrivalTime;
        processes[idx].waitingTime = processes[idx].turnaroundTime - processes[idx].burstTime;

        totalWT += processes[idx].waitingTime;
        totalTAT += processes[idx].turnaroundTime;

        // Update time and mark as completed
        currentTime = processes[idx].completionTime;
        isCompleted[idx] = true;
        completed++;
        executionOrder.push_back(idx);
    }

    // 1. Print the Table
    cout << "\n--- SJF SCHEDULING RESULTS ---" << endl;
    cout << left << setw(10) << "Process" << setw(10) << "Arrival" << setw(10) << "Burst" 
         << setw(15) << "Completion" << setw(15) << "Turnaround" << setw(10) << "Waiting" << endl;

    for (const auto& p : processes) {
        cout << left << "P" << setw(9) << p.id << setw(10) << p.arrivalTime << setw(10) << p.burstTime 
             << setw(15) << p.completionTime << setw(15) << p.turnaroundTime << setw(10) << p.waitingTime << endl;
    }

    cout << "\nAverage Waiting Time: " << (totalWT / n) << endl;
    cout << "Average Turnaround Time: " << (totalTAT / n) << endl;

    // 2. Print the Gantt Chart
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

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        cout << "Enter Arrival Time for P" << i + 1 << ": ";
        cin >> processes[i].arrivalTime;
        cout << "Enter Burst Time for P" << i + 1 << ": ";
        cin >> processes[i].burstTime;
    }

    calculateSJF(processes);

    return 0;
}