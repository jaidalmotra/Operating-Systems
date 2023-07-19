#include <iostream>
#include <cmath>

using namespace std;

// Function to calculate the total head movements
int calculateTotalHeadMovements(int requests[], int size, int initialPosition) {
    int totalHeadMovements = abs(requests[0] - initialPosition);

    for (int i = 1; i < size; i++) {
        totalHeadMovements += abs(requests[i] - requests[i - 1]);
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
