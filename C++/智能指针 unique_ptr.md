# 智能指针
c++中使用动态内存需要程序员手动的通过new来申请，通过delete来释放内存。在某些情况下，程序员会忘记或者不够及时的通过delete来释放动态内存，从而引起内存的浪费以及泄露。   
为了解决c++内存泄漏的问题，c++11引入了智能指针（Smart Point)。  
智能指针分为三种类型，shared\_ptr、unique\_ptr和weak\_ptr。以下为shared_ptr的使用介绍。    
## unique\_ptr  
一个unique_ptr拥有/独占/绑定它所指向的对象。与shared_ptr不同，任何时刻只能有一个unique_ptr指向一个给定对象。   
当unique_ptr被销毁时，它所指向的对象也被销毁。   
## 基本用法
### 头文件支持
```c
#include <memory>   
```   
### 初始化
与shared_ptr不同，没有类似make_shared的标准库函数返回相关的指针。当我们定义一个unique_ptr时需要将其绑定到一个new返回的指针上，采用的时直接初始化形式。   
```c
unique_ptr<double> p;	//初始化一个空的unique指针   
unique_ptr<double> p1(new double(2.14));	//通过new返回的指针进行直接初始化    
unique_ptr<double> p2(p1);	//这是错误的，由于unique_ptr时独占的，它无法被其他智能指针初始化或者赋值   
p2 = p1;	//错误，无法被赋值   
```   
