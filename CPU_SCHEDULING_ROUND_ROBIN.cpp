#include<iostream>
#include<conio.h>
#include<stdlib.h>
#include<iomanip>
#include<queue>

using namespace std;


void order(int pro_name , int t);          //shows processes in the order of execution
void swap (int &a , int &b);                    

int main ()  
{
	cout<<"--------------------------------------------------> WELCOME TO CPU SCHEDULING SIMULATION <--------------------------------------------------\n"
	    <<"-------------------------------------------------->        ROUND-ROBIN SCHEDULING        <--------------------------------------------------\n\n"
        <<"Press any key to continue...";

    cin.get();
   
    int num;


here:cout<<("\e[1;1H\e[2J");
	cout << "How many processes are there : ";
	cin >> num;
	
	queue <int> ready;
	int process[num];
	int processNew[num];
	int processSyn[num];
	int priority[num];
	int arrival[num];
	int arrivalNew[num];
	int burst[num];
	int burstNew[num];
	int tot = 0;

	
	for (int var = 0 ; var < num ; ++var)  
	{	
		cout << "Enter the Process Priority : ";
		cin >> priority[var];
		
		cout << "Enter the Process Arrival time : ";
		cin >> arrival[var];
		
		cout << "Enter the process Burst time : ";
		cin >> burst[var];
		
		tot += burst[var];
		
	    processSyn[var]= var;
	    process[var] = var;
		burstNew[var] = burst[var];
		
		cout<<"\n\n";
	}
	
	
	int check = 0;
	
	
	for (int start : priority)  
	{	
		if (start == 0 )  {
			check = 1;
			break;
		}	
	}
	
	if ( !check )  
	{	
		cout<<"\n\nThere must be a process with zero priority";
		cout<<"Enter any key to continue";
		cin.get();
		goto here;
	}
	
	
	for (int m = 0 ; m < num ; ++m)
		for (int k = 0 ; k < num-1 ; ++k)  
		{
			if(priority[k] < priority[k+1])  
			{      
			  swap(processSyn[k] , processSyn[k+1]);  
			  swap(burstNew[k] , burstNew[k+1]);
			  swap(priority[k] , priority[k+1]);
		      swap(arrival[k] , arrival[k+1]);
			  swap(burst[k] , burst[k+1]);	
			}
						
		}	
	
	for (int k = 0 ; k < num ; ++k) 
	{		
			arrivalNew[k] = arrival[k];		
			processNew[k] = process[k];
	}
	
	int qtm;	
	cout << "Time quantum? :  ";
	cin>>qtm;
	
	
	int k =0;
	
	for (int m = 0 ; m < num ; ++m)
	for (int k = 0 ; k < num-1 ; ++k)  
	{		
		if (arrivalNew[k] > arrivalNew[k+1]) 
		{
			swap(arrivalNew[k] ,arrivalNew[k+1]);
			swap(processNew[k] , processNew[k+1]);		
		}
	}

	cout<<"\n";
	
	int token;
	int z =1;
	int primeTime = arrivalNew[0];
	int checkpoint = 1;
	int waitingTime[num];
	
	ready.push(processNew[0]);	
	cout<<endl<<endl;
	
	while (tot != primeTime)  
	{	
     	if (burst[ready.front()] > qtm)  
     	{
			burst[ready.front()] -= qtm;
			primeTime += qtm;
			order(processSyn[ready.front()] , qtm);
			checkpoint = 3;
		}
		
	    else if (burst[ready.front()] == qtm) 
	    {
			burst[ready.front()] = 0;	
			primeTime += qtm;
			order(processSyn[ready.front()] , qtm);
			checkpoint = 2;
			waitingTime[ready.front()] = primeTime;
			ready.pop();
		}
		
		
		else {
			primeTime += burst[ready.front()];
			order(processSyn[ready.front()] , burst[ready.front()]);
			burst[ready.front()] = 0;
		
			checkpoint = 2;
			waitingTime[ready.front()] = primeTime;
			ready.pop();	
		}
		
	
		for ( ; z < num ; ++z)  
		{	
			if (primeTime >= arrivalNew[z])
				ready.push(processNew[z]);
			else break;
		} 
		
		
		if (checkpoint == 3)  
		{
			ready.push(ready.front());   
			ready.pop();			
		}
	
	}
  
  	cout <<  "\n\n\n\nProcess   " << setw(15) << right << "Priority" << setw(15) << right << "Arrival time"  << setw(15) << right << "Burst time"  << setw(15) << right << "Waiting time" << setw(20) << right << "Turnaround time"<<endl<<endl;
  
	
	for (int l = 0 ; l < num ;++l) 
	{
		cout <<  "P"  <<processSyn[l] << setw(18) << right << priority[l] << setw(15) << right << arrival[l]  << setw(15) << right << burstNew[l]  << setw(15) << right << (waitingTime[l]-arrival[l])-burstNew[l] << setw(20) << right << (waitingTime[l]-arrival[l]) <<"\n\n";	
	}
	
	
}


void swap (int &a , int &b)
{
	a = a+b;
	b = a-b;
	a = a-b;
}

void order(int pro_name , int t)
{
	for(int var = 0 ; var < t ; ++var )
		cout << 'P'<< pro_name << "->";
}