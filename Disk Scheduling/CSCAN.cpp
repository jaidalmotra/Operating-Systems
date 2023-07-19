#include <iostream>
#include <cmath>

using namespace std;

// Function to calculate the total head movements
int calculateTotalHeadMovements(int requests[], int size, int initialPosition) {
    int totalHeadMovements = 0;

    int currentPosition = initialPosition;

    // Find the nearest end point (smallest and largest cylinder number)
    int smallest = INT_MAX, largest = INT_MIN;
    for (int i = 0; i < size; i++) {
        if (requests[i] < smallest)
            smallest = requests[i];
        if (requests[i] > largest)
            largest = requests[i];
    }

    bool movingRight = (initialPosition < (largest + smallest) / 2); // Determine the initial direction

    while (true) {
        int nextRequest = INT_MAX;
        int index = -1;

        // Find the next request in the current direction
        for (int i = 0; i < size; i++) {
            if (movingRight && requests[i] >= currentPosition && requests[i] < nextRequest) {
                nextRequest = requests[i];
                index = i;
            } else if (!movingRight && requests[i] <= currentPosition && requests[i] > nextRequest) {
                nextRequest = requests[i];
                index = i;
            }
        }

        if (index != -1) {
            totalHeadMovements += abs(requests[index] - currentPosition);
            currentPosition = requests[index];
            requests[index] = -1; // Mark the request as visited
        } else {
            if (movingRight) {
                totalHeadMovements += abs(largest - currentPosition);
                currentPosition = largest;
                movingRight = false; // Change direction
            } else {
                totalHeadMovements += abs(smallest - currentPosition);
                currentPosition = smallest;
                movingRight = true; // Change direction
            }
        }

        // Check if all requests have been visited
        bool allVisited = true;
        for (int i = 0; i < size; i++) {
            if (requests[i] != -1) {
                allVisited = false;
                break;
            }
        }

        if (allVisited)
            break;
    }

    return totalHeadMovements;
}

// Function to print the request sequence and total head movements
void printDiskSchedule(int requests[], int size, int initialPosition, int totalHeadMovements) {
    cout << "Disk Request Sequence: ";
    for (int i = 0; i < size; i++) {
        if (requests[i] != -1) {
            cout << requests[i];
            if (i != size - 1) {
                cout << " -> ";
            }
        }
    }

    cout << "\nInitial Head Position: " << initialPosition;
    cout << "\nTotal Head Movements: " << totalHeadMovements << endl;
}

int main() {
    int initialPosition;
    const int MAX_SIZE = 100;
    int requests[MAX_SIZE];

    // Input the initial head position
    cout << "Enter the initial head position: ";
    cin >> initialPosition;

    // Input the disk requests
    cout << "Enter the disk requests (-1 to stop): ";
    int request;
    int size = 0;
    while (cin >> request && request != -1) {
        requests[size] = request;
        size++;
    }

    // Calculate total head movements
    int totalHeadMovements = calculateTotalHeadMovements(requests, size, initialPosition);

    // Print disk schedule
    printDiskSchedule(requests, size, initialPosition, totalHeadMovements);

    return 0;
}
