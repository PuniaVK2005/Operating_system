#include <iostream>
#include <queue>
using namespace std;

struct Process {
    int pid;         
    int arrivalTime; 
    int burstTime;   
    int remainingTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
};


void roundRobinScheduling(Process proc[], int n, int quantum) {
    queue<int> readyQueue;
    int currentTime = 0;
    int completedProcesses = 0;

 
    for (int i = 0; i < n; i++) {
        proc[i].remainingTime = proc[i].burstTime;
    }


    readyQueue.push(0);
    int index = 1;

    while (completedProcesses < n) {
       
        int currentProcess = readyQueue.front();
        readyQueue.pop();

        
        int timeSlice = min(quantum, proc[currentProcess].remainingTime);
        proc[currentProcess].remainingTime -= timeSlice;
        currentTime += timeSlice;

        while (index < n && proc[index].arrivalTime <= currentTime) {
            readyQueue.push(index);
            index++;
        }

  
        if (proc[currentProcess].remainingTime > 0) {
            readyQueue.push(currentProcess);
        } else {
          
            completedProcesses++;
            proc[currentProcess].completionTime = currentTime;
            proc[currentProcess].turnaroundTime = currentTime - proc[currentProcess].arrivalTime;
            proc[currentProcess].waitingTime = proc[currentProcess].turnaroundTime - proc[currentProcess].burstTime;
        }

    
        if (readyQueue.empty() && index < n) {
            readyQueue.push(index);
            currentTime = proc[index].arrivalTime;
            index++;
        }
    }
}


void findAverageTime(Process proc[], int n, int quantum) {
    roundRobinScheduling(proc, n, quantum);

    int totalWaitingTime = 0, totalTurnaroundTime = 0;
    cout << "Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n";

    for (int i = 0; i < n; i++) {
        totalWaitingTime += proc[i].waitingTime;
        totalTurnaroundTime += proc[i].turnaroundTime;

        cout << proc[i].pid << "\t" << proc[i].arrivalTime << "\t\t"
             << proc[i].burstTime << "\t\t" << proc[i].waitingTime << "\t\t"
             << proc[i].turnaroundTime << endl;
    }

    cout << "\nAverage Waiting Time: " << (float)totalWaitingTime / n;
    cout << "\nAverage Turnaround Time: " << (float)totalTurnaroundTime / n << endl;
}

int main() {
    int n, quantum;

  
    cout << "Enter the number of processes: ";
    cin >> n;

    Process proc[n];
    
   
    for (int i = 0; i < n; i++) {
        cout << "Enter arrival time and burst time for process " << i + 1 << ": ";
        cin >> proc[i].arrivalTime >> proc[i].burstTime;
        proc[i].pid = i + 1;
    }

  
    cout << "Enter the time quantum: ";
    cin >> quantum;

    findAverageTime(proc, n, quantum);

    return 0;
}
