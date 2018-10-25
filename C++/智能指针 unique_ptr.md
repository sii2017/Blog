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
```   
### 赋值操作
由于unique_ptr只支持一对一的绑定，可以想到的是，它是不支持赋值的。   
```c
p2 = p1;	//错误，无法被赋值   
```   
给unique_ptr赋值nullptr可以释放其指向的对象，将其置为空。   
对于赋值和拷贝，unique_ptr有一个例外：我们可以拷贝或赋值一个将要被销毁的unique_ptr：   
```c
unique_ptr<int> clont(int p)   
{   
	return unique_ptr<int>(new int(p));	  //即将被销毁的临时对象unique_ptr    
}      
```   
还可以返回一个局部对象的拷贝：   
```c
unique_ptr<int> clone(int p)  
{   
	unique_ptr<int> ret(new int (p));   
	return ret;    //出了作用域即将被销毁的局部对象  
}  
```  
### 其它功能函数
```c
unique_ptr<string> u;   
u.release();	//释放u对指针的控制权，函数返回该指针，并将u置为空   
u.reset();	//释放u指向的对象，并且将u置为空。   
u.reset(q);	//如果提供了内置指针q，那么令释放原来指向的对象并指向这个指针。   
```   
虽然不能拷贝或赋值unique_ptr，但是可以通过调用release或reset函数将指针的所有权从一个（非const）unique_ptr转移到另一个unique_ptr：   
```c
unique_ptr<string> p2(p1.release());	//release将p1值为空，同时返回指针给p2进行初始化。   
p2.reset(p3.release());	//ret释放了p2原来指向的内存，然后重新指向了p3释放的指针。   
```  
### 向unique_ptr传递删除器  
与shared_ptr类似，unique_ptr默认情况下用delete释放他指向的对象。与shared_ptr一样，我们可以重载unique_ptr中默认的删除器，即传递一个新的删除方式给unique_ptr。但是与shared_ptr不同的是，shared_ptr通过reset函数就可以传递，而unique_ptr需要在声明该智能指针的时候，在尖括号的第二个参数进行传递。   
> 在重载了删除器之后，当我们使用reset也需要再次指定删除器。   
   
```c
unique_ptr<objT, delT> p(new objT, fun);   
```   
delT为fun类型的指针，通常我们使用decltype来获取这个指针。如：  
```c   
void delfunction(int* b)  
{   
	delete b;  
}   
unique_ptr<int, decltype(delfunction)*> p(new int, fun);    
```   
