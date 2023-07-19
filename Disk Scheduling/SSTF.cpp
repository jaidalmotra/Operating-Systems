#include <iostream>
#include <cmath>

using namespace std;

// Function to calculate the total head movements
int calculateTotalHeadMovements(int requests[], int size, int initialPosition) {
    int totalHeadMovements = 0;

    int visited[size];
    for (int i = 0; i < size; i++) {
        visited[i] = 0;
    }

    int currentPosition = initialPosition;
    for (int i = 0; i < size; i++) {
        int minDistance = INT_MAX;
        int index = -1;

        // Find the request with the shortest seek time
        for (int j = 0; j < size; j++) {
            if (visited[j] == 0) {
                int distance = abs(requests[j] - currentPosition);
                if (distance < minDistance) {
                    minDistance = distance;
                    index = j;
                }
            }
        }

        visited[index] = 1; // Mark the request as visited
        totalHeadMovements += minDistance;
        currentPosition = requests[index];
    }

    return totalHeadMovements;
}

// Function to print the request sequence and total head movements
void printDiskSchedule(int requests[], int size, int initialPosition, int totalHeadMovements) {
    cout << "Disk Request Sequence: ";
    for (int i = 0; i < size; i++) {
        cout << requests[i];
        if (i != size - 1) {
            cout << " -> ";
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
