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
### 调整容器的容量
```c
std::deque<int> deq{1,2,3,4,5,6};  
deq.resize(3);	//如果往小调整，则会从后往前删除多余的元素，1，2，3    
deq.resize(5);	//如果往大了调整，则会从前往后增加默认值初始化元素，1，2，3，0，0    
deq.resize(7,200);	//如果往大了调整，可以使用特定值进行增加元素的值初始化。1,2,3,0,0,200,200    
```   
这是个相对比较灵活的函数，在特定时候可以用于增加或删除元素。    
另外可以通过shrink_to_fit函数来收缩deque的内存空间。通常情况下deque及其它类似的容器会提前分配一些额外的空间，以便于在插入的时候可以快速插入新的元素。而这个函数可以收束空间，使其只占用当前实际需要的内存。   
```c
deq.shrink_to_fit();	//调用很方便    
```   
使用起来比较方便，这样当前需要多少空间，那么就占用多少空间了，不会占用额外的一些空间。       
### 功能函数
以下是一些常用的功能函数：  
deq.empty();	//如果为空则返回true，不然false   
deq.size();	//返回元素的输两   
deq.max_size();	//返回deq在当前系统环境中能容纳的最多的元素的数量   
deq.front();	//返回第一个元素   
deq.back();	//返回最后一个元素   
deq1.swap(deq2);	//交换两个deque的内容   
deq[n];	//支持下标，可以像数组一样访问每个位置上的数字，但不会检查是否越界。    
deq.at(n);    //at方法访问，与下标相同，区别就是at会检查是否越界，是则抛出out of range异常。  
### 迭代器的使用及遍历    
迭代器是一种检查容器内元素并遍历元素的数据类型。C++更趋向于使用迭代器而不是下标操作，因为标准库为每一种标准容器定义了一种迭代器类型。  
**获取迭代器的函数**   
```c
deque<int> deq;  
deque<int>::iterator itrBegin= deq.begin();  //获取第一个元素的迭代器   
deque<int>::iterator itrEnd= deq.end();   //获取最后一个元素再后一个的迭代器   
deque<int>::const_iterator itrCBegin= deq.cbegin();  //获取begin的const属性的迭代器   
deque<int>::const_iterator itrCEnd= deq.cend();   //获取end的const属性的迭代器   
```   
**使用迭代器进行遍历**   
```c
deque<int> deq;   
for (int i = 0; i < 5; i++)  
	deq.push_back(i);	 	 	
	
deque<int>::iterator itr;   
for (itr = deq.begin(); itr != deq.end(); itr++)  
	cout << *itr << " ";   
```  
需要注意的是，不要对deq.end()进行解引用操作，因为它已经在容器之外了，解引用将会是未定义的操作。  
### 总结
尽管就名称上是double-queue，但是实际上与queue队列的区别还是挺大的。   
queue不支持迭代器，不支持下标，只能对头节点进行操作，当然这种模式下它的效率会很高。   
与其跟queue相比较，deque与vector的相似度更高一些，在各种功能函数及使用上，都有着很多相同性。  
其不同点在于：   
1. 两端都能快速安插和删除元素，这些操作可以在分期摊还的常数时间（amortized constant time）内完成。    
2. 元素的存取和迭代器的动作比vector稍慢。   
3. 迭代器需要在不同区块间跳转，所以它非一般指针。   
4. 因为deque使用不止一块内存（而vector必须使用一块连续内存），所以deque的max_size()可能更大。   
5. 不支持对容量和内存重新分配时机的控制。不过deque的内存重分配优于vector，因为其内部结构显示，deque不必在内存重分配时复制所有元素。而vector由于总是连续的，所以它会需要重新复制所有的元素。        
6. 除了头尾两端，在任何地方安插或删除元素，都将导致指向deque元素的所有pointers、references、iterators失效。   
7. deque的内存区块不再被使用时，会自动被释放。deque的内存大小是可自动缩减的。    
8. deque与vector组织内存的方式不一样。在底层，deque按“页”（page）或“块”（chunk）来分配存储器，每页包含固定数目的元素。而vector只分配一块连续的内存。例如，一个10M字节的vector使用的是一整块10M字节的内存，而deque可以使用一串更小的内存块，比如10块1M的内存。所以不能将deque的地址（如&deque[0]）传递给传统C的API，因为deque内部所使用的内存不一定会连续。   