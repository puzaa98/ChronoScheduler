# ChronoScheduler

An interactive CPU scheduling simulator built as an Operating Systems course project.

**Visualize. Compare. Optimize.**

---

## About the Project

CPU scheduling decides which process gets the CPU and for how long. Different algorithms give different results in waiting time, turnaround time, response time, and fairness.

We noticed that when you study these algorithms only from slides and solve them by hand, it's hard to actually see what is happening. So we built a simulator where you can enter processes, run them through different algorithms, and look at the results side by side.

This is a learning tool first. It is not meant to replace a real OS scheduler.

---

## What It Will Do

- Take process details as input through a modern Graphical User Interface (GUI).
- Run the processes through a selected scheduling algorithm.
- Show the execution order as a visual Gantt chart.
- Calculate completion time, turnaround time, waiting time, and response time.
- Compare multiple algorithms on the same set of processes.
- Explain why a process was picked at each step (Decision Explainer Log).
- Point out processes that waited too long (starvation) and show how aging helps.
- Let you change arrival times, burst times, priorities, or the time quantum and rerun the same workload to see what changes.

---

## Algorithms

| Algorithm | Type |
|---|---|
| FCFS | Non-preemptive |
| SJF | Non-preemptive |
| SRTF | Preemptive |
| Priority Scheduling | Preemptive / Non-preemptive |
| Round Robin | Preemptive (time quantum) |

---

## Tech Stack

- **Backend Logic:** C++
- **Frontend Interface:** HTML, CSS, JavaScript
- **Communication:** HTTP Server (using `cpp-httplib`)
- **Version control:** Git + GitHub

---

## Folder Structure

```text
ChronoScheduler/
├── README.md
├── .gitignore
├── gui/
│   └── index.html          # Web-based User Interface
├── src/
│   ├── main.cpp            # C++ Server & Main Controller
│   ├── algorithms/
│   │   ├── fcfs.cpp        # FCFS Logic & Gantt Chart
│   │   └── sjf.cpp         # SJF Logic & Gantt Chart
│   ├── metrics/
│   └── simulation/
├── include/
│   ├── algorithms.h        # Function declarations
│   ├── process.h           # Process struct
│   └── httplib.h           # Web server library
├── tests/
└── docs/
```

---

## Roadmap

We are building this in stages instead of trying to finish everything at once.

- [x] **Phase 1 - Core simulation**
      Implemented FCFS and SJF with accurate metrics calculation.
- [x] **Phase 2 - Gantt chart output & GUI**
      Integrated a web-based GUI dashboard with the C++ backend, displaying text-based Gantt charts and decision logs.
- [ ] **Phase 3 - Decision explanation (Advanced)**
      Expand the log to explain preemption and priority decisions for SRTF and Priority Scheduling.
- [ ] **Phase 4 - Fairness analysis**
      Detect long waiting times and demonstrate priority aging.
- [ ] **Phase 5 - What-if experiments and recommendation**
      Compare workloads by changing inputs, and suggest an algorithm based on the actual results.
- [ ] **Phase 6 - Testing and documentation**
      Verify with hand-calculated test cases and finish the docs.

---

## Testing Plan

We will write at least 10 test cases with expected results calculated by hand. Each test will be run against the simulator and the output compared manually.

Test inputs will vary in arrival times, burst times, priorities, and time quantum values.

---

## Team

**Department of Computer Science and Engineering**
**Metropolitan University**

| Role | Name | GitHub |
|---|---|---|
| Team Leader | Puza Talukder | [@puzaa98](https://github.com/puzaa98) |
| Member | Israt Zahan Moumita | [@IsratZahanMoumita](https://github.com/IsratZahanMoumita) |
| Member | Anika Tasnim | [@anika-tasnim-07](https://github.com/anika-tasnim-07) |

### Work Division

| Member | Core work | Advanced work |
|---|---|---|
| Puza (Leader) | FCFS, SJF, Gantt Chart & CPU Idle tracking, GUI development, PR Reviews & Integration | Recommendation engine |
| Israt | SRTF, Priority Scheduling | Advanced Decision Explainer (preemption logic), fairness and aging analysis |
| Anika | Round Robin, shared metrics module (CT/TAT/WT/RT) | What-if experiment lab, test coordination |

Everyone writes 3-4 test cases for their own algorithms and reviews each other's pull requests before merging.

---

## References

1. Silberschatz, A., Galvin, P. B., & Gagne, G. *Operating System Concepts*, 10th Edition, Wiley.
2. Stallings, W. *Operating Systems: Internals and Design Principles*, Pearson.
3. Course lectures and lab materials, Operating Systems, Metropolitan University.

---

## Status

Under development. Phases 1 and 2 are complete. GUI and backend are successfully connected!

**ChronoScheduler - Visualize. Compare. Optimize.**
