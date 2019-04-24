## 标准库模板 deque
双端队列，doulbe-ended queue，它的特点在于可以动态的在两个端进行增加或删减元素。   
同vector类似，deque可以在两端进行高效的插入和删除。但是与vector不同的是，deque不保证它的元素都保存在相邻的位置，因此使用指针进行位移来指向deque的另一个元素，有可能指向未定义的空间。   
尽管deque与vector提供了看上去比较类似的解决方案，但是deque的内部更加复杂一些。由于deque的元素是分散存储的，因此deque内部存储了相关的信息，以便可以让使用者顺利访问指定的元素，并且即使在相当长的队列的情况下，增加元素也能更加高效。   
我认为，deque应该比vector略微高效，但是内存的花销较高。    
### 头文件支持
```c
#include <deque>   
```
### 初始化
deque<T> first;  //默认初始化
deque<T> second(n,val);	//用n个val进行初始化   
deque<T> third(second.begin(), second.end());	//用second的区间进行初始化   
deque<T> fouth(third);	//用另外一个deque进行初始化   

int arr[]={1,2,3,4,5};  
deque<int> fifth(arr, arr+size(arr)/sizeof(int));	//直接用数组进行初始化   
deque<int> sixth{1,2,3,4,5};	//使用初始化列表进行初始化   
### 添加元素
**压入单个元素**   
```c
deque<int> deq;  
deq.push_back(10);	//最后压入  
deq.push_front(4);	//开头压入   
deq.emplace_back(10);	//最后压入（构造）   
deq.emplace_front(4);	//开头压入（构造）   
```   
**赋值操作**（会覆盖原有的元素）     
```c  
deque<int> first;   
first.assign(7,100);	//赋值7个100     
deque<int> second;   
second.assign(first.begin(), first.end());	//根据区间赋值       
deque<int> third;   
int arr[]= {1,2,3,4,5,6,7};    
third.assign(arr, arr+3);	//复制从arr开始后的3个元素（实际上也是根据区间进行赋值）     
```    
以上几种方法与初始化比较类似。   
**固定位置加入单个或多个元素**    
```c
deque<int> first{12,3,4,5};  
auto it= first.begin();   
first.insert(it+1, 10);	//在第二个位置插入单个元素10   
first.insert(first.begin()+3, 2, 8);	//在第四个位置插入2个相同的元素8    
deque<int> second{3,4,5,6};   
second.insert(second.begin(), first.begin(), first.end());	//在第一个位置插入一段区间里的元素   
```
以上可以看到跟初始化类似，支持单元素，相同的多元素，以及区间的插入。   
```c
first.emplace(first.begin()+1, 1);	//与insert类似，不过emplace只能添加单个元素，不支持区间以及多个同样的元素   
```
以上函数的返回值都是一个指向新添加的第一个元素的迭代器。  
> 注意：在添加元素以后，作为位置的元迭代器将会失效，再去使用它是非常危险且未定义的，应该重新获取迭代器。   
### 删除元素
**删除单个元素（只支持在两端操作）**   
```c
deque<int> deq{1,2,3,4,5,6,7};   
deq.pop_back();	//压出最后一个元素   
deq.pop_front();	//压出开头第一个元素   
```   
比vector多支持一个前端。   
**删除批量元素**   
deque的erase函数，可以根据提供的位置，删除一个或者多个连续的元素。   
```c
deque<int> deq{1,2,3,4,5,6};   
deq.erase(deq.begin()+1);	//删除第二个位置的元素  
deq.erase(deq.begin(), deq.begin()+1);	//删除开头两个元素   
```  
同样值得注意的是删除元素后原有的迭代器就失效了，需要重新获取。   
**删除全部元素 **   
```c
deq.clear();	
```   
### 扩充空间