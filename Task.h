// Header file for Task class
#ifndef TASK_H
#define TASK_H

#include <string>
#include <iostream>
#include <vector>
using namespace std;

// Defines a class Task with parameters to specify its functionality
// and priority
class Task {
private:
    string name;
    // How often Task needs to run (time between job releases):
    float period;
    // How long the task actually takes to run:
    float executionTime;
    // Maximum response time allowed:
    float deadline;
    int priority;

    // (Variable below) When this task should next become available to run/When it can 
    // start its next period of work:
    float nextReleaseTime;
    // How much work is left for this task in the current period:
    float remainingExecution;
    // Whether or not this task is currently using the CPU:
    bool isRunning;

    int deadlineMisses;

public:
    Task(string n, float p, float eT, float d, int prty);

    // Getter method declarations
    string getName();
    float getPeriod();
    float getET();
    float getDeadline();
    int getPriority();
    bool getRunningStatus();

    float getNextReleaseTime();
    float getRemainingExecution();

    // Scheduling method declaration
    bool isReady(float currentTime);

    int getDeadlineMisses();

    // Helper methods for TaskList.cpp to update Task every 1ms:
    void executeOneTimeStep(float currentTime);
    void startExecution();

    // reset() method to reset Task states prior to next scheduler run:
    void reset();
};

#endif