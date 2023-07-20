#include <iostream>
#include <algorithm>

using namespace std;

struct Process {
    int processId;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int waitingTime;
    int turnaroundTime;
};

// Function to calculate the average waiting time and turnaround time
void calculateAverageTimes(Process processes[], int n, float& averageWaitingTime, float& averageTurnaroundTime) {
    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;

    int currentTime = 0; // Tracks the current time during execution

    // Sort the processes based on arrival time
    sort(processes, processes + n, [](const Process& p1, const Process& p2) {
        return p1.arrivalTime < p2.arrivalTime;
    });

    for (int i = 0; i < n; i++) {
        // Find the process with the shortest burst time among the available processes
        int shortestJobIndex = -1;
        int shortestBurstTime = INT_MAX;
        for (int j = 0; j < n; j++) {
            if (processes[j].arrivalTime <= currentTime && processes[j].burstTime < shortestBurstTime) {
                shortestJobIndex = j;
                shortestBurstTime = processes[j].burstTime;
            }
        }

        if (shortestJobIndex == -1) {
            currentTime++;
            continue;
        }

        // Update the current time
        currentTime += processes[shortestJobIndex].burstTime;

        // Completion time is the current time
        processes[shortestJobIndex].completionTime = currentTime;

        // Waiting time is the difference between the completion time and the burst time
        processes[shortestJobIndex].waitingTime = processes[shortestJobIndex].completionTime - processes[shortestJobIndex].burstTime - processes[shortestJobIndex].arrivalTime;

        // Turnaround time is the sum of burst time and waiting time
        processes[shortestJobIndex].turnaroundTime = processes[shortestJobIndex].burstTime + processes[shortestJobIndex].waitingTime;

        // Accumulate the waiting time and turnaround time
        totalWaitingTime += processes[shortestJobIndex].waitingTime;
        totalTurnaroundTime += processes[shortestJobIndex].turnaroundTime;

        // Mark the process as completed
        processes[shortestJobIndex].burstTime = INT_MAX;
    }

    // Calculate the average waiting time and turnaround time
    averageWaitingTime = static_cast<float>(totalWaitingTime) / n;
    averageTurnaroundTime = static_cast<float>(totalTurnaroundTime) / n;
}

// Function to display the process details
void displayProcessDetails(Process processes[], int n) {
    cout << "\nProcess\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n";
    for (int i = 0; i < n; i++) {
        cout << processes[i].processId << "\t" << processes[i].arrivalTime << "\t\t" << processes[i].burstTime
             << "\t\t" << processes[i].completionTime << "\t\t" << processes[i].waitingTime << "\t\t"
             << processes[i].turnaroundTime << endl;
    }
}

int main() {
    int n; // Number of processes
    cout << "Enter the number of processes: ";
    cin >> n;

    Process* processes = new Process[n];

    // Input process details
    for (int i = 0; i < n; i++) {
        cout << "Process " << i + 1 << ":\n";
        processes[i].processId = i + 1;
        cout << "Enter arrival time: ";
        cin >> processes[i].arrivalTime;
        cout << "Enter burst time: ";
        cin >> processes[i].burstTime;
    }

    float averageWaitingTime, averageTurnaroundTime;
    calculateAverageTimes(processes, n, averageWaitingTime, averageTurnaroundTime);

    // Print the average waiting time and turnaround time
    cout << "\nAverage Waiting Time: " << averageWaitingTime << endl;
    cout << "Average Turnaround Time: " << averageTurnaroundTime << endl;

    // Display process details
    displayProcessDetails(processes, n);

    delete[] processes; // Deallocate memory

    return 0;
}
