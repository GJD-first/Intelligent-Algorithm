# Intelligent-Algorithm

---

> 本程序只实现最基础的接口与函数的编写
>
> 具体问题需要做适当修改

---

使用本程序前 请确保安装boost  并修改**Makefile**中库文件和头文件的搜索路径

```c++
#include<boost/numeric/ublas/vector.hpp>
#include<boost/numeric/ublas/io.hpp>
```

> -I指定头文件搜索路径
>
> -L指定库文件搜索路径

```makefile
gene:genn.cpp
	g++ genn.cpp -o gene -I../vcpkg-master/vcpkg-master/installed/x64-windows/include -L-I../vcpkg-master/vcpkg-master/installed/x64-windows/lib
```

---

### 变量简介

> iter：迭代次数
>
> individual：个体数
>
> N：染色体上基因数
>
> cp：复制率
>
> adapt：每条染色体的适应度
>
> select：每条染色体被选择的概率     该条染色体的适应度越大，被选择的概率越大

```c++
#define N 10
#define individual 100
#define iter 1000
#define cp 0.2
vector<double> select(individual);
vector<double> adapt(individual);
```



---

### 计算每个个体的适应度

> 计算该代种群中，每一个个体的适应度
>
> 该函数对adapt完成赋值，根据待求解的问题确定

```c++
void calc_adapt()
{
	for(int i=0;i<individual;i++)
	{
	}
}
```



---

### 计算每条染色体自然选择的概率

> 计算每条染色体被选择的概率
>
> sum：通过adapt累加获得总适应度
>

```c++
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
```

---

### 交叉互换算子

---

### 变异算子

---

### 复制算子

---

