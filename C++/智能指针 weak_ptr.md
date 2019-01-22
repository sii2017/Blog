# 智能指针
c++中使用动态内存需要程序员手动的通过new来申请，通过delete来释放内存。在某些情况下，程序员会忘记或者不够及时的通过delete来释放动态内存，从而引起内存的浪费以及泄露。   
为了解决c++内存泄漏的问题，c++11引入了智能指针（Smart Point)。  
智能指针分为三种类型，shared\_ptr、unique\_ptr和weak\_ptr。以下为weak\_ptr的使用介绍。    
## weak\_ptr
weak\_ptr是一种不控制所指向对象生存期的智能指针，它指向一个由shared_ptr管理的对象。   
将一个weak_ptr绑定到一个shared_ptr不会改变shared_ptr的引用计数。一旦最后一个指向对象的shared_ptr被销毁，对象就被释放，**即使有weak_ptr指向对象，对象也还是会被释放**。因此weak_ptr的名字抓住了这种智能指针“弱”共享对象的特点。   
## 基本用法
### 头文件支持
```c
#include <memory>  
```   
### 初始化
weak_ptr的初始化相对其他的智能指针比较简单。  
```c
weak_ptr<T> w;	//无值初始化   
weak_ptr<T> w(s);	//s可以是shared_ptr也可以是weak_ptr   
```  
### 赋值操作
weak_ptr可以用weak_ptr或shared_ptr直接进行赋值。   
```c
shared_ptr<int> p1(nwe int(8));    
weak_ptr<int> w1(p1);   
weak_ptr<int> w2;  
w2= p1;	//用shared_ptr进行赋值    
w2= w1;	//用weak_ptr进行赋值   
```   
### 其它功能函数  
```c
w.reset();	//将w置为空   
w.use_count();	//与w共享对象的shared_ptr的数量   
w.expired();	//如果w.use_cound()为0则返回ture不然则false   
w.lock();	//如果expired为true则返回一个空的shared_ptr，否则返回一个指向w的对象的shared_ptr   
```   
### weak\_ptr不支持解引用访问
由于weak_ptr是弱共享，因此可能存在指向的内存已经被释放的情况。所以weak_ptr不支持直接解引用访问。   
正确的访问姿势如下：   
```c
if(shared_ptr<int> temp= w.lock())     
	cout << *temp;    
```   
通过lock返回一个shared_ptr，如果不是空，则通过解引用访问shared_ptr。  
weak_ptr是不支持直接访问的。   