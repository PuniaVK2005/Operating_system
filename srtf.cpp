#include <iostream>
#include <climits>
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

void findWaitingTime(Process proc[], int n) {
    int complete = 0, time = 0, minm = INT_MAX;
    int shortest = 0, finish_time;
    bool check = false;

   
    while (complete != n) {
      
        for (int j = 0; j < n; j++) {
            if ((proc[j].arrivalTime <= time) &&
                (proc[j].remainingTime < minm) && proc[j].remainingTime > 0) {
                minm = proc[j].remainingTime;
                shortest = j;
                check = true;
            }
        }

        if (check == false) {
            time++;
            continue;
        }

    
        proc[shortest].remainingTime--;


        minm = proc[shortest].remainingTime;
        if (minm == 0)
            minm = INT_MAX;


        if (proc[shortest].remainingTime == 0) {
            complete++;
            check = false;

            finish_time = time + 1;


            proc[shortest].waitingTime =
                finish_time - proc[shortest].burstTime -
                proc[shortest].arrivalTime;

            if (proc[shortest].waitingTime < 0)
                proc[shortest].waitingTime = 0;
        }
        time++;
    }
}

void findTurnaroundTime(Process proc[], int n) {
    for (int i = 0; i < n; i++)
        proc[i].turnaroundTime = proc[i].burstTime + proc[i].waitingTime;
}

void findAverageTime(Process proc[], int n) {
    findWaitingTime(proc, n);
    findTurnaroundTime(proc, n);

    cout << "Processes " << " Arrival Time " << " Burst Time "
         << " Waiting Time " << " Turnaround Time\n";

    int totalWaitingTime = 0, totalTurnaroundTime = 0;
    for (int i = 0; i < n; i++) {
        totalWaitingTime += proc[i].waitingTime;
        totalTurnaroundTime += proc[i].turnaroundTime;
        cout << " " << proc[i].pid << "\t\t"
             << proc[i].arrivalTime << "\t\t"
             << proc[i].burstTime << "\t\t"
             << proc[i].waitingTime << "\t\t "
             << proc[i].turnaroundTime << endl;
    }

    cout << "\nAverage waiting time = "
         << (float)totalWaitingTime / n;
    cout << "\nAverage turnaround time = "
         << (float)totalTurnaroundTime / n;
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    Process proc[n];
    for (int i = 0; i < n; i++) {
        cout << "Enter arrival time and burst time for process " << i + 1 << ": ";
        cin >> proc[i].arrivalTime >> proc[i].burstTime;
        proc[i].pid = i + 1;
        proc[i].remainingTime = proc[i].burstTime;
    }

    findAverageTime(proc, n);
    return 0;
}
