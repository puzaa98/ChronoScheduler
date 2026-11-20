#include <iostream>
#include <vector>
#include <iomanip>
#include <climits>

using namespace std;

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int priority;
    int remainingTime;
    int startTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
    int responseTime;
    bool started;
};

struct GanttBlock {
    int pid;
    int start;
    int end;
};

void calculateSRTF(vector<Process> processes) {
    int n = processes.size();
    int currentTime = 0;
    int completed = 0;
    int lastPid = -1;
    double totalWT = 0, totalTAT = 0, totalRT = 0;

    vector<GanttBlock> gantt;

    for (auto& p : processes) {
        p.remainingTime = p.burstTime;
        p.startTime = -1;
        p.completionTime = 0;
        p.turnaroundTime = 0;
        p.waitingTime = 0;
        p.responseTime = -1;
        p.started = false;
    }

    cout << "\n--- [SRTF DECISION EXPLAINER LOG] ---" << endl;

    while (completed != n) {
        int idx = -1;
        int minRem = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0) {
                if (processes[i].remainingTime < minRem) {
                    minRem = processes[i].remainingTime;
                    idx = i;
                } else if (processes[i].remainingTime == minRem) {
                    if (processes[i].arrivalTime < processes[idx].arrivalTime) {
                        idx = i;
                    } else if (processes[i].arrivalTime == processes[idx].arrivalTime &&
                               processes[i].id < processes[idx].id) {
                        idx = i;
                    }
                }
            }
        }

        if (idx == -1) {
            if (lastPid != 0) {
                cout << "Time " << currentTime << ": CPU Idle. Reason: No arrived process remaining." << endl;
                lastPid = 0;
            }
            if (!gantt.empty() && gantt.back().pid == -1 && gantt.back().end == currentTime) {
                gantt.back().end = currentTime + 1;
            } else {
                gantt.push_back({-1, currentTime, currentTime + 1});
            }
            currentTime++;
            continue;
        }

        if (!processes[idx].started) {
            processes[idx].started = true;
            processes[idx].startTime = currentTime;
            processes[idx].responseTime = processes[idx].startTime - processes[idx].arrivalTime;
        }

        if (processes[idx].id != lastPid) {
            if (lastPid > 0) {
                cout << "Time " << currentTime << ": CPU switched to P" << processes[idx].id
                     << " (Remaining: " << processes[idx].remainingTime
                     << "). Reason: Shortest remaining burst among ready processes (preemption)." << endl;
            } else {
                cout << "Time " << currentTime << ": CPU selected P" << processes[idx].id
                     << " (Remaining: " << processes[idx].remainingTime
                     << "). Reason: Shortest remaining burst among ready processes." << endl;
            }
            lastPid = processes[idx].id;
        }

        if (!gantt.empty() && gantt.back().pid == processes[idx].id && gantt.back().end == currentTime) {
            gantt.back().end = currentTime + 1;
        } else {
            gantt.push_back({processes[idx].id, currentTime, currentTime + 1});
        }

        processes[idx].remainingTime--;
        currentTime++;

        if (processes[idx].remainingTime == 0) {
            processes[idx].completionTime = currentTime;
            processes[idx].turnaroundTime = processes[idx].completionTime - processes[idx].arrivalTime;
            processes[idx].waitingTime = processes[idx].turnaroundTime - processes[idx].burstTime;

            totalWT += processes[idx].waitingTime;
            totalTAT += processes[idx].turnaroundTime;
            totalRT += processes[idx].responseTime;

            completed++;
            cout << "Time " << currentTime << ": P" << processes[idx].id << " finished execution." << endl;
            lastPid = -1;
        }
    }

    cout << "\n--- SRTF SCHEDULING RESULTS ---" << endl;
    cout << left << setw(10) << "Process" << setw(10) << "Arrival" << setw(10) << "Burst"
         << setw(12) << "Completion" << setw(12) << "Turnaround" << setw(10) << "Waiting"
         << setw(10) << "Response" << endl;

    for (const auto& p : processes) {
        cout << left << "P" << setw(9) << p.id << setw(10) << p.arrivalTime << setw(10) << p.burstTime
             << setw(12) << p.completionTime << setw(12) << p.turnaroundTime << setw(10) << p.waitingTime
             << setw(10) << p.responseTime << endl;
    }

    cout << fixed << setprecision(2);
    cout << "\nAverage Waiting Time: " << (totalWT / n) << endl;
    cout << "Average Turnaround Time: " << (totalTAT / n) << endl;
    cout << "Average Response Time: " << (totalRT / n) << endl;

    cout << "\n--- GANTT CHART (SRTF) ---" << endl;
    for (const auto& g : gantt) {
        if (g.pid == -1) {
            cout << "| IDLE (" << g.start << "-" << g.end << ") ";
        } else {
            cout << "| P" << g.pid << " (" << g.start << "-" << g.end << ") ";
        }
    }
    cout << "|" << endl;
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
        processes[i].priority = 0;
    }

    calculateSRTF(processes);
    return 0;
}
