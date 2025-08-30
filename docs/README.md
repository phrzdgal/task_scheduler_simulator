# Real-Time Task Scheduler Simulator

A C++ implementation of three real-time scheduling algorithms designed to bridge computer science algorithms knowledge into embedded systems engineering concepts.

## Project Overview

This simulator demonstrates how different real-time scheduling algorithms handle time-critical tasks in resource-constrained environments. More specifically, the program
models emergency infrastructure systems for crisis scenarios like Gaza's water and power management. In real world embedded systems, hard deadlines exist. Missing deadlines even
by 1ms can cause system failure in applications. Furthermore, embedded processers have
limited CPU, memory, and power and require predictable and analyzable performance rather
than best-effort execution. This task scheduler utilizes a real-world crisis scenario
to demonstrate the functionality and importance of different concepts within embedded
systems. 

## Scheduling Algorithms Implemented

### Rate Monotonic (RM)
- **Priority Assignment**: Tasks with shorter periods receive higher priority
- **Behavior**: Fixed priorities, simple and predictable
- **Use Case**: Automotive systems, industrial control

### Earliest Deadline First (EDF)
- **Priority Assignment**: Dynamic priorities based on absolute deadlines
- **Behavior**: Always runs the task closest to missing its deadline
- **Use Case**: Aerospace applications, complex real-time systems

### Round Robin (RR)
- **Priority Assignment**: Equal time slices for all tasks
- **Behavior**: Fair CPU sharing, ignores deadlines
- **Use Case**: General-purpose systems (poor for real-time)

## Task Set: Gaza Emergency Infrastructure

The simulation models critical infrastructure tasks:

- **ADC Reading** (5ms period, 1ms execution): Battery voltage monitoring
- **Pump Control** (20ms period, 3ms execution): Water pump management  
- **Safety Check** (100ms period, 5ms execution): System health monitoring
- **Radio Communication** (1000ms period, 50ms execution): Status updates

## Key Features

- **Execution Tracking**: Tasks run for their full execution time
- **Deadline Miss Detection**: Identifies when tasks fail to meet timing constraints
- **CPU Utilization Monitoring**: Tracks system resource usage
- **Algorithm Comparison**: Side-by-side performance analysis

## Compilation and Execution

```bash```
# Compile
g++ Task.cpp Scheduler.cpp TaskList.cpp -o run

# Run simulation
./run

# Sample Output

=== RATE MONOTONIC SIMULATION ===
Time 0ms: Running adcReading
Time 1ms: Running pumpControl
Time 4ms: Running safetyCheck
...

=== Algorithm Comparison ===
Rate Monotonic: 2 misses, 65% CPU
EDF: 2 misses, 65% CPU  
Round Robin: 2 misses, 65% CPU