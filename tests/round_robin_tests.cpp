#include "../include/algorithms.h"
#include "../include/metrics.h"
#include <iostream>
#include <vector>

using namespace std;

bool checkResults(const vector<Process>& processes,
                  const vector<int>& ct,
                  const vector<int>& tat,
                  const vector<int>& wt,
                  const vector<int>& rt)
{
    if (processes.size() != ct.size())
        return false;

    for (size_t i = 0; i < processes.size(); i++)
    {
        if (processes[i].completionTime != ct[i] ||
            processes[i].turnaroundTime != tat[i] ||
            processes[i].waitingTime != wt[i] ||
            processes[i].responseTime != rt[i])
        {
            return false;
        }
    }

    return true;
}

bool test1()
{
    vector<Process> p(3);

    p[0].pid = 1;
    p[0].arrivalTime = 0;
    p[0].burstTime = 5;

    p[1].pid = 2;
    p[1].arrivalTime = 1;
    p[1].burstTime = 3;

    p[2].pid = 3;
    p[2].arrivalTime = 2;
    p[2].burstTime = 1;

    roundRobin(p, 2);
    calculateMetrics(p);

    return checkResults(p, {9, 8, 5},
                           {9, 7, 3},
                           {4, 4, 2},
                           {0, 1, 2});
}

bool test2()
{
    vector<Process> p(3);

    p[0].pid = 1;
    p[0].arrivalTime = 0;
    p[0].burstTime = 4;

    p[1].pid = 2;
    p[1].arrivalTime = 0;
    p[1].burstTime = 2;

    p[2].pid = 3;
    p[2].arrivalTime = 0;
    p[2].burstTime = 1;

    roundRobin(p, 2);
    calculateMetrics(p);

    return checkResults(p, {7, 4, 5},
                           {7, 4, 5},
                           {3, 2, 4},
                           {0, 2, 4});
}

bool test3()
{
    vector<Process> p(3);

    p[0].pid = 1;
    p[0].arrivalTime = 2;
    p[0].burstTime = 3;

    p[1].pid = 2;
    p[1].arrivalTime = 8;
    p[1].burstTime = 2;

    p[2].pid = 3;
    p[2].arrivalTime = 9;
    p[2].burstTime = 1;

    roundRobin(p, 2);
    calculateMetrics(p);

    return checkResults(p, {5, 10, 11},
                           {3, 2, 2},
                           {0, 0, 1},
                           {0, 0, 1});
}

bool test4()
{
    vector<Process> p(2);

    p[0].pid = 1;
    p[0].arrivalTime = 0;
    p[0].burstTime = 3;

    p[1].pid = 2;
    p[1].arrivalTime = 0;
    p[1].burstTime = 2;

    roundRobin(p, 1);
    calculateMetrics(p);

    return checkResults(p, {5, 4},
                           {5, 4},
                           {2, 2},
                           {0, 1});
}

int main()
{
    int passed = 0;

    if (test1())
    {
        cout << "Test 1: PASSED" << endl;
        passed++;
    }
    else
        cout << "Test 1: FAILED" << endl;

    if (test2())
    {
        cout << "Test 2: PASSED" << endl;
        passed++;
    }
    else
        cout << "Test 2: FAILED" << endl;

    if (test3())
    {
        cout << "Test 3: PASSED" << endl;
        passed++;
    }
    else
        cout << "Test 3: FAILED" << endl;

    if (test4())
    {
        cout << "Test 4: PASSED" << endl;
        passed++;
    }
    else
        cout << "Test 4: FAILED" << endl;

    cout << "\nTotal Passed: " << passed << "/4" << endl;

    return passed == 4 ? 0 : 1;
}