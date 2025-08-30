/* File defines a methods for scheduling algorithms Rate Monotonic, Earliest Deadline
*  First, and Round Robin.
*/ 
#include "Task.h"
#include "Scheduler.h"
#include <climits>
#include <cmath>

/* Method returns name of task which is both ready and has the lowest period 
* in accordance with Rate Monotonic scheduling principles -- 
* shorter cyle duration results in higher priority since tasks with the shortest
* repeat more frequently and are often the most time critical in real systems. */
Task* Scheduler::scheduleRateMonotonic(vector<Task>& tasks, float currentTime) {
    Task* chosenTask = nullptr;
    float lowestPeriod = numeric_limits<float>::max();

    for (int i = 0; i < tasks.size(); i++) {
        if (tasks[i].isReady(currentTime) && (tasks[i].getPeriod() < lowestPeriod)) {
            chosenTask = &tasks[i];
            lowestPeriod = tasks[i].getPeriod();
        }
    }

    return chosenTask;
}

/* Method returns name of task which is both ready and has the least time  
* remaining until its deadline in accordance with Rate Monotonic scheduling 
* principles -- "panic-driven" scheduling as it aims to help the task that's
* most in danger of missing its deadline, regardless of how often the task
* normally runs */ 
Task* Scheduler::scheduleEDF(vector<Task>& tasks, float currentTime) {
    Task* chosenTask = nullptr;
    float leastTime = numeric_limits<float>::max();

    for (int i = 0; i < tasks.size(); i++) {
        float absoluteDeadline = tasks[i].getNextReleaseTime() - tasks[i].getPeriod() + tasks[i].getDeadline();
        float timeTilDeadline = absoluteDeadline - currentTime;

        if (tasks[i].isReady(currentTime) && (timeTilDeadline < leastTime)) {
            chosenTask = &tasks[i];
            leastTime = timeTilDeadline;
        }
    }

    return chosenTask;
}

/* Method returns name of task which is ready based off the provided timeQuantum
* which designates the time alotted to each task to run until it cycles to the next
* task in accordance with Round Robin scheduling principles -- the logic behind this 
* scheduling process is to allow each task in the list the opportunity to run. This 
* provides the benefit of eliminating starvation. 
*/ 
Task* Scheduler::scheduleRoundRobin(vector<Task>& tasks, float currentTime, float timeQuantum) {
    int numTasks = tasks.size();
    int startIndex = (int)(fmod(currentTime / timeQuantum, numTasks));

    // looping through all tasks to ensure which is ready; if task is not ready, move
    // to next task in sequence
    for (int i = 0; i < numTasks; i++) {
        int taskIndex = (startIndex + i) % numTasks;
        if (tasks[taskIndex].isReady(currentTime)) {
            return &tasks[taskIndex];
        }
    }

    return nullptr;
}