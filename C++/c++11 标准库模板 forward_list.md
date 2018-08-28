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
```   
除了以上的，forward_list还支持c++11推出的**移动构造函数**来进行构造。详情可参考本目录下的《c++11 移动构造函数和移动赋值函数》。   
### 添加元素
### 删除元素