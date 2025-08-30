#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <vector>
#include <string>
#include "Task.h"
#include <iostream>
using namespace std;

class Scheduler {
public:
    Task* scheduleRateMonotonic(vector<Task> &tasks, float currentTime);
    Task* scheduleEDF(vector<Task> &tasks, float currentTime);
    Task* scheduleRoundRobin(vector<Task> &tasks, float currentTime, float timeQuantum);
};

#endif