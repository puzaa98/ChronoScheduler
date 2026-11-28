#ifndef PROCESS_H
#define PROCESS_H

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int startTime;
    int firstStartTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
    int responseTime;
};

#endif