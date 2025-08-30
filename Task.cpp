#include "Task.h"

Task::Task(string n, float p, float eT, float d, int prty) {
    name = n;
    period = p;
    executionTime = eT;
    deadline = d;
    priority = prty;

    nextReleaseTime = 0;
    remainingExecution = executionTime;
    isRunning = false;

    deadlineMisses = 0;
}

// Getter methods:
string Task::getName() {
    return name;
}
float Task::getPeriod() {
    return period;
}
float Task::getET() {
    return executionTime;
}
float Task::getDeadline() {
    return deadline;
}
int Task::getPriority() {
    return priority;
}
bool Task::getRunningStatus() {
    return isRunning;
}

float Task::getNextReleaseTime() {
    return nextReleaseTime;
}
float Task::getRemainingExecution() {
    return remainingExecution;
}

// Scheduling Method:
bool Task::isReady(float currentTime) {
    return ((currentTime >= nextReleaseTime) && !isRunning && (remainingExecution > 0));
}

int Task::getDeadlineMisses() {
    return deadlineMisses;
}

void Task::executeOneTimeStep(float currentTime) {
    if (isRunning && remainingExecution > 0) {
        remainingExecution--; // Completion of 1ms of work

        if (remainingExecution == 0) {
            // Current Task is completed, so run below:
            float absoluteDeadline = nextReleaseTime - period + deadline;
            if (currentTime > absoluteDeadline) {
                deadlineMisses++;
            }

            isRunning = false;
            nextReleaseTime = nextReleaseTime + period; // Next period
            remainingExecution = executionTime;         // Fresh work for next time
        }
    }
}

void Task::startExecution() {
    isRunning = true;
}

void Task::reset() {
    nextReleaseTime = 0;
    remainingExecution = executionTime;
    isRunning = false;

    deadlineMisses = 0;
}
