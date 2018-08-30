## 标准库模板 list
list是标准库实现的双向链表，与向量(vectors)相比, 它允许快速的插入和删除，但是随机访问却比较慢。   
就效率和运行时效率与c++11推出的forward_list单向链表来比，forward_list的效率略高一些。但是，list是双向的。  
### 头文件支持
```c
include <list>  
```   
### 初始化
作为标准库模板，其初始化的方式与其它模板类似。   
```c
list<int> lst1(5);	//建立有5个元素的链表，值默认初始化。  0 0 0 0 0  
list<int> lst2(3, 2);	//建立有3个2的链表  2 2 2  
list<int> lst3{ 4,5,6,7,8 };	//使用初始化列表进行初始化   

list<int>::iterator itrBegin = lst3.begin();  
list<int>::iterator itrEnd = itrBegin;  
itrEnd++;	//挪到第二个位置   
itrEnd++;	//挪到第三个位置   
list<int> lst4(itrBegin, itrEnd);	//以[ )的形式，将两个位置之间的值进行初始化本链表。  4 5   
list<int> lst5(lst4);	//使用别的链表初始化本链表  4 5   
list<int> lst6 = lst5;	//通过拷贝来初始化   
```  
### 添加元素
**在头尾插入一个元素**   
```c
lst.push_back(10);	//在末尾插入一个元素  
lst.push_front(1);	//在开头插入一个元素   

//以及c++11新推出的emplace相关函数  
lst.emplace_front(10);		//在开头插入一个元素  
lst.emplace_back(8);	//在最后插入一个元素    
```   
与vector相比，多了一个从头插入，与forward_list相比多了一个push_back。  
**赋值操作**   
```c  
list<int> lst, lst1, lst2, lst3;	//先声明需要使用的lst  
lst = lst1;	//支持赋值号赋值  
lst2 = { 1,2,3,4 };	//支持初始化列表赋值  
list<int>::iterator itrBegin = lst2.begin();  
list<int>::iterator itrEnd = lst2.end();  
lst3.assign(itrBegin, itrEnd);	//与其它容器相似，支持以[)的方式，将其它容器的段落赋值进来	1 2 3 4  
lst3.assign(2, 5);	//支持数量*元素的方式赋值。   5 5    
```  
**在固定位置添加单个或多个连续的元素**  
主要为insert与emplace相关的函数。  
```c
//insert相关函数  
list<int> lst1;  
lst1.insert(lst1.begin(), 10);	//1 通过位置进行单个元素的插入 10   
list<int> temp = { 1,2,3,4 };   
lst1.insert(lst1.begin(), temp.begin(), temp.end());	//2 将其它list的一段元素插入lst的指定位置 1 2 3 4 10   
list<int>::iterator itr = lst1.begin();   
itr++;		//挪动迭代器的位置，总是在第一个位置加也挺无聊的。      
lst1.insert(itr, 2, 8);	//3 在指定位置（第二个位置）加入2个8。  1 8 8 2 3 4 10    
   
//emplace相关函数  
list<int> lst2;  
lst2.emplace_front(10);		//在开头插入一个元素  10  
lst2.emplace_back(8);	//在最后插入一个元素  10 8   
lst2.emplace(lst2.begin(), 25);	//在固定位置加入一个元素 25 10 8     
```  
insert\_after和emplace\_after的区别是，前者会拷贝一份副本，然后再加入其中，而后者则是将参数传递给元素类型的构造函数直接构造一份出来。c++reference中提到emplace_after的效率更高一些。   
不过emplace无法像insert将一段元素加入到固定位置。  
### 删除元素  
**删除所有元素**   
```c
lst.clear();  
```   
**删除第一个或最后一个元素**   
```c
lst2.pop_back();  
lst2.pop_front();  
```   
**删除指定位置的一个或多个元素**   
```c
list<int> lst = { 1,2,3,4,5,6 };   
auto itr = lst.erase(lst.begin());	//1 删除指定位置的元素，返回下一个元素的迭代器。  2 3 4 5 6   
list<int>::iterator itrBegin = lst.begin();  
list<int>::iterator itrEnd = itrBegin;  
itrEnd++;  
itrEnd++;   
itr = lst.erase(itrBegin, itrEnd);	//2 以[)的方式删除第一个位置开始到第三个位置结束（不包括第三个位置）的元素 返回下一个元素的迭代器 4 5 6    
```   
**根据条件删除元素**  
```c
bool isBiggerThan10(int i)  
{   
	return i > 10;   
}  

int main(int argc, char** argv)  
{  
	list<int> lst = { 100, 2, 25, 9, 1, 1, 5, 3, 3, 2, 2 };  

	lst.remove(3);	//删除所有值为3的元素。 100, 2, 25, 9, 1, 1, 5, 2, 2    

	lst.remove_if(isBiggerThan10);	//删除所有值大于10的元素。   2, 9, 1, 1, 5, 2, 2   
	lst.remove_if([](int i) {return i > 5; });	//也可以使用c++11退出的lambda表达式，删除所有值大于5的数。  2, 1, 1, 5, 2, 2    

	getchar();  
	return 0;  
}  
```   
### 调整空间   
与forward_list相近，使用resize重新增加或减少空间，并且以默认值或指定值填充多出来的空间，以及当缩小时，从后往前删除元素。   
```c
list<int> lst = { 1,2,3,4,5,6 };   
lst.resize(10);		//扩大到10  1 2 3 4 5 6 0 0 0 0   
lst.resize(2);		//缩小到2   1 2  
lst.resize(5, 122);	//扩大到5  多出来的以122来配置   1 2 122 122 122  
```   
### 其它功能函数   
其它的一些功能函数：  
lst.size();	//返回总共的元素数量。  
lst.back();	//返回最后一个元素。   
lst.front();	//返回第一个元素。  
lst.empty();	//判断是否为空，空则返回true，反之false。  
lst.max\_size();	//返回当前内存能容纳的最多的元素数量，一般来说很大。   
list1.merge(list2);	//将list2的元素**合并**到list1中，假定二者原来都已序，那么移动之后list1仍然有序   
list1.merge(list2, op);	//将list2的元素**合并**到list1中，假定二者原来都按op已序，那么移动之后list1将按op排序   
list.sort();	//默认从小到大排序  
list.sort(op);	//也可以构造条件函数来排序  
list.reverse();	//反转list中的元素   
lst.splice(itr, lst2);	//将lst2的元素**拼接**到lst第二个位置开始    
lst.splice(itr, lst2, lst2.begin());	//将lst2的第一个位置的元素**拼接**到lst的itr位置   
lst.splice(itr, lst2, lst2.begin(), lst2.end());	//将lst2的一段元素**拼接**到lst的itr位置   
lst1.swap(lst2);	//交换lst1和lst2的元素。  
lst.unique();		//只是删除相邻相等的其中一个元素  
lst.unique(op);	//根据op条件来决定每一对相邻的元素需要删除的内容，与remove_if不同的地方在于，remove_if是判断每个独立元素是否符合条件，而unique是以相邻的一对元素是否符合条件。    
== != < >等符号正常支持。   
### 迭代器的使用及遍历
**获取迭代器的函数**    
迭代器是一种检查容器内元素并遍历元素的数据类型，标准库为每一种标准容器定义了一种迭代器类型。   
```c
list<int>::iterator itrBegin = lst.begin();	//获取第一个元素的迭代器 
list<int>::iterator itrEnd = lst.end();	//获取最后一个元素后一个位置的迭代器
list<int>::const_iterator itrCBegin = lst.cbegin();	//获取const属性的首元素迭代器
list<int>::const_iterator itrCEnd = lst.cend();	//获取const属性的最后一个元素后一个位置的迭代器
```   
**使用迭代器进行遍历**  
```c
list<int> lst = { 1,5 };    

for (list<int>::iterator itr = lst.begin(); itr != lst.end(); itr++)   
{  
	cout << *itr << endl;   
}   
```     
需要注意的是，不要对list.before_begin()和list.end()进行解引用操作，因为这两个容器的实际位置在容器之外，这样的行为是未定义的。  
### 总结   
结构：list是一个线性双向链表结构，它的数据由若干个节点构成，每一个节点都包括一个信息块（即实际存储的数据）、一个前驱指针和一个后驱指针。它无需分配指定的内存大小且可以任意伸缩，这是因为它存储在非连续的内存空间中，并且由指针将有序的元素链接起来。  
访问：list 随机检索的性能非常的不好，因为它不像vector 那样直接找到元素的地址，而是要从头一个一个的顺序查找，这样目标元素越靠后，它的检索时间就越长。    
插入删除：可以迅速地在任何节点进行插入和删除操作。因为lis 的每个节点保存着它在链表中的位置，插入或删除一个元素仅对最多三个元素有所影响，而不像vector插入一个元素要改变大量元素的内存位置。   
与forward_list单向列表相比，由于list需要支持双向，所以会占用更多的内存来存储反向的指针。   
