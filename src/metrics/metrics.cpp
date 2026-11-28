#include "../../include/metrics.h"
#include <stdexcept>

using namespace std;

void calculateMetrics(vector<Process>& processes)
{
    for (Process& p : processes)
    {
        if (p.firstStartTime < p.arrivalTime ||
            p.completionTime < p.firstStartTime ||
            p.completionTime <= p.arrivalTime)
        {
            throw invalid_argument("Process is not completed.");
        }

        p.turnaroundTime = p.completionTime - p.arrivalTime;

        p.waitingTime = p.turnaroundTime - p.burstTime;

        p.responseTime = p.firstStartTime - p.arrivalTime;
    }
}