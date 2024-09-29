//Mariam Abdelaal 900231510
#include "simulation.h"
#include "deq.h"
#include "plane.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Constructor: initializes the simulation with given time parameters
Simulation::Simulation(int Tmax, int Ts, int DeltaT)
    : Tmax(Tmax), Ts(Ts), DeltaT(DeltaT) {
    srand((unsigned)time(0));  // Initialize random number generator
}

// Run the simulation
void Simulation::run() {
    int currentTime = 0;  // Track the current time of the simulation
    int nextArrivalTime = generateNextArrivalTime();  // Time for the next plane to arrive

    while (currentTime < Tmax) {
        // Check if it's time for the next plane to arrive
        if (currentTime >= nextArrivalTime) {
            Plane newPlane(currentTime, generateRandomPriority());
            enqueuePlane(newPlane);
            nextArrivalTime += generateNextArrivalTime();  // Schedule the next arrival
        }

        // Process landing every Ts minutes
        if (currentTime % Ts == 0) {
            processLanding(currentTime);
        }

        currentTime++;  // Increment the current time
    }

    // Print the average wait time after the simulation ends
    printAverageWaitTime();
}

// Enqueue a plane into the queue based on its priority
void Simulation::enqueuePlane(const Plane& plane) {
    // If the DEQ is empty, add the plane to the front
    if (queue.DEQisEmpty()) {
        queue.Add_Front(plane);
    } else {
        // Traverse the DEQ to find the correct position based on priority
        DEQ<Plane> tempQueue;  // Temporary DEQ to hold planes
        while (!queue.DEQisEmpty()) {
            Plane frontPlane = queue.Remove_Front();
            // Insert the plane if it has a higher priority
            if (plane.priority > frontPlane.priority) {
                tempQueue.Add_Front(frontPlane);  // Move frontPlane to tempQueue
                break;  // Stop traversing as we found the insertion point
            } else {
                tempQueue.Add_Front(frontPlane);  // Move frontPlane to tempQueue
            }
        }
        // Add the new plane to the tempQueue
        tempQueue.Add_Front(plane);
        // Restore remaining planes back to the main queue
        while (!queue.DEQisEmpty()) {
            tempQueue.Add_Front(queue.Remove_Front());
        }
        // Restore the tempQueue to the original queue
        while (!tempQueue.DEQisEmpty()) {
            queue.Add_Front(tempQueue.Remove_Front());
        }
    }
}

// Simulate landing of planes
void Simulation::processLanding(int currentTime) {
    // Ensure there is a plane to land
    if (!queue.DEQisEmpty()) {
        Plane landingPlane = queue.Remove_Front();  // Get the plane at the front
        int waitTime = currentTime - landingPlane.arrivalTime;  // Calculate wait time
        waitTimes.push_back(waitTime);  // Store the wait time
        cout << "Plane with priority " << landingPlane.priority
             << " landed after waiting for " << waitTime << " minutes." << endl;
    }
}

// Calculate and print the average wait time
void Simulation::printAverageWaitTime() const {
    if (waitTimes.empty()) {
        cout << "No planes landed." << endl;
        return;
    }

    int totalWaitTime = 0;
    for (int time : waitTimes) {
        totalWaitTime += time;
    }
    double averageWaitTime = static_cast<double>(totalWaitTime) / waitTimes.size();
    cout << "Average wait time: " << averageWaitTime << " minutes." << endl;
}

// Generates a random priority (0 = low, 1 = medium, 2 = high)
int Simulation::generateRandomPriority() {
    return rand() % 3;  // Random priority between 0 (low) and 2 (high)
}

// Generates the time for the next plane's arrival
int Simulation::generateNextArrivalTime() {
    return DeltaT + (rand() % 3 - 1);  // Adds some variability to DeltaT
}
