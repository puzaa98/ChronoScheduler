#include <iostream>
#include <vector>
#include "../include/algorithms.h"

using namespace std;

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