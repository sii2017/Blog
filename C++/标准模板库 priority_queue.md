## 标准模板库 priority_queue 优先队列
priority_queue是queue的变种，它与queue的不同在于priority_queue具有排序的功能，默认从大到小排序，即顶端元素最大，尾端元素最小。   
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
priority_queue<int, vector<int>, greater<int>> pqvg;	//使用三个参数进行初始化，指定存储元素类型及使用的里容器，以及使用STL里面定义了一个仿函数 greater<>来从小到大排列   

priority_queue<int> qq(pq);	//也可以使用其他优先队列来初始化自己，但是要保证他们的模式一致   
```   
相比queue，priority_queue的参数要多一个，为三个，因此初始化也较为复杂一些。  
前两个与之前一致，来决定存储元素的类型以及使用的里容器，第三个参数为一个仿函数。   
### 添加元素
### 删除元素
### 功能函数
### 迭代以及遍历
### 总结