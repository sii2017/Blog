# 智能指针   
c++中使用动态内存需要程序员手动的通过new来申请，通过delete来释放内存。在某些情况下，程序员会忘记或者不够及时的通过delete来释放动态内存，从而引起内存的浪费以及泄露。   
为了解决c++内存泄漏的问题，c++11引入了智能指针（Smart Point)。  
智能指针分为三种类型，shared\_ptr、unique\_ptr和weak\_ptr。以下为shared_ptr的使用介绍。    
## shared\_ptr
shared_ptr是一种使用引用计数的智能指针。它通过正常动态分配的动态内存进行初始化。    
每多一个shared_ptr的拷贝，引用技术就加1，并且它们指向同一个动态内存。   
当智能指针shared_ptr离开作用域，智能指针shared_ptr会自己析构，但是只要引用计数大于0，那么指向的动态内存就仍然存在。当最后一个智能指针shared_ptr析构的时候，shared_ptr会delete指向的动态内存。   
因此智能指针shared_ptr可以防止由于忘记delete引起的内存泄露，它总是能在最后一个shared_ptr析构时释放内存。并且它也能防止由于多次delete引起的程序崩溃，因为引用计数只要大于0，它就不会去释放内存。   
## 基本用法   
### 头文件支持  
```c
#include <memory>   
```   
### 初始化  
如果使用动态内存进行初始化，那么引用计数为1。   
如果使用已经指向动态内存的智能指针进行初始化，那么引用计数+1。  
```c   
shared_ptr<int> p1;	//初始化为空智能指针   
shared_ptr<int> p2(new int(6));		//通过new返回的指针进行初始化    
shared_ptr<int> p3 = new int(6);	//这是错误的，shared_ptr的构造函数带有explicit参数，不接受隐式转换，因此不能将普通的隐式指针转换成智能指针，只能通过直接初始化      
shared_ptr<int> p4(p2);		//通过其它智能指针进行赋值，这里share了p2指向的值，计数器为2，当然计数器也是共享的。    
shared_ptr<int> p5(make_shared<int>(100));	//make_shared函数会返回一个shared_prt类型的智能指针，与p4类似，是通过别的智能指针进行初始化，不过这是一个全新的智能指针，计数为1。   
```   
另外，在初始化的时候我们也可以以函数的形式手动传输给智能指针shared_ptr删除器。   
在某些情况下会用到，比如我们使用智能指针管理的资源并不是new出来的，比如我们需要遍历着去delete数组里的指针。   
```c
void del(int* i)   
{  
	delete i;   
}   

int main()  
{   
	shared_ptr<int> p(new int(5), del);   
	getchar();   
	return 0;  
}   
```
### 赋值操作
智能指针shared_ptr的赋值，与指针的赋值类似：赋值不改变值，而是让指针指向一个别的地方。   
需要注意的是，让动态指针改变指向的位置，会导致原来指向的动态指针的计数减少，以及新指向的动态指针的计数增加。   
```c   
shared_ptr<double> p(new double (9.6));   
shared_ptr<double> p1;   
p1 = p;	//赋值，引用计数加1。     
p1 = make_shared<double>(10.1);	//p1指向其它动态内存，p的引用计数-1，p1作为第一个指向该动态内存的智能指针，引用计数为1。  
p1 = new double(5.5);	//错误，不能将内置动态指针赋值给智能指针。   
```  
我们可以认为每个shared_ptr都有一个关联的计数器，通常称其为引用计数。无论何时我们拷贝一个shared_ptr，计数器都会递增。当我们给shared_ptr赋予一个新值或者shared_ptr被销毁（例如一个局部的shared_ptr离开其作用域），计数器则会递减。  
### make_shared函数   
最安全的分配和使用动态内存的方法是调用一个叫make_shared的标准库函数。这个函数在动态内存中分配一个对象并初始化它，返回指向此对象的shared_ptr指针。   
要使用该函数，必须要在尖括号中指定创建的对象的类型。   
```c
shared_ptr<int> p1= make_shared<int>(42);	//指向一个值为42的int的shared_ptr    
shared_ptr<string> p2= make_shared<string>("fate");	//指向一个值为"fate"的string   
shared_ptr<int> p3= make_shared<int>();	//指向值初始化的int（为0）。   
```   
因为其返回的是shared_ptr指针，因此既可以用来赋值，也可以用来初始化。   
### 其它功能函数 
```c
p1.swap(p2);	//进行交换  
p.unique()；		//如果只有一个引用了，那么返回true，如果大于或小于1个则返回false。   
p.use_count();	//返回当前引用计数   
p.reset();	//如果p是唯一指向其对象的智能指针，reset会释放此对象，然后将p置为空。  
p.reset(q);	//使p指向q，p原来指向的智能指针减1或释放，新指向的q加1。   
p.reset(q, d);	//会调用d来释放q而不是delete。   
*p;		//解引用智能指针获得指向的原始内置指针。   
(*p).fun();	//(*p).fun()等于p->fun()   
p.get();	//返回p指向的原始内置指针。   
```   
### 注意
#### 不要混合使用普通指针和智能指针。   
使用一个内置指针来访问一个智能指针所负责的对象是危险的，因为我们无法指针对象何时被销毁。因此当我们访问内置指针的时候，很可能该地址已经被释放了。   
#### 也不要使用get初始化另一个智能指针或为智能指针赋值。   
```c
int* i = new int(1);  
shared_ptr<int> p(i);   
shared_ptr<int> q(i);   
cout << p.use_count() << " " << q.use_count() << endl;   //1 1   
//如果这时候p被释放，会delete i，那么q指向的就是被释放的i，就是一个悬垂指针了。   
```   
当我们使用智能指针给智能指针初始化或赋值的时候，他们属于共享的情况。而当我们独立的使用同一个指针给不同的智能指针初始化，他们是相对独立的。  
同理，当我们使用get获得的原始内置指针给另一个智能指针初始化的时候，会出现一个情况：有两个智能指针同时指向同一个内置指针，且他们的计数是相对独立的。当其中一个智能指针销毁的时候会delete指向的指针，而那时候另外一个智能指针就是悬垂指针了。   
#### 循环引用
循环引用是智能指针的死穴，一定要避免。  
```c  
class A  
{   
public:   
	shared_ptr<B> p;   
};  

class B   
{  
public:    
	shared_ptr<A> p;   
};   

int main()  
{   
	while (true)  
	{  
		shared_ptr<A> pa(new A);   
		shared_ptr<B> pb(new B);   
		pa->p = pb;  
		pb->p = pa;   
	}  
	//由于初始化和赋值，两个智能指针的计数都为2。他们在出循环的时候无法析构两次，因此会进入死循环不断的泄露内存。   
	getchar();   
	return 0;  
}  
```    
### 智能指针陷阱总结
1 不使用相同的内置指针值初始化（或reset）多个智能指针。   
2 不delete通过get()返回的指针。   
3 不使用get()初始化或reset另一个智能指针。   
4 如果使用通过get()返回的指针，记住当最后一个对应的智能指针销毁后，这个指针就变无效了。   
5 如果使用智能指针管理的资源不是new分配的内存，记住传递给他一个删除器。   