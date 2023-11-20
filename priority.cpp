#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Process
{
    public:
        string id;
        int arrTime;
        int burstTime;
        int compTime;
        int turnTime;
        int waitTime;
        int priority;

        Process()
        {
            arrTime = 0;
            burstTime = 0;
            compTime = 0;
            turnTime = 0;
            waitTime = 0;
            priority = 0;
        }

        Process(string id , int art , int brt , int priority)
        {
            this->id = id;
            arrTime = art;
            burstTime = brt;
            turnTime = 0;
            waitTime = 0;
            this->priority = priority;
        }

        bool operator<(const Process &other) const{
            return priority > other.priority;
        }

};

bool comparator(Process p1, Process p2)
{
    return p1.arrTime < p2.arrTime;
}

class Priority
{
    public:
        vector<Process> proclst;
        int n;
        Priority()
        {
            cout<<"\nEnter number of process: ";
            cin>>n;
            string id;
            int art , brt , priority;
            for(int i=0;i<=n-1;i++)
            {
                cout<<"\nEnter id: ";
                cin>>id;
                cout<<"\nEnter arrival Time for "<<id<<": ";
                cin>>art;
                cout<<"\nEnter burst Time for "<<id<<": ";
                cin>>brt;
                cout<<"\nEnter priority for "<<id<<" : ";
                cin>>priority;

                Process P(id,art,brt , priority);
                proclst.push_back(P);
            }
        }


        void compTime()
        {
            int currTime = 0;
            vector<Process> temp;
            priority_queue<Process> q;

            sort(proclst.begin(),proclst.end(),comparator);

            while(!q.empty() || !proclst.empty())
            {
                while(!proclst.empty() && proclst.front().arrTime <= currTime)
                {
                    q.push(proclst.front());
                    proclst.erase(proclst.begin());
                    
                }

                if(!q.empty())
                {
                    Process p = q.top();
                    q.pop();

                    currTime += p.burstTime;
                    p.compTime = currTime;
                    temp.push_back(p);
                    // cout<<p.id<<" ";
                }
                else
                {
                    currTime++;
                }
            }
            proclst = temp;
        }
        

        void calTurnTime()
        {
            for(int i=0;i<=n-1;i++)
            {
                proclst[i].turnTime = proclst[i].compTime - proclst[i].arrTime;
            }
        }

        void calWaitTime()
        {
            for(int i=0;i<=n-1;i++)
            {
                proclst[i].waitTime = proclst[i].turnTime - proclst[i].burstTime;
            }
        }

        void display(){
            cout<<"id\tat\tbt\tct\twt\ttat"<<endl;
            for(auto i:proclst){
                cout<<i.id<<"\t"<<i.arrTime<<"\t"<<i.burstTime<<"\t"<<i.compTime<<"\t"<<i.waitTime<<"\t"<<i.turnTime<<endl;
            }
        }
};

int main()
{
    Priority pr;
    pr.compTime();
     pr.calTurnTime();
    pr.calWaitTime();
   
    cout<<endl;
    // cout<<"\nHello world";
    pr.display();
}

// p1 0 8 3 p2 1 2 4 p3 3 4 4 p4 4 1 5 p5 5 6 2 p6 6 5 6 p7 10 1 1