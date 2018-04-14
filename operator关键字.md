## operator关键字的两种用法
在C++中，operator是一个关键字，它一共有两种用法。   
> ps operator的意思是操作员。   
### 用于类型转换函数
类型转换操作符（type conversion operator）是一种特殊的类成员函数，它定义将类类型值转变为其他类型值的转换。转换操作符在类定义体内声明，在保留字 operator 之后跟着转换的目标类型。转换函数又称类型强制转换成员函数，它是类中的一个非静态成员函数。   
**类型转换函数的特征：**  
1 类型转换函数被定义在源类中。即    
```c     
A a;   
B b;   
a= b;   //则类型转换函数被定义在A类中   
```   
2 类型转换函数须由operator关键字修饰，函数名称是目标类型名或目标类名。    
3 类型转换函数没有参数，没有返回值，但是有return语句。return语句中返回目标类型数据或调用目标类的构造函数。    
**类型转换函数主要有两类：**    
1 对象向基本数据类型转换，代码如下   
```c
#include<iostream>    
#include<string>    
using namespace std;     
class D    
{     
public:    
	D(double d):d_(d) {}  //从这里可知D类原本是支持double类型数据的   
	//类型转换函数，符合特征：没有返回值定义内有return语句、没有参数、须由operator做修饰、函数名为目标类或数据类型。
	operator int() const   
	{    
		std::cout<<"(int)d called!"<<std::endl;//这行并不是必要的，为被调用做标记。        
		//每当该类实例被赋值的时候，
		return static_cast<int>(d_);     
	}     
private:    
	double d_;    
};     

int add(int a,int b)		    
{    
	return a+b;    
}     

int main()		   
{    
	D d1=1.1;    
	D d2=2.2;    
	std::cout<<add(d1,d2)<<std::endl;    
	system("pause");   
	return 0;    
}    
```
### 用于重载操作符