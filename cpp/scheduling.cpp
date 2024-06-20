#include <bits\stdc++.h>
#include <iostream>
#include <fstream>
#include <cstdlib> // For atoi
#define int long long
#define pii pair<int, int>
#define ppii pair<pii, int>
#define fi first
#define se second
#define inf 1e18
#define Not_Responsed -1
using namespace std;

const int N = 1e5 + 5;

int n, TQ;
int ArrivalTime[N], BurstTime[N], Priority[N], gantt[N], Response[N], SaveBurst[N];

void PrintResult(vector<int> order, int idleTime, ostream &os)
{
    int AT, BT, WT, TT, ST, FT, RT;
    int WT_sum = 0;
    int TT_sum = 0;
    for (int i = 0; i < n; i++)
    {
        int id = order[i];
        FT = gantt[id];
        AT = ArrivalTime[id];
        BT = BurstTime[id];
        RT = Response[id] - AT;
        TT = FT - AT;
        WT = TT - BT;
        WT_sum += WT;
        TT_sum += TT;
        os << "Process:P" << id + 1 << "  Finish Time: " << FT << "  Response Time: " << RT << "  Waiting Time: " << WT << "  Turnaround Time: " << TT << endl;
    }
    double avg_WT = WT_sum / (double)n;
    double avg_TT = TT_sum / (double)n;

    os << "\nAverage waiting time: " << avg_WT << endl;
    os << "Average Turnaround time: " << avg_TT << endl;
    os << "Idle Time: " << idleTime << endl;
}

void FindAverage(ostream &os)
{
    int AT, BT, WT, TT, ST, FT;
    int WT_sum = 0;
    int TT_sum = 0;
    for (int i = 0; i < n; i++)
    {
        FT = gantt[i];
        AT = ArrivalTime[i];
        BT = BurstTime[i];
        TT = FT - AT;
        WT = TT - BT;
        WT_sum += WT;
        TT_sum += TT;
    }
    double avg_WT = WT_sum / (double)n;
    double avg_TT = TT_sum / (double)n;
    os << "  \tAverage waiting time: " << avg_WT << "  \tAverage Turnaround time: " << avg_TT << endl;
}

void FCFS(bool cmp = false, ostream &os = cout)
{
     
    int curTime = 0, idleTime = 0, cnt = 0;
    int vis[n] = {};

    vector<int> order;
    priority_queue<pii> pq;

  
    os << "\nGantt Chart" << endl;
   do
   {
        if (pq.empty() == false)
          {  
            pii process = pq.top();
            pq.pop();
            int AT = -process.fi;
            int id = -process.se;
            int dur = BurstTime[id];

            if (Response[id] == Not_Responsed)
                Response[id] = curTime;

            curTime += dur;

            order.push_back(id);
            gantt[id] = curTime;

            os << curTime - dur << " P" << id + 1 << " ";
        }
        if (cnt != n)
        {
            bool got = 0;
            for (int i = 0; i < n; i++)
            {
                if (vis[i] == 0 && ArrivalTime[i] <= curTime)
                {
                    pii process = make_pair(-ArrivalTime[i], -i);
                    pq.push(process);
                    vis[i] = 1, got = 1;
                    cnt += 1;
                }
            }
            if (got == 0)
            {
                int mnAT = inf, mnID;
                for (int i = 0; i < n; i++)
                {
                    if (vis[i] == 0 && ArrivalTime[i] < mnAT)
                    {
                        mnAT = ArrivalTime[i];
                        mnID = i;
                    }
                }
                vis[mnID] = 1;
                cnt += 1;
                idleTime += mnAT - curTime;
                curTime = mnAT;

                pii process = make_pair(-mnAT, -mnID);
                pq.push(process);
            }
        }

    }while (!pq.empty());
    // cout<<"hello";
    // for(auto x:order){
    //       cout<<x;
    // }
    os << endl
        << endl;
    PrintResult(order, idleTime, os);
}

