## 标准库模板 queue 队列
queue是标准库的一种**容器适配器**。（与stack类似）   
它不只是一种容器，而是封装了一个类作为他的特定容器，提供了一组成员函数去访问该容器的元素。   
在默认的情况下queue使用deque队列作为自己的特定容器，当然我们也可以使用其它的容器如deque，list等。   
stack的访问顺序，以“后进先出（first-in first-out)”为特点。（相似的，stack的特性为后进先出（last-in first-out））     
因此当我们需要使用一种容器，其访问顺序为先进先出的，那么我们可以使用queue。    
### 头文件支持
```c
#include <queue>   
```  
### 初始化  
```c
queue<int> q;	//省略模板参数，默认以deque作为特定模板。     
queue<int, vector<int>> qv;	//使用vector作为特定模板    
queue<int, list<int>> ql;	//使用list作为特定模板    

queue<int> qq(q);	//使用q来初始化qq     
```  
相比正常的容器如vector、list，queue作为容器适配器，它的初始化方式也比较少，比较简单。   
当没有指定容器参数的时候，默认使用deque作为特定容器。当我们使用其它容器作为特定容器的时候，该容器必须包含以下函数：   
empty();    
size();   
front();	
back();    
push\_back();    
pop\_front();       
在标准容器中，deque、vector和list都满足这些要求。   
### 添加元素
```c
queue<double> qq;   
qq.push(1.25);		//将1.25添加到queue的末端   
qq.emplace(6.5);	//将6.5直接构造在queue的末端  
```  
emplace相关函数是c++11新推出的函数，emplace相关函数则是直接把元素传递给该元素的构造函数，在相关位置直接进行构造。因此emplace的效率是高于一般的插入元素的函数的。   
queue添加元素的函数也比较简单，它只能从尾部进行添加（不过只能从头部删除元素）。   
> 注意并不是push_back，尽管是从尾部添加，但是尾部添加为queue特性，因此只是push函数。   
### 删除元素
```c
qq.pop();	//从头部删除元素  
```  
弹出（删除）头部的元素，并且queue也只能从头部删除元素。   
不存在批量删除，贯彻先进先出。   
> 注意 并不是pop_front，由于从头部弹出为queue的特性，所以只是pop函数。   
### 功能函数
queue作为迭代器适配器，功能函数也比较有限，如下：   
queue<int> qq;  
qq.back();	//返回尾部元素  
qq.front();	//返回头部元素  
qq.empty();	//返回容器是否为空   
qq.size();	//返回容器的大小  
qq1.swap(qq2);	//交换qq1和qq2的内容   
以上就是仅有的几个功能函数。   
### 迭代器及遍历  
不支持迭代器也不支持遍历。  
如果需要遍历，那么就不应该使用queue，显然queue是为其特性先进先出服务的。     
### 总结
queue为其特性先进先出而服务，因此当我们需要一个容器实现先进先出的特点可以考虑使用queue。  
同时，他也不具有其它容器如vector和list，较为复杂的功能函数，既不支持迭代，也不支持遍历。  