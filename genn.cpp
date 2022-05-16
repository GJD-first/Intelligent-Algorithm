/*
author:guojiadong
date:2022-05-15
description:Implementing Genetic Algorithms
use this program to get max value of y=-x*x+10*x+32 with x in range [0,10]
*/
#include<bits/stdc++.h>
using namespace std;
#define N 4 //gene length
#define individual 100//number of individuals
#define iter 1000//number of iterations
#define cp 0.2//copy rate
#define variation 0.008
#define ex 0.8//change rate
vector<int> adapt(individual);//adaptability
vector<vector<int>> population(individual,vector<int>(N));//the population of each generation
void calc_adapt(int id)
{
    adapt[id]=0;
    for(int j=0;j<N;j++)
    {
        adapt[id]=adapt[id]*2+population[id][j];
    }
    adapt[id]=-adapt[id]*adapt[id]+10*adapt[id]+32;
}
void init()
{
    srand(time(0));
    for(int i=0;i<individual;i++)
    {
        for(int j=0;j<N;j++)
        {
            population[i][j]=rand()%2;
        }
    }
    for(int i=0;i<individual;i++)
        calc_adapt(i);
}
void change()
{
    int num=individual*ex;
    if(num%2!=0)num--;
    vector<double> need(num);
    vector<double> rate(individual);
    vector<int> select(num);
    rate[0]=adapt[0];
    for(int i=1;i<individual;i++) {
        rate[i] = rate[i - 1] + adapt[i];
    }
    for(int i=0;i<individual;i++)
    {
        rate[i]/=rate[individual-1];
    }
    for(int i=0;i<num;i++)
    {
        need[i]=1.*rand()/RAND_MAX;
    }
    sort(need.begin(),need.end());
    int j=0,k=0;
    while(j<num)
    {
        if(rate[k]>=need[j])
        {
            select[j]=k;
            j++;
        }
        else {
            k++;
        }
    }
    j=0,k=num-1;
    while(j<k)
    {
        int idx=rand()%N,idy=rand()%N;
        if(idx<idy)
        {
            int idz=idx;
            idx=idy;
            idy=idz;
        }
        for(int i=idx;i<=idy;i++)
        {
            int temp=population[select[j]][i];
            population[select[j]][i]=population[select[k]][i];
            population[select[k]][i]=temp;
        }
        calc_adapt(select[j]);
        calc_adapt(select[k]);
        j++;
        k--;
    }
}
//copy the best individual and delete the worst individual
void copy()
{
    //pair: fitness,number
    int num=individual*cp;
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<>> best;
    priority_queue<pair<int,int>> worst;
    for(int i=0;i<individual;i++)
    {
        if(i<num)
        {
            best.push(make_pair(adapt[i],i));
            worst.push(make_pair(adapt[i],i));
        }
        else
        {
            if(adapt[i]>best.top().first)
            {
                best.pop();
                best.push(make_pair(adapt[i],i));
            }
            if(adapt[i]<worst.top().first)
            {
                worst.pop();
                worst.push(make_pair(adapt[i],i));
            }
        }
    }
    for(int i=0;i<num;i++)
    {
        int j=best.top().second,k=worst.top().second;
        population[k].assign(population[j].begin(),population[j].end());
        adapt[k]=adapt[j];
        best.pop();
        worst.pop();
    }
}
void mutations()
{
	srand(time(0));
	for(int i=0;i<individual;i++)
	{
		double rate=1.*rand()/RAND_MAX;
		if(rate<=variation)
		{
			int pos=rand()%N;
			population[i][pos]^=1;
            calc_adapt(i);
		}
	}
}
int getSum()
{
    int sum=0;
    for(int i=0;i<individual;i++)
    {
        sum=max<int>(sum,adapt[i]);
    }
    return sum;
}
int main()
{
    init();
    for(int i=0;i<iter;i++) {
        copy();
        change();
        mutations();
    }
	return 0;
}