#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "../include/httplib.h"
#include "../include/algorithms.h"

using namespace std;

int main() {
    httplib::Server svr;

    svr.Post("/run", [](const httplib::Request& req, httplib::Response& res) {
        string body = req.body;
        
        size_t delimiterPos1 = body.find('|');
        string algo = body.substr(0, delimiterPos1);
        
        size_t delimiterPos2 = body.find('|', delimiterPos1 + 1);
        int quantum = stoi(body.substr(delimiterPos1 + 1, delimiterPos2 - delimiterPos1 - 1));
        
        string dataStr = body.substr(delimiterPos2 + 1);

        vector<Process> processes;
        stringstream ss(dataStr);
        string processStr;
        int id = 1;

        while (getline(ss, processStr, ';')) {
            stringstream pss(processStr);
            string arrivalStr, burstStr;
            getline(pss, arrivalStr, ',');
            getline(pss, burstStr, ',');

            Process p;
            p.id = id++;
            p.arrivalTime = stoi(arrivalStr);
            p.burstTime = stoi(burstStr);
            
            p.remainingTime = p.burstTime; 
            p.startTime = 0; 
            p.firstStartTime = -1; 
            p.completionTime = 0;
            p.responseTime = 0;
            p.turnaroundTime = 0;
            p.waitingTime = 0;
            
            processes.push_back(p);
        }

        stringstream buffer;
        streambuf* oldCout = cout.rdbuf(buffer.rdbuf());

        if (algo == "fcfs") {
            calculateFCFS(processes);
        } else if (algo == "sjf") {
            calculateSJF(processes);
        } else if (algo == "round_robin") {
            roundRobin(processes, quantum); 
        }

        cout.rdbuf(oldCout); 
        string outputText = buffer.str();

        string ganttData = "";
        
        if (algo == "round_robin") {
            for (const auto& block : rrGanttBlocks) {
                ganttData += "P" + to_string(block.pid) + "," + 
                             to_string(block.start) + "," + 
                             to_string(block.end) + "|";
            }
        } else {
            for (const auto& p : processes) {
                if (p.completionTime != 0) {
                    ganttData += "P" + to_string(p.id) + "," + 
                                 to_string(p.startTime) + "," + 
                                 to_string(p.completionTime) + "|";
                }
            }
        }

        string finalResponse = outputText + "@@@" + ganttData;

        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_content(finalResponse, "text/plain");
    });

    cout << "=================================================" << endl;
    cout << "ChronoScheduler Server is running on http://localhost:8080" << endl;
    cout << "=================================================" << endl;
    
    svr.listen("localhost", 8080);

    return 0;
}