## 标准模板库 priority_queue 优先队列
priority_queue是queue的变种，它与queue的不同在于**priority_queue具有排序的功能，默认从大到小排序，即顶端元素最大，尾端元素最小。**    
因此，priority中存放的元素类型，需要支持小于号，如果是自定义类型则需要进行小于号重载。   
如果需要调整排序的逻辑，则需要在第三个参数加入compare函数。  
priority_queue的第一第二个参数与queue相同，第一个参数为所存放的元素的类型，第二个参数为使用的容器，默认使用的容器为vector。  
### 头文件支持
```c
#include <queue>  
```  
虽然模板类型名不同，但是头文件与queue相同。   
### 初始化
```c
priority_queue<int> pq;	//使用一个参数默认初始化，只指定存储的元素是类型，默认使用vector作为里容器，默认从大到小排列   
priority_queue<int, list<int>> pql; //使用两个参数默认初始化，指定存储的元素类型及使用的里容器，默认从大到小排列     
priority_queue<int, vector<int>, greater<int>> pqvg;	//使用三个参数进行初始化，指定存储元素类型及使用的里容器，以及使用STL里面定义了一个仿函数 greater<>来从小到大排列 头元素为最大     

priority_queue<int> qq(pq);	//也可以使用其他优先队列来初始化自己，但是要保证他们的模式一致   
```   
相比queue，priority_queue的参数要多一个，为三个，因此初始化也较为复杂一些。  
前两个与之前一致，来决定存储元素的类型以及使用的里容器。   
当没有指定容器参数的时候，默认使用vector作为特定容器。当我们使用其它容器作为特定容器的时候，该容器必须包含以下函数：   
empty();    
size();   
front();	   
push\_back();    
pop\_front();       
在标准容器中，deque、vector都满足这些要求。   
第三个参数为一个仿函数，由于第三个参数的需求为一个类，因此直接用比较函数无法成功初始化，需要使用仿函数，仿函数可以自己设计。   
以下做一个从大到小的排列，头元素为最小。   
```c
class small  
{    
public:  
	bool operator()(int a, int b)  
	{  
		return a > b;  
	}  
};   

int main()  
{   
	priority_queue<int, vector<int>, small> uu;  
	uu.push(10);  
	uu.push(70);  
	uu.push(1);  
	uu.push(100);  

	cout << uu.top();	//1  
	getchar();  
	return 0;   
}  
```   
### 添加元素
```c
priority_queue<int> pq;
pq.push(10);	//添加元素到尾端，会进行自动排列  
pq.emplace(10);	//直接构造元素在尾端，会进行自动排列  
```  
emplace相关函数是c++11新推出的函数，emplace相关函数则是直接把元素传递给该元素的构造函数，在相关位置直接进行构造。因此emplace的效率是高于一般的插入元素的函数的。   
添加元素与queue基本没有区别。  
### 删除元素  
```c
pq.pop();	//删除顶端元素，先进先出的原则   
```  
尽管先进先出的原则在这里变种了，由于排列，实际先出是最大（或者自定义过的特定）的值。   
### 功能函数
常用函数如下    
priority_queue<int> pq;  
pq.empty();	//返回pq是否为空  
pq.size();	//返回pq的大小  
pq.top();	//返回pq的头元素     
pq.swap(pq1);	//交换两个优先队列的元素    
比queue缺少一个返回尾端元素的功能，其它基本一致。  
### 迭代以及遍历
不支持迭代和遍历。  
### 总结  
queue可以返回顶端元素和尾端元素，但是priority_queue只能返回顶端元素。   
可以看到priority_queue的使用场景，当我们需要一个简单的队列，可以按照我们的想法进行排序，同时随时可以访问顶端（最大或者最小）的元素，那么可以使用这个容器适配器，优先队列。    
**ps 我觉得它最大的有点在于排序。**  