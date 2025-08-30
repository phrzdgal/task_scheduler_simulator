// File defines a data structure (vector) to hold multiple tasks running together
#include "Task.h"
#include "Scheduler.h"

int main() {
    // Tasks:
    Task adcReading("adcReading", 5, 1, 5, 1);       // Read battery voltage every 5ms
    Task pumpControl("pumpControl", 20, 3, 20, 2);    // Control water pump every 20ms
    Task radioComm("radioComm", 1000, 50, 1000, 3); // Send status every 1 second
    Task safetyCheck("safetyCheck", 100, 5, 100, 1);  // Safety monitor every 100ms

    vector<Task> taskList;
    taskList.push_back(adcReading);
    taskList.push_back(pumpControl);
    taskList.push_back(radioComm);
    taskList.push_back(safetyCheck);

    Scheduler scheduler;

    float totalTime = 200.0;
    float busyTime;

    float RMcpuUtilization;
    float EDFcpuUtilization;
    float RRcpuUtilization;

    int RMmisses;
    int EDFmisses;
    int RRmisses;

    // RateMonotonic Simulation
    cout << "=== RATE MONOTONIC SIMULATION ===" << endl;
    busyTime = 0.0;
    for (float ms = 0.0; ms < 200.0; ms += 1.0) {
        // Check if any task is currently running
        bool anyTaskRunning = false;
        for (int i = 0; i < taskList.size(); i++) {
            if (taskList[i].getRunningStatus()) {
                anyTaskRunning = true;
                break;
            }
        }

        Task *chosenTask = nullptr;
        if (!anyTaskRunning) {
            // New task is chosen only if nothing is currently running
            chosenTask = scheduler.scheduleRateMonotonic(taskList, ms);
            if (chosenTask != nullptr) {
                chosenTask->startExecution();
            }
        }

        if (anyTaskRunning || chosenTask != nullptr) {
            busyTime += 1.0;
            // Determining which task is running for output:
            for (int i = 0; i < taskList.size(); i++) {
                if (taskList[i].getRunningStatus()) {
                    cout << "Time " << ms << "ms: Running " << taskList[i].getName() << endl;
                    break;
                }
            }
        } else {
            cout << "Time " << ms << "ms: CPU idle" << endl;
        } 

        // Update ALL tasks (whether running or not)
        for (int i = 0; i < taskList.size(); i++) {
            taskList[i].executeOneTimeStep(ms);
        }
    }

    RMcpuUtilization = (busyTime / totalTime) * 100.0;

    // Deadline Miss Detection & reset:
    for (int i = 0; i < taskList.size(); i++) {
        RMmisses = taskList[i].getDeadlineMisses();
        taskList[i].reset();
    }



    // EDF Simulation
    cout << "=== EARLIEST DEADLINE FIRST SIMULATION ===" << endl;
    busyTime = 0.0;
    for (float ms = 0.0; ms < 200.0; ms += 1.0) {
        // Check if any task is currently running
        bool anyTaskRunning = false;
        for (int i = 0; i < taskList.size(); i++) {
            if (taskList[i].getRunningStatus()) {
                anyTaskRunning = true;
                break;
            }
        }

        Task *chosenTask = nullptr;
        if (!anyTaskRunning) {
            // New task is chosen only if nothing is currently running
            chosenTask = scheduler.scheduleEDF(taskList, ms);
            if (chosenTask != nullptr) {
                chosenTask->startExecution();
            }
        }

        if (anyTaskRunning || chosenTask != nullptr) {
            busyTime += 1.0;
            // Determining which task is running for output:
            for (int i = 0; i < taskList.size(); i++) {
                if (taskList[i].getRunningStatus()) {
                    cout << "Time " << ms << "ms: Running " << taskList[i].getName() << endl;
                    break;
                }
            }
        } else {
            cout << "Time " << ms << "ms: CPU idle" << endl;
        } 

        // Update ALL tasks (whether running or not)
        for (int i = 0; i < taskList.size(); i++) {
            taskList[i].executeOneTimeStep(ms);
        }
    }

    EDFcpuUtilization = (busyTime / totalTime) * 100.0;
    
    // Deadline Miss Detection & Reset:
    for (int i = 0; i < taskList.size(); i++) {
        EDFmisses = taskList[i].getDeadlineMisses();
        taskList[i].reset();
    }



    // RoundRobin Simulation
    cout << "=== ROUND ROBIN SIMULATION ===" << endl;
    busyTime = 0.0;
    for (float ms = 0.0; ms < 200.0; ms += 1.0) {
       // Check if any task is currently running
        bool anyTaskRunning = false;
        for (int i = 0; i < taskList.size(); i++) {
            if (taskList[i].getRunningStatus()) {
                anyTaskRunning = true;
                break;
            }
        }

        Task *chosenTask = nullptr;
        if (!anyTaskRunning) {
            // New task is chosen only if nothing is currently running
            chosenTask = scheduler.scheduleRoundRobin(taskList, ms, 10.0);
            if (chosenTask != nullptr) {
                chosenTask->startExecution();
            }
        }

        if (anyTaskRunning || chosenTask != nullptr) {
            busyTime += 1.0;
            // Determining which task is running for output:
            for (int i = 0; i < taskList.size(); i++) {
                if (taskList[i].getRunningStatus()) {
                    cout << "Time " << ms << "ms: Running " << taskList[i].getName() << endl;
                    break;
                }
            }
        } else {
            cout << "Time " << ms << "ms: CPU idle" << endl;
        } 

        // Update ALL tasks (whether running or not)
        for (int i = 0; i < taskList.size(); i++) {
            taskList[i].executeOneTimeStep(ms);
        }
    }

    RRcpuUtilization = (busyTime / totalTime) * 100.0;
    
    // Deadline Miss Detection & Reset:
    for (int i = 0; i < taskList.size(); i++) {
        RRmisses = taskList[i].getDeadlineMisses();
        taskList[i].reset();
    }


    cout << "\n=== Algorithm Comparison ===" << endl;
    cout << "Rate Monotonic: " << RMmisses << " misses, " << RMcpuUtilization << "% CPU" << endl;
    cout << "EDF: " << EDFmisses << " misses, " << EDFcpuUtilization << "% CPU" << endl;
    cout << "Round Robin: " << RRmisses << " misses, " << RRcpuUtilization << "% CPU" << endl;

    return 0;
}