## 类默认函数的控制  
c++11增加了两个关键字用来增强（或者说简化）类默认函数的控制。  
> 默认构造函数，默认拷贝构造函数，默认赋值运算符函数，默认析构函数。    
### default
通常情况下，当我们没有显式设定类的构造函数时，编译器会自动生成一个默认的无参数的构造函数。   
但是当我们设定了任意一个构造函数时，编译器就不再生成默认构造函数了。   
有时候，我们自己编写了一个构造函数，但是却又想要默认的构造函数时，通常这么做：   
```c
class A
{
public:
	A(){}   
};   
```  
我们会另外手动设置一个空的构造函数。   
现在default可以更方便的来做这件事情。   
```c
class A
{
public:
	A()=default;  
	A(const A& a)=default;   
	A& operator= (const A& a)=default;
	~A()=default;   
};
```  
这样写，就可以强制编译器生成一个默认函数（据说也会方便编译器做一些相关的优化）。    
### delete
delete关键字的推出，方便程序员可以显式的禁用一些类默认函数。防止进行一些不符我们想法的默认转化。   
用的方式也与default很类似。  
```c
class A
{
public:
	A()=delete;	//禁用构造函数，在有这个关键字之前，禁用构造函数通常是将构造函数放在private里。  
	A(const A& a)=delete;	//禁用默认拷贝构造函数  
	A& operator=(const A& a)=delete;	//禁用默认赋值运算符函数  
```   
delete函数特性还可以用来禁用某些用户自定义的类的 new 操作符，从而避免在自由存储区创建类的对象。  
```c
class X5
{
public:
    void *operator new(size_t) = delete;
    void *operator new[](size_t) = delete;
};
```