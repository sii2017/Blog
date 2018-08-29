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

ret= list.emplace_after(list.begin(), 25);	//在list的第一个元素后插入25，返回第一个新元素的位置  2 25 9 1 1 5 3 3 2 2     
list.emplace_front(100);	//在list的第一个元素前插入100，无返回值  100 2 25 9 1 1 5 3 3 2 2     
```
与vector，这些函数以迭代器位置为标识进行插入，返回新插入的（第一个）元素的位置。   
需要注意的是，由于单向链表的插入，只需要改变个别指针，并不需要移动内存，因此单向链表中间位置元素的插入的效率高于vector。   
### 删除元素
**删除开头单个元素**   
```c
list.pop_front();  
```   
不需要参数。  
由于我们始终知道头节点，删除头部元素相当方便。就实现而言，只需要提前将下一个节点保存为头节点，并释放原来的第一个指针就可以。      
**删除固定位置的一个或多个元素**  
```c
forward_list<int> list = { 100, 2, 25, 9, 1, 1, 5, 3, 3, 2, 2 };  

forward_list<int>::iterator itrPos= list.begin();  
itrPos++;	//将迭代器移动到第二个元素   

list.erase_after(itrPos);	//删除第二个元素后的一个元素即25。  100 2 9 1 1 5 3 3 2 2   
list.erase_after(list.begin(), ++itrPos);	//删除第一个元素（不包括）和第二个参数（不包括）之间的元素。 100 9 1 1 5 3 3 2 2    
```   
**根据条件删除元素**   
```c
bool isBiggerThan10(int i)  
{   
	return i > 10;   
}  

int main(int argc, char** argv)  
{  
	forward_list<int> list = { 100, 2, 25, 9, 1, 1, 5, 3, 3, 2, 2 };  

	list.remove(3);	//删除所有值为3的元素。 100, 2, 25, 9, 1, 1, 5, 2, 2    

	list.remove_if(isBiggerThan10);	//删除所有值大于10的元素。   2, 9, 1, 1, 5, 2, 2   
	list.remove_if([](int i) {return i > 5; });	//也可以使用c++11退出的lambda表达式，删除所有值大于5的数。  2, 1, 1, 5, 2, 2    

	getchar();  
	return 0;  
}  
```  
根据条件删除元素还是比较便利的，省区了自己统一遍历单向链表的过程。     
**删除所有的元素**   
```c
list.clear();   
```  
简单明了。  
### 调整空间  
关于调整容器的空间，与vector的resize相似，多出来的部分用默认值或者指定值进行填充，如果是见小，那么就从后往前进行删除。   
```c
forward_list<int> list = { 1,5 };  

list.resize(4);		//将大小调整（扩大）为4个，多出来的部分按照默认来构造。  1 5 0 0     
list.resize(6, 255);	//将大小调整（扩大）为6个，多出来的部分按照255来构造  1 5 0 0 255 255   
list.resize(2);		//将大小调整（缩小）为2个， 从后往前删除多余的元素   1 5   
```  
### 功能函数
注意：因为性能方面的考虑，forward\_list不提供size()接口，这正是标准所说的“不比手写的C风格单链表有更多的时间和空间上的开销”的设计目标的结果。   
其它的一些功能函数：  
list.empty();	//返回list是否为空  
list.max\_size()；	//返回list的最大可能的容量，内存大的话数量会非常多。   
list.unique();	//删除所有连续相同的元素  
list.unique(op);	//山粗连续使op(elem)==true的值，与remove\_if的参数相类似，可以使用返回bool值的函数也可以使用lambda表达式。   
list.sort();	//使用默认的<来给所有的元素排序。   
list.sort(op);	//需要返回bool值的函数或者lambda支持，按照返回值来排序。  
dst.splice\_after(dstPos, src); //把src里的全部元素移动到dst中的dstPos之后。   
dst.splice\_after(dstPos, src, srcPos);  //把src里的srcPos后面的一个元素移动到dst中的dstPos之后。   
dst.splice_after(dstPos, src, srcBegin, srcEnd);	//把src里(srcBegin, srcEnd)之间的元素移动到dst中的dstPos之后   
> 注意，splice\_after中的dst和src可以是同一个list，因此可以用此函数实现内部位置移动。   
   
list1.merge(list2);	//将list2的元素合并到list1中，假定二者原来都已序，那么移动之后list1仍然有序   
list1.merge(list2, op);	//将list2的元素合并到list1中，假定二者原来都按op已序，那么移动之后list1将按op排序  
list1.swap(list2);	//list1和list2交换元素   
list.reverse();	//反转list中的元素  
== != < >等符号正常支持。  
### 迭代器的使用及遍历
迭代器是一种检查容器内元素并遍历元素的数据类型。C++更趋向于使用迭代器而不是下标操作，因为标准库为每一种标准容器定义了一种迭代器类型。   
**获取迭代器的函数**  
```c
forward_list<int> list = { 1,5 };   

forward_list<int>::iterator itrBegin = list.begin();	//获取第一个元素的迭代器  
forward_list<int>::iterator itrEnd = list.end();	//获取最后一个元素后一个位置的迭代器  
forward_list<int>::const_iterator itrCBegin = list.cbegin();	//获取begin的const属性迭代器  
forward_list<int>::const_iterator itrCEnd = list.cend(); //获取end的const属性迭代器   
forward_list<int>::iterator itrBeforeBegin = list.before_begin();	//获取第一个元素前一个位置的迭代器  
forward_list<int>::const_iterator itrCBeforeBegin = list.cbefore_begin();	//获取before_begin的const属性迭代器   
```  
**使用迭代器进行遍历**  
```c
forward_list<int> list = { 1,5 };

for (forward_list<int>::iterator itr = list.begin(); itr != list.end(); itr++)
{
	cout << *itr << endl;
}
```   
需要注意的是，不要对list.before_begin()和list.end()进行解引用操作，因为这两个容器的实际位置在容器之外，这样的行为是未定义的。  
### 总结
结构：以指针相互连接而成，由于要存放大量指针，因此占用的内存空间相对vector而言较高。  
访问：访问头节点快，但是不支持下标，随机访问较慢（需要遍历）。    
插入删除：由于只需要更改指针的指向而不用移动整体内存位置，在任意位置插入删除都很快。   