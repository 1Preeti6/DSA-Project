#include<bits/stdc++.h>
using namespace std;

struct Driver {
    int id;
    double x, y; // Coordinates of the driver

    Driver(int id, double x, double y) : id(id), x(x), y(y) {}
};

struct RideRequest {
    int riderId;
    double x, y; // Coordinates of the rider

    RideRequest(int riderId, double x, double y) : riderId(riderId), x(x), y(y) {}
};

// Class for the Ride-Sharing System
class RideSharingSystem {
private:
    vector<Driver> drivers; // List of available drivers
    queue<RideRequest> rideQueue; // Queue for ride requests
    unordered_map<int, string> assignedRides; // Map to store assigned rides

public:
    // Add a driver to the system
    void addDriver(int id, double x, double y) {
        drivers.emplace_back(id, x, y);
        cout << "Driver " << id << " added at location (" << x << ", " << y << ").\n";
    }

    // Add a ride request to the queue
    void addRideRequest(int riderId, double x, double y) {
        rideQueue.emplace(riderId, x, y);
        cout << "Ride request from Rider " << riderId << " at location (" << x << ", " << y << ") added.\n";
    }

    // Find the distance between two points
    double calculateDistance(double x1, double y1, double x2, double y2) {
        return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
    }

    // Match rides to the nearest drivers
    void matchRides() {
        while (!rideQueue.empty()) {
            RideRequest request = rideQueue.front();
            rideQueue.pop();

            if (drivers.empty()) {
                cout << "No drivers available for Rider " << request.riderId << ".\n";
                continue;
            }

            double minDistance = DBL_MAX;
            vector<Driver>::iterator nearestDriver;

            // Find the nearest driver
            for (auto it = drivers.begin(); it != drivers.end(); ++it) {
                double distance = calculateDistance(request.x, request.y, it->x, it->y);
                if (distance < minDistance) {
                    minDistance = distance;
                    nearestDriver = it;
                }
            }

            cout << "Rider " << request.riderId << " matched with Driver " << nearestDriver->id
                 << " (Distance: " << minDistance << ").\n";

            // Update the assigned rides map
            assignedRides[request.riderId] = "Driver " + to_string(nearestDriver->id);

            // Remove the driver from the available drivers list
            drivers.erase(nearestDriver);
        }
    }

    // Display assigned rides
    void displayAssignedRides() {
        cout << "\nAssigned Rides:\n";
        for (const auto& ride : assignedRides) {
            cout << "Rider " << ride.first << " -> " << ride.second << "\n";
        }
    }
};

int main() {
    RideSharingSystem system;

    int choice;
    do {
        cout << "\nRide-Sharing System Menu:\n";
        cout << "1. Add Driver\n";
        cout << "2. Add Ride Request\n";
        cout << "3. Match Rides\n";
        cout << "4. Display Assigned Rides\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int id;
                double x, y;
                cout << "Enter driver ID: ";
                cin >> id;
                cout << "Enter driver location (x y): ";
                cin >> x >> y;
                system.addDriver(id, x, y);
                break;
            }
            case 2: {
                int riderId;
                double x, y;
                cout << "Enter rider ID: ";
                cin >> riderId;
                cout << "Enter rider location (x y): ";
                cin >> x >> y;
                system.addRideRequest(riderId, x, y);
                break;
            }
            case 3: {
                system.matchRides();
                break;
            }
            case 4: {
                system.displayAssignedRides();
                break;
            }
            case 5: {
                cout << "Exiting the system.\n";
                break;
            }
            default: {
                cout << "Invalid choice! Please try again.\n";
            }
        }
    } while (choice != 5);

    return 0;
}
