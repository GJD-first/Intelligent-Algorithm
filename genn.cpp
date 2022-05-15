/*
author:guojiadong
date:2022-05-15
description:Implementing Genetic Algorithms
*/
#include<boost/numeric/ublas/vector.hpp>
#include<boost/numeric/ublas/io.hpp>
#include<cstring>
#include<cstdlib>
//using namespace std;
using namespace boost::numeric::ublas;
#define N 10 //gene length
#define individual 100//number of individuals
#define iter 1000//number of iterations
#define cp 0.2//copy rate
vector<double> select(individual);//selection probability
vector<double> adapt(individual);//adaptability
//Calculate the probability of each chromosome being selected
void select_pro()
{
	double sum=0;
	for(int i=0;i<individual;i++)
	{
		sum+=adapt[i];
	}
	for(int i=0;i<individual;i++)
	{
		select[i]=adapt[i]/sum;
	}
}
//Copy the best individual
void copy()
{
	
}
int main()
{
	return 0;
}