void SJF(bool cmp = false, ostream &os = cout)
{
    int curTime = 0, idleTime = 0, cnt = 0;
    int vis[n] = {};
    priority_queue<ppii> pq;
    vector<int> order;
    os << "\nGantt Chart:" << endl;
    do
    {   
        if (!pq.empty())
        {
            ppii process = pq.top();
            pq.pop();
            int AT = -process.fi.se;
            int BT = -process.fi.fi;
            int id = -process.se;

            if (Response[id] == Not_Responsed)
                Response[id] = curTime;

            curTime += BT;

            order.push_back(id);
            gantt[id] = curTime;

            os << curTime - BT << " P" << id + 1 << " ";
        }
        if (cnt != n)
        {
            int got = 0;
            for (int i = 0; i < n; i++)
            {
                if (vis[i] == 0 && ArrivalTime[i] <= curTime)
                {
                    ppii process = make_pair(pii(-BurstTime[i], -ArrivalTime[i]), -i);
                    pq.push(process);
                    vis[i] = 1, got = 1;
                    cnt += 1;
                }
            }
            if (got == 0)
            {
                int mnAT = 1e18, mnBT = 1e18, mnID;
                for (int i = 0; i < n; i++)
                {
                    if (vis[i])
                        continue;

                    if (ArrivalTime[i] < mnAT)
                    {
                        mnAT = ArrivalTime[i];
                        mnBT = BurstTime[i];
                        mnID = i;
                    }
                    else if (ArrivalTime[i] == mnAT)
                    {
                        if (BurstTime[i] < mnBT)
                        {
                            mnBT = BurstTime[i];
                            mnID = i;
                        }
                    }
                }
                vis[mnID] = 1;
                cnt += 1;
                idleTime += mnAT - curTime;
                curTime = mnAT;

                ppii process = make_pair(pii(-BurstTime[mnID], -mnAT), -mnID);
                pq.push(process);
            }
        }

    } while (!pq.empty());
    os << endl
        << endl;
    PrintResult(order, idleTime, os);
 
   
}

void SRTF(bool cmp = false, ostream &os = cout)
{
    int curTime = 0, idleTime = 0, cnt = 0;
    int vis[n] = {};
    priority_queue<ppii> pq;
    vector<int> order;
    
    os << "\nGantt Chart:" << endl;
    do
    {
        if (!pq.empty())
        {
            ppii process = pq.top();
            pq.pop();
            int AT = -process.fi.se;
            int BT = -process.fi.fi;
            int id = -process.se;
            int dur = (cnt != n) ? 1 : BT;

            if (Response[id] == Not_Responsed)
                Response[id] = curTime;

            curTime += dur;
            BT -= dur;

            if (BT != 0)
            {
                process = make_pair(pii(-BT, -AT), -id);
                pq.push(process);
            }
            else
            {
                order.push_back(id);
                gantt[id] = curTime;
            }
         
            os << curTime - dur << " P" << id + 1 << " ";
        }
        if (cnt != n)
        {
            int got = 0;
            for (int i = 0; i < n; i++)
            {
                if (vis[i] == 0 && ArrivalTime[i] <= curTime)
                {
                    ppii process = make_pair(pii(-BurstTime[i], -ArrivalTime[i]), -i);
                    pq.push(process);
                    vis[i] = 1, got = 1;
                    cnt += 1;
                }
            }
            if (got == 0)
            {
                int mnAT = 1e18, mnBT = 1e18, mnID;
                for (int i = 0; i < n; i++)
                {
                    if (vis[i])
                        continue;

                    if (ArrivalTime[i] < mnAT)
                    {
                        mnAT = ArrivalTime[i];
                        mnBT = BurstTime[i];
                        mnID = i;
                    }
                    else if (ArrivalTime[i] == mnAT)
                    {
                        if (BurstTime[i] < mnBT)
                        {
                            mnBT = BurstTime[i];
                            mnID = i;
                        }
                    }
                }
                vis[mnID] = 1;
                cnt += 1;
                idleTime += mnAT - curTime;
                curTime = mnAT;

                ppii process = make_pair(pii(-BurstTime[mnID], -mnAT), -mnID);
                pq.push(process);
            }
        }

    } while (!pq.empty());
    os << endl
        << endl;
    PrintResult(order, idleTime, os);
 
}

