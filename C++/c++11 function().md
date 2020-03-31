## c++11 function()
类模版std::function是一种通用、多态的函数封装。   
std::function的实例可以对任何可以调用的目标实体进行存储、复制、和调用操作，这些目标实体包括普通函数、Lambda表达式、函数指针、以及其它函数对象等。std::function对象是对C++中现有的可调用实体的一种类型安全的包裹（我们知道像函数指针这类可调用实体，是类型不安全的）。    
通常std::function是一个**函数对象类**，它包装其它任意的函数对象，被包装的函数对象具有类型为T1, …,TN的N个参数，并且返回一个可转换到R类型的值。std::function使用 模板转换构造函数接收被包装的函数对象；特别是，闭包类型可以隐式地转换为std::function。   
> 通过std::function对c++中各种可调用实体（普通函数、Lambda表达式、函数指针、以及其它函数对象等）的封装，形成一个新的可调用的std::function对象；   
> 或者说，function可以声明一个属于“可调用对象”的变量。   
### 头文件
```c
#include <functional>   
```   
该类型在名字空间std中。   
### 原型
```c
template< class R, class... Args >   
class function<R(Args...)>   
```   
R是返回值类型，Args是函数的参数类型。    
声明一个std::function对象很简单，就是将可调用对象的返回值类型和参数类型作为模板参数传递给std::function模板类。比如：   
```c
std::function<void()> f1;
std::function<int (int , int)> f2;
```   
### 用法
std::function类型支持封装的可调用对象有如下六种：   
1 普通函数   
2 lambda表达式（可以参考同目录下《c++11 Lambda表达式》）  
3 函数指针（《可以参考同目录下函数指针》）   
4 仿函数（可以参考同目录下《仿函数》）   
5 类成员函数  
6 静态成员函数   
#### 代码说明
```c
//普通函数
bool compare_fun(int a, int b)
{
	return a < b;
}

//lambda函数
auto compare_lambda = [](int a, int b)->bool {return a < b; };

//仿函数
class compare_functor
{
public:
	bool operator()(int a, int b)
	{
		return a < b;
	}
};

class compare
{
public:
	bool compare_class(int a, int b)	//普通类成员函数
	{
		return a < b;
	}

	static bool compare_static(int a, int b)	//类静态成员函数
	{
		return a < b;
	}
};

int main()
{
	function<bool(int, int)> fun;
	
	int a = 10;
	int b = 20;

	//普通函数
	fun = compare_fun;
	cout << fun(a, b) << endl;

	//lambda函数
	fun = compare_lambda;
	cout << fun(a, b) << endl;

	//仿函数
	fun = compare_functor();
	cout << fun(a, b) << endl;

	//静态函数
	fun = compare::compare_static;
	cout << fun(a, b) << endl;

	//类普通成员函数比较特殊，需要使用bind函数，并且需要实例化对象，成员函数要加取地址符
	compare temp;
	fun = bind(&compare::compare_class, temp, placeholders::_1, placeholders::_2);
	cout << fun(a, b) << endl;

	getchar();
	return 0;
}
```
关于bind函数，可以参考同目录下《c++11 bind()》   
### 注意事项
1 可调用实体与function对象的参数和返回值要相同，或者满足隐式转换的要求。    
2 function不能被用来检查相等或者不相等，但是可以与NULL或nullptr进行比较。  
3 如果对空的function进行调用会引发异常。   