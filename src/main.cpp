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

// ==========================================
// 1. FCFS ALGORITHM
// ==========================================
void calculateFCFS(vector<Process> processes) {
    int currentTime = 0;
    double totalWT = 0;
    double totalTAT = 0;

    cout << "\n--- [FCFS DECISION EXPLAINER LOG] ---" << endl;

    for (size_t i = 0; i < processes.size(); i++) {
        if (currentTime < processes[i].arrivalTime) {
            cout << "CPU Idle from time " << currentTime << " to " << processes[i].arrivalTime << endl;
            currentTime = processes[i].arrivalTime;
        }

        cout << "Time " << currentTime << ": CPU selected P" << processes[i].id 
             << " (Burst: " << processes[i].burstTime << "). Reason: First in queue." << endl;

        processes[i].completionTime = currentTime + processes[i].burstTime;
        processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
        processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;

        currentTime = processes[i].completionTime;
        totalWT += processes[i].waitingTime;
        totalTAT += processes[i].turnaroundTime;
    }

    cout << "\n--- FCFS SCHEDULING RESULTS ---" << endl;
    cout << left << setw(10) << "Process" << setw(10) << "Arrival" << setw(10) << "Burst" 
         << setw(15) << "Completion" << setw(15) << "Turnaround" << setw(10) << "Waiting" << endl;

    for (const auto& p : processes) {
        cout << left << "P" << setw(9) << p.id << setw(10) << p.arrivalTime << setw(10) << p.burstTime 
             << setw(15) << p.completionTime << setw(15) << p.turnaroundTime << setw(10) << p.waitingTime << endl;
    }

    cout << "\nAverage Waiting Time: " << (totalWT / processes.size()) << endl;
    cout << "Average Turnaround Time: " << (totalTAT / processes.size()) << endl;

    cout << "\n--- GANTT CHART (FCFS) ---" << endl;
    cout << "0 ";
    for (const auto& p : processes) cout << "|  P" << p.id << "  |";
    cout << endl << "  ";
    int timeDisplay = 0;
    for (const auto& p : processes) {
        timeDisplay += p.burstTime; 
        cout << left << setw(7) << timeDisplay;
    }
    cout << endl;
}

// ==========================================
// 2. SJF ALGORITHM
// ==========================================
void calculateSJF(vector<Process> processes) {
    int currentTime = 0;
    int completed = 0;
    int n = processes.size();
    double totalWT = 0, totalTAT = 0;
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
             << " (Burst: " << processes[idx].burstTime << "). Reason: Shortest burst among available." << endl;

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
    for (int idx : executionOrder) cout << "|  P" << processes[idx].id << "  |";
    cout << endl << "  ";
    int timeDisplay = 0;
    for (int idx : executionOrder) {
        timeDisplay = processes[idx].completionTime;
        cout << left << setw(7) << timeDisplay;
    }
    cout << endl;
}

// ==========================================
// MAIN FUNCTION (The Menu)
// ==========================================
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

    int choice;
    do {
        cout << "\n===================================" << endl;
        cout << "   CHRONOSCHEDULER - MAIN MENU" << endl;
        cout << "===================================" << endl;
        cout << "1. Run FCFS Algorithm" << endl;
        cout << "2. Run SJF Algorithm" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                calculateFCFS(processes);
                break;
            case 2:
                calculateSJF(processes);
                break;
            case 0:
                cout << "Exiting ChronoScheduler. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);

    return 0;
}