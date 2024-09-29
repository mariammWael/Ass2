//Mariam Abdelaal 900231510
#ifndef SIMULATION_H
#define SIMULATION_H

#include <iostream>
#include <vector>
#include "plane.h"
#include "deq.h" // Assuming you have a header file for DEQ (Double Ended Queue)

class Simulation {
public:
    // Constructor with parameters for max planes, time step, and delta time
    Simulation(int Tmax, int Ts, int DeltaT);

    // Method to enqueue a plane into the simulation
    void enqueuePlane(const Plane& plane);

    // Method to process landing of planes at a given current time
    void processLanding(int);

    // Method to display planes currently in the DEQ
    void displayPlanes();

    void printAverageWaitTime() const ;

    int generateRandomPriority();

    int generateNextArrivalTime();


    void run();








private:
    DEQ<Plane> queue; // Queue to manage planes
    int Tmax;              // Maximum number of planes
    int Ts;                // Time step
    int DeltaT;
    vector<int> waitTimes;

    // Delta time
};

#endif // SIMULATION_H
