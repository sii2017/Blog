## 标准库模板 forward_list
c++11之前，我们使用单向链表，一边自己造轮子使用ListNode类型。从c++11开始，我们可以使用标准库的单向链表std::forward\_list了。   
单向链表forward\_list其实就是对C语言风格的单链表的封装，仅提供有限的接口。  
相对于std::list(双向链表，并且定义很多接口)来说它节省了内存，同时又有比list更好的运行时性能；相对于自己实现的C风格的单链表(hand-written c-style linked list)而言，forward_list也有与其不相上下的效率表现。   
### 头文件支持   
```c
#include <forward_list>   
```   
### 初始化
作为标准库模板，其初始化的方式与其它模板类似。   
```c
forward_list<int> list1 = { 1,2,3,4,5 };		//通过初始化列表初始化   
forward_list<int> list2 = list1;	//通过拷贝来初始化   
forward_list<int> list3(list2);		//同样是通过拷贝初始化   
forward_list<int> list4(10);	//通过数量初始化，每个元素使用默认构造函数初始化，int则为0     
forward_list<int> list5(10, 2);	//以10个2进行初始化，即n个element进行初始化     
forward_list<int>::iterator itrBegin = list5.begin();  
forward_list<int>::iterator itrEnd = list5.end();  
forward_list<int> list6(itrBegin, itrEnd);	//也支持[a,b)的范围赋值。但是需要注意，由于forward_list的存在形式是指针，并不是数组，我们没有办法通过给迭代器+数字来定位某个位置，不过++还是支持的。   
```   
除了以上的，forward_list还支持c++11推出的**移动构造函数**来进行构造。详情可参考本目录下的《c++11 移动构造函数和移动赋值函数》。   
### 添加元素
**在开头插入单个元素**   
```c
forward_list<int> list(3, 2);   
list.push_front(10);	//在开头插入10.  10 2 2 2  
```   
由于我们始终知道单向链表的头节点，所以在头部插入元素效率很高。  
**赋值操作**  
```c
list1= list2;  //支持正常的赋值  
list3= rValue;	//支持c++11新推出的移动赋值  
list4= {1,2,3,4,5};	//支持初始化列表赋值   
forward_list<int>::iterator itrBegin= list4.begin();   
forward_list<int>::iterator itrEnd= list4.end();   
list5= assign(itrBegin, itrEnd); //支持assign的[)分配元素  
list6= assign(3,10);	//支持assign的数量*元素的赋值   
```  
基本上，vector支持的赋值操作，单向链表都支持。   
**在固定位置添加单个或多个连续的元素**   
```c
forward_list<int>::iterator  ret;  
forward_list<int> list(3, 2);  

forward_list<int>::iterator itrBegin = list.begin();  
ret= list.insert_after(itrBegin, 5);	//在第1个元素后插入5，返回新插入的元素的位置		2 5 2 2    

ret= list.insert_after(itrBegin++, 2, 3);	//在第2个元素后面插入2个3，返回新插入的第一个元素的位置  2 5 3 3 2 2    

forward_list<int> templist = { 9,1,1 };  
forward_list<int>::iterator rangeBegin = templist.begin();  
forward_list<int>::iterator rangeEnd = templist.end();  
list.insert_after(list.begin(), rangeBegin, rangeEnd);	//在list的第一个元素后面插入templist的全部元素，返回新插入的第一个元素的位置 2 9 1 1 5 3 3 2 2   
```
与vector，这些函数以迭代器位置为标识进行插入，返回新插入的（第一个）元素的位置。   
需要注意的是，由于单向链表的插入，只需要改变个别指针，并不需要移动内存，因此单向链表中间位置元素的插入的效率高于vector。   
### 删除元素
### 功能函数
注意：因为性能方面的考虑，forward_list不提供size()接口，这正是标准所说的“不比手写的C风格单链表有更多的时间和空间上的开销”的设计目标的结果。   