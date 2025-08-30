# Real-Time Task Scheduler Simulator - Artifact

**Name:** Phiroze Duggal 
**Date Completed:** 28 Aug, 2025  

---

## Overview

A C++ simulator that implements and compares different real-time scheduling algorithms which demonstrate understanding of RTOS concepts critical in embedded systems roles.

### Learning Objectives
- [X] Understand real-time scheduling constraints and guarantees
- [X] Implement classic real-time scheduling algorithms  
- [X] Analyze schedulability and timing behavior
- [X] Compare algorithm performance under different workloads

---

### Development Environment Setup
**IDE/Editor Used:** VS Code  
**Compiler:** g++ -- GNU C++ Compiler  
**Version Control:** GitHub

### Background Knowledge Check
Key concepts:

**Process vs Thread scheduling** - Threads share memory and resources within the same 
process. Thread scheduling and switching have lower overhead and are faster in terms of
context switches than process scheduling. In both cases, the OS must choose which program
or thread gets CPU time. Unlike threads, process have their own memory space and resources.

**Preemptive vs Non-preemptive scheduling** - In preemptive scheduling, the OS can interrupt a running task at any time to give the CPU to a higher priority task. 
Non-preemptive scheduling on the other hand allows a task to utilize the CPU until the 
task is done. 

**Real-time constraints** - These are the strict timing deadlines that must be met. This is
an essential concept when dealing with real-time scheduling where time predictability and
deadline compliance must be guaranteed. 

---

## Phase 1: Project Setup and Design

### Task 1.1: Project Structure
Create your project directory structure and document it here:

```
task_scheduler_simulator/
├── .vscode/
    ├── settings.json
├── docs/   
│   ├── .gitignore
│   ├── lab-worksheet.md
│   └── README.md
├── run
├── Scheduler.cpp
├── Scheduler.h
├── Task.cpp
├── Task.h
└── TaskList.cpp
```

**Build Command:** g++ Task.cpp Scheduler.cpp TaskList.cpp -o run

### Task 1.2: Task Class Design
Design and implement your Task class. Document your design decisions:

**Task Attributes:**
- Task name: Unique Identifier of task
- Period (T): Time between task releases
- Execution Time (C): Worst-case execution time
- Deadline (D): Relative deadline per task
- Priority: Necessary for priority-based algorithms
- Next Release Time: Time when task next available to run
- Remaining Execution: Time left for task in current period
- Deadline Misses: Count for number of deadline misses per task

**Key methods implemented:**
- Constructor
- get() methods for all task attributes/variables
- Other methods: 
  1. bool isReady(float currentTime)
  2. int getDeadlineMisses()
  3. void executeOneTimeStep(float currentTime)
  4. void startExecution()
  5. void reset()

### Task 1.3: Base Scheduler Interface
Document your scheduler base class design:

**Pure virtual methods:**
There are three methods, each corresponding to the different task scheduling algorithm 
being used.

**Common functionality in base class:** 
The class's main purpose is to hold the functions which call on either of the scheduling 
algorithms to be used for the taskList. 

---

## Phase 2: Algorithm Implementation

### Task 2.1: Rate Monotonic Scheduler

**Implementation Status:** Complete

**Priority Assignment Logic:**
Static priorities are assigned to each task based off their periods. Tasks with shorter periods gain higher priority. 

**Preemption Handling:**
If, after each time unit or 1ms, if task with a higher priority is ready, preempt the 
current task and switch to the higher priority task. That is, switch to the new task if
that new task has a shorter period/higher frequency. 

### Task 2.2: Earliest Deadline First Scheduler

**Implementation Status:** Complete

**Dynamic Priority Calculation:**
Priority is dynamic/shifts as tasks are being completed. After each time unit, absolute 
deadline = arrival_time + relative_deadline is calculated for each task. The task with
the earliest absolute deadline gains the highest priority. 

**Deadline Miss Detection:**
If at each time unit the current time exceeds the absolute deadline for any incomplete 
task, a deadline miss is recorded. 

### Task 2.3: Round Robin Scheduler

**Implementation Status:** Complete

**Time Quantum:** Arbitrary -- 10ms used in main()

**Queue Management:**
A list of tasks is already given as the argument to the scheduler function and thus, there
is a preset queue. When a task's quantum expires, the task is moved back in the queue (the tasks cycle through their turns of completion)

**Preemption Logic:**
Tasks are preempted when the current task uses the full quantum, the current task completes, or a new task arrives with the same priority level. 

---

## Phase 3: Testing and Analysis

### Task 3.1: Test Case Design

**Test Case - Schedulable Task Set:**
```
Task 1: Period=5ms, Exec_Time=_1ms, Deadline=5ms
Task 2: Period=20ms, Exec_Time=3ms, Deadline=20ms
Task 3: Period=1000ms, Exec_Time=50ms, Deadline=1000ms
Task 4: Period=100ms, Exec_Time=5ms, Deadline=100ms
```

### Task 3.2: Results Analysis

**Test Case Results:**
| Rate Monotonic | 2 misses | 65% CPU|
| EDF | 2 misses | 65% CPU |
| Round Robin | 2 misses | 65% CPU |


### Task 3.3: Timeline Visualization
Create a simple timeline showing task execution:

**Example for Test Case 1 - First 50 time units:**
```
Time:  0    10   20   50   100   199
Task1: 1    1    0    0     0     0
Task2: 0    0    0    0     0     0
Task3: 0    0    1    1     0     0
Task4: 0    0    0    0     1     0
```

---

## Lab Reflection

### Challenges Encountered
1. Initial learning curve re-exposing myself to C++ syntax and programming logic.

2. Learning of the logic and uses of various OS scheduling routines. 

3. Debugging.

### Key Insights
1. **Real-time vs General Purpose Scheduling:** 
Real-time requires predictable timing guarantees, not just average performance optimization.

2. **Algorithm Trade-offs:**
RM is simpler and more predictable and may not always provide the most optimal solution. EDF is optimal but more complex and may also lead to starvation of taks. RR provides fairnessbut poor real-time guarantees and may not be optimal as it does not take into account priority of different tasks (Different tasks are assigned the same priority).

3. **Embedded Systems Implications:** 
Understanding timing constraints is crucial - late results may cause system failures in embedded applications. 

### Interview Preparation
**Elevator Pitch (30 seconds):**
I built a real-time scheduler simulator in C++ inplementing RM, EDF, and RR algorithms. It
demonstrates schedulability analysis, deadline guarantee testing, and performance comparison - key concepts for embedded systems where timing predictability is critical. 

**Technical Deep-Dive Questions You Can Answer -- REVIEW PRIOR TO INTERVIEW:**
- [X] "Walk me through how Rate Monotonic scheduling works"
- [X] "How would you handle priority inversion in a real embedded system?"
- [X] "What are the trade-offs between different real-time scheduling approaches?"


