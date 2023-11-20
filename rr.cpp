#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Process
{
    public:
        string id;
        int arrTime;
        int burstTime;
        int turnTime;
        int waitTime;
        int compTime;
        int remTime;

        Process()
        {
            arrTime = 0;
            burstTime = 0;
            turnTime = 0;
            waitTime =0;
            compTime = 0;
            remTime = 0;
        }

        Process(string st , int art , int brt)
        {
            id = st;
            arrTime = art;
            burstTime = brt;
            turnTime = 0;
            waitTime = 0;
            compTime = 0;
            remTime = brt;

        }

        bool operator<(const Process& other) const {
            return remTime > other.remTime;
        }
};

bool comparator(Process p1 ,Process p2)
{
    return p1.arrTime<p2.arrTime;
}

class rr
{
    vector<Process> procLst;
    public:
        int n;
        rr()
        {
            cout<<"\nEnter number of process: ";
            cin>>n;
            string st ; int art , brt;
            for(int i=0;i<=n-1;i++)
            {
                cout<<"\nEnter id: ";
                cin>>st;
                cout<<"\nEnter arrival time for "<<st<<" : ";
                cin>>art;
                cout<<"\nEnter burst time for: "<<st<<" : ";
                cin>>brt;

                Process p(st , art , brt);
                procLst.push_back(p);
            }
        }

        void calCompleteTime()
        {
            queue<Process> q;
            vector<Process> temp;

            cout<<"\nEnter time quantum: ";
            int qt;cin>>qt;

            int curTime = 0;

            sort(procLst.begin(),procLst.end(),comparator);

            while(!q.empty() || !procLst.empty())
            {
                while (!procLst.empty() && procLst.front().arrTime<= curTime)
                {
                    /* code */
                    q.push(procLst.front());
                    procLst.erase(procLst.begin());
                }

                if(!q.empty())
                {
                    Process p = q.front();
                    q.pop();

                    int exeTime = min(p.remTime , qt);
                    curTime += exeTime;
                    p.remTime -= exeTime;
                    // cout<<curTime<<" ";
                    if(p.remTime > 0)
                    {
                        while (!procLst.empty() && procLst.front().arrTime<= curTime)
                        {
                    /* code */
                            q.push(procLst.front());
                            procLst.erase(procLst.begin());
                        }
                        q.push(p);
                    }
                    else
                    {
                         p.compTime = curTime;
                        temp.push_back(p);
                       
                    }
                    // cout<<p.compTime<<" ";

                }
                else
                {
                    curTime++;
                }

            }

            procLst = temp;

        }

        void calTurnTime()
        {
            for(int i=0;i<=n-1;i++)
            {
                procLst[i].turnTime = procLst[i].compTime - procLst[i].arrTime;
            }
        }

        void calWaitTime()
        {
            for(int i=0;i<=n-1;i++)
            {
                procLst[i].waitTime = procLst[i].turnTime - procLst[i].burstTime;
            }
        }

        void display(){
            cout<<"id\tat\tbt\tct\twt\ttat"<<endl;
            for(auto i:procLst){
                cout<<i.id<<"\t"<<i.arrTime<<"\t"<<i.burstTime<<"\t"<<i.compTime<<"\t"<<i.waitTime<<"\t"<<i.turnTime<<endl;
            }
        }

};

int main()
{
    rr sch;
    sch.calCompleteTime();
    sch.calTurnTime();
    sch.calWaitTime();
    sch.display();
}

// p1 0 8 p2 5 2 p3 1 7 p4 6 3 p5 8 5