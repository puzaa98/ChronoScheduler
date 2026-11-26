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
        
        // The frontend sends: "algo|arrival,burst;arrival,burst"
        size_t delimiterPos = body.find('|');
        string algo = body.substr(0, delimiterPos);
        string dataStr = body.substr(delimiterPos + 1);

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
            processes.push_back(p);
        }

        // THIS IS THE MAGIC TRICK: We capture the output of your C++ functions
        stringstream buffer;
        streambuf* oldCout = cout.rdbuf(buffer.rdbuf());

        // Call your real algorithms!
        if (algo == "fcfs") {
            calculateFCFS(processes);
        } else if (algo == "sjf") {
            calculateSJF(processes);
        }

        // Restore the normal terminal output
        cout.rdbuf(oldCout);

        // Get the text that your algorithms printed
        string outputText = buffer.str();

        // Send it back to the web page
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_content(outputText, "text/plain");
    });

    cout << "ChronoScheduler Server is running on http://localhost:8080" << endl;
    cout << "Keep this terminal open while using the GUI." << endl;
    
    svr.listen("localhost", 8080);

    return 0;
}