void Priority_Non_Preemptive(bool cmp = false, ostream &os = cout)
{
    int curTime = 0, idleTime = 0, cnt = 0;
    int vis[n] = {};
    priority_queue<ppii> pq;
    vector<int> order;
    
    os << "\nGantt Chart:" << endl;
    do
    {
        if (!pq.empty())
        {
            ppii process = pq.top();
            pq.pop();

            int Prio = -process.fi.fi;
            int AT = -process.fi.se;
            int id = -process.se;
            int BT = BurstTime[id];

            if (Response[id] == Not_Responsed)
                Response[id] = curTime;

            curTime += BT;

            order.push_back(id);
            gantt[id] = curTime;

            os << curTime - BT << " P" << id + 1 << " ";
        }
        if (cnt != n)
        {
            int got = 0;
            for (int i = 0; i < n; i++)
            {
                if (vis[i] == 0 && ArrivalTime[i] <= curTime)
                {
                    ppii process = make_pair(pii(-Priority[i], -ArrivalTime[i]), -i);
                    pq.push(process);
                    vis[i] = 1, got = 1;
                    cnt += 1;
                }
            }
            if (got == 0)
            {
                int mnAT = 1e18, HighPrio = inf, mnID;
                for (int i = 0; i < n; i++)
                {
                    if (vis[i])
                        continue;

                    if (ArrivalTime[i] < mnAT)
                    {
                        mnAT = ArrivalTime[i];
                        HighPrio = Priority[i];
                        mnID = i;
                    }
                    else if (ArrivalTime[i] == mnAT)
                    {
                        if (Priority[i] < HighPrio)
                        {
                            HighPrio = Priority[i];
                            mnID = i;
                        }
                    }
                }
                vis[mnID] = 1;
                cnt += 1;
                idleTime += mnAT - curTime;
                curTime = mnAT;

                ppii process = make_pair(pii(-HighPrio, -mnAT), -mnID);
                pq.push(process);
            }
        }

    } while (!pq.empty());

    os << endl
        << endl;
    PrintResult(order, idleTime, os);
    
    
}

void Priority_Preemptive(bool cmp = false, ostream &os = cout)
{
    for (int i = 0; i < n; i++)
        SaveBurst[i] = BurstTime[i];

    int curTime = 0, idleTime = 0, cnt = 0;
    int vis[n] = {};
    priority_queue<ppii> pq;
    vector<int> order;
    os << "\nGantt Chart:" << endl;
    do
    {
        if (!pq.empty())
        {
            ppii process = pq.top();
            pq.pop();

            int Prio = -process.fi.fi;
            int AT = -process.fi.se;
            int id = -process.se;
            int &BT = SaveBurst[id];

            int dur = (cnt != n) ? 1 : BT;

            if (Response[id] == Not_Responsed)
                Response[id] = curTime;

            curTime += dur;
            BT -= dur;

            if (BT != 0)
            {
                process = make_pair(pii(-Prio, -AT), -id);
                pq.push(process);
            }
            else
            {
                order.push_back(id);
                gantt[id] = curTime;
            }

            if (cmp == 0)
                os << curTime - dur << " P" << id + 1 << " ";
        }
        if (cnt != n)
        {
            int got = 0;
            for (int i = 0; i < n; i++)
            {
                if (vis[i] == 0 && ArrivalTime[i] <= curTime)
                {
                    ppii process = make_pair(pii(-Priority[i], -ArrivalTime[i]), -i);
                    pq.push(process);
                    vis[i] = 1, got = 1;
                    cnt += 1;
                }
            }
            if (got == 0)
            {
                int mnAT = 1e18, HighPrio = inf, mnID;
                for (int i = 0; i < n; i++)
                {
                    if (vis[i])
                        continue;

                    if (ArrivalTime[i] < mnAT)
                    {
                        mnAT = ArrivalTime[i];
                        HighPrio = Priority[i];
                        mnID = i;
                    }
                    else if (ArrivalTime[i] == mnAT)
                    {
                        if (Priority[i] < HighPrio)
                        {
                            HighPrio = Priority[i];
                            mnID = i;
                        }
                    }
                }
                vis[mnID] = 1;
                cnt += 1;
                idleTime += mnAT - curTime;
                curTime = mnAT;

                ppii process = make_pair(pii(-HighPrio, -mnAT), -mnID);
                pq.push(process);
            }
        }

    } while (!pq.empty());

   
    os << endl
        << endl;
    PrintResult(order, idleTime, os);
    

}

