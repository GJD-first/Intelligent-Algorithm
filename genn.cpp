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
#define N 10 //chromosome length
//Calculate the probability of each chromosome being selected
void select_pro()
{
	double sum=0;
	for(int i=0;i<N;i++)
	{
		sum+=adapt[i];
	}
	for(int i=0;i<N;i++)
	{
		select[i]=adapt[i]/sum;
	}
}
int main()
{
	return 0;
}