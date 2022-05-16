# Intelligent-Algorithm

---

> 本程序只实现最基础的接口与函数的编写
>
> 具体问题需要做适当修改

### 头文件

```c++
#include<bits/stdc++.h>
```

> 对不支持万能头文件的编译器，主要引入下面几个头文件

```c++
#include<iostream>
#include<cstdio>
#include<ctime>
#include<vector>
#include<queue>
#include<cstdlib>
#include<utility>
#include<algorithm>
```



### 变量简介

> N：染色体上基因数
>
> individual：个体数
>
> iter：迭代次数
>
> cp：复制率
>
> variation：变异率
>
> ex：交叉互换率
>
> adapt：每条染色体的适应度
>
> population：当代种群

```c++
#define N 10
#define individual 100
#define iter 1000
#define cp 0.2
#define variation 0.008
#define ex 0.8
vector<double> adapt(individual);
vector<vector<int>> population(individual,vector<int>(N));
```

---

### 编码

> 对于求解单个变量的最值问题：采用二进制编码
>
> 类TSP问题：采用排列编码
>
> 方案选择问题：二进制编码
>
> 多变量整数规划问题：整数编码  给出上限值

本文以求解**y=-x\*x+10\*x+32**在**[0,10]**上的最大值为例给出基本模板

```c++
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
}
```

---

### 计算每个个体的适应度

> 计算该代种群中，每一个个体的适应度
>
> 该函数对adapt完成赋值，根据待求解的问题确定

```c++
void calc_adapt(int id)
{
    adapt[id]=0;
    for(int j=0;j<N;j++)
    {
        adapt[id]=adapt[id]*2+population[id][j];
    }
    adapt[id]=-adapt[id]*adapt[id]+10*adapt[id]+32;
}
```

---

### 复制算子

> 使得一定数量的最好的个体复制，最差的个体消亡
>
> num：保留的个体数，由个体总数×复制率得出
>
> worst：大根堆，记录适应度最差的num个个体
>
> best：小根堆，记录适应度最好的num个个体

```c++
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
```

---

### 交叉互换算子

> 利用轮盘赌选择出需要进行交叉互换的个体
>
> 在随机的区间进行交叉互换

```c++
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
```



---

### 变异算子

> rate：小于等于变异率时该个体发生变异，否则不发生变异
>
> 采用单点突变的方法，变异基因的位置随机确定

```c++
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
```



---

### 调用

> 首先初始化种群，然后每次迭代按以下顺序进行
>
> 染色体复制--交叉互换--变异

```c++
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
```