void RoundRobin(bool cmp = false, ostream &os = cout)
{
    for (int i = 0; i < n; i++)
        SaveBurst[i] = BurstTime[i];

    int curTime = 0, idleTime = 0, cnt = 0;
    int vis[n] = {};

    queue<int> q;
    vector<int> order;

    os << "\nGantt Chart" << endl;
    while (!q.empty() || cnt != n)
    {
        if (!q.empty())
        {
            int id = q.front();
            q.pop();

            int &BT = SaveBurst[id]; // remaining burst time ekhane thakbe
            int dur = (TQ < BT) ? TQ : BT;

            if (Response[id] == Not_Responsed)
                Response[id] = curTime;

            curTime += dur;
            BT -= dur;
            if (cnt != n)
            {
                for (int i = 0; i < n; i++)
                {
                    if (vis[i] == 0 && ArrivalTime[i] <= curTime)
                    {
                        q.push(i);
                        vis[i] = 1;
                        cnt += 1;
                    }
                }
            }
            if (BT != 0)
                q.push(id);
            else
            {
                order.push_back(id);
                gantt[id] = curTime;
            }
           
            os << curTime - dur << " P" << id + 1 << " ";
        }
        else
        {
            int mnAT = 1e18, mnID;
            for (int i = 0; i < n; i++)
            {
                if (vis[i])
                    continue;

                if (ArrivalTime[i] < mnAT)
                {
                    mnID = i;
                    mnAT = ArrivalTime[i];
                }
            }
            vis[mnID] = 1;
            cnt += 1;
            idleTime += mnAT - curTime;
            curTime = mnAT;
            q.push(mnID);
        }
    }
   
    os << endl
        << endl;
    PrintResult(order, idleTime, os);
    
   
}

int Calculate_TQ()
{
    int Asum = 0, mxBurst = 0;
    double Hsum = 0;
    for (int i = 0; i < n; i++)
    {
        mxBurst = max(mxBurst, BurstTime[i]);
        Asum += BurstTime[i];
        Hsum += 1.0 / BurstTime[i];
    }
    double Amean = Asum / n;
    double Hmean = n / Hsum;
    int TQ = ceil((Amean + Hmean + mxBurst) / 3.0);
    return TQ;
}

int32_t main()
{

    int option;
    const char* inputFileName = "C:/Users/lenovo/Desktop/cpu_scheduler/php/input.txt";
    const char* outputFileName = "C:/Users/lenovo/Desktop/cpu_scheduler/php/output.txt";

    ifstream inputFile(inputFileName);
    if (!inputFile) {
        cerr << "Error: Could not open input file " << inputFileName << "\n";
        return 1;
    }

    ofstream outputFile(outputFileName);
    if (!outputFile) {
        cerr << "Error: Could not open output file " << outputFileName << "\n";
        return 1;
    }
    inputFile >> option;
    inputFile >> n;
    if (option < 4 || option == 6)
	{
       for (int i = 0; i < n; i++) {
        inputFile >> ArrivalTime[i] >> BurstTime[i];
        SaveBurst[i] = BurstTime[i];
        Response[i] = -1;
       }

    }else{
        for (int i = 0; i < n; i++)
           {
        inputFile >> ArrivalTime[i] >> BurstTime[i] >> Priority[i];
        SaveBurst[i] = BurstTime[i];
        Response[i] = -1;
            }
    }

    if (option == 6 || option == 7)
    {
        inputFile >> TQ;
    }

    switch (option)
    {
        case 1: FCFS(false, outputFile);  break;
        case 2: SJF(false, outputFile); break;
        case 3: SRTF(false, outputFile); break;
        case 4: Priority_Non_Preemptive(false, outputFile); break;
        case 5: Priority_Preemptive(false, outputFile); break;
        case 6: RoundRobin(false, outputFile); break;
        case 7:
            for (int i = 1; i <= 7; i++)
            {
                outputFile << "Algorithm: " << i << endl;
                switch (i)
                {
                    case 1: FCFS(true, outputFile); break;
                    case 2: SJF(true, outputFile); break;
                    case 3: SRTF(true, outputFile); break;
                    case 4: Priority_Non_Preemptive(true, outputFile); break;
                    case 5: Priority_Preemptive(true, outputFile); break;
                    case 6: RoundRobin(true, outputFile); break;
                    case 7: Proposed(true, outputFile); break;
                }
            }
            break;
        default: cerr << "Error: Invalid algorithm option.\n"; return 1;
    }
    inputFile.close();
    outputFile.close();

    return 0;
}
