## operator关键字的两种用法
在C++中，operator是一个关键字，它一共有两种用法。   
> ps operator的意思是操作员。   
### 用于类型转换函数
类型转换操作符（type conversion operator）是一种特殊的类成员函数，它定义将类类型值转变为其他类型值的转换。    
转换操作符在类定义体内声明，在保留字 operator 之后跟着转换的目标类型。转换函数又称类型强制转换成员函数，**每当类的实例需要类型转换时会调用**，它是类中的一个非静态成员函数。   
类型转换函数是自动被系统调用的，并且它的类型转换并不影响原来实例的值，只是需要类型转换时，将原来实例的值的副本进行转换并传出。   
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
	//add函数的形参为int，而D类型为double，这时候add函数会尝试让d1和d2进行类型转换，即调用类型转换函数
	std::cout<<add(d1,d2)<<std::endl;    
	system("pause");   
	return 0;    
}    
```    
2 对象向不同类的对象的转换：   
```c
#include <iostream>    
class A
{    
public:    
	A(int num = 0) :dat(num) {}   
	operator int() { return dat; }    
private:    
	int dat;   
};    
   
class X   
{     
public:    
	X(int num = 0) :dat(num) {}    
	operator int() { return dat; }    
	operator A()    
	{    
		A temp = dat;   
		return temp;   
	}    
private:   
	int dat;    
};   
   
int main()   
{   
	X stuff = 37;   
	A more = 0;    
	int hold;     
	hold = more;	//A类实例通过类型转换函数转换成int赋值给hold  
	std::cout << hold << std::endl;   
	more = stuff;	//X类实例通过类型转换函数转换成A类赋值给more    
	std::cout << more << std::endl;  
	getchar();    
	return 0;  
}   
```    
### 用于操作符重载    
将现有操作符与一个成员函数相关联，当成员对象使用该操作符的时候，赋予已有运算符新的功能，使它能够用于特定类型执行特定的操作。    
可以理解为：一方面要使运算符的使用方法与其原来一致，另一方面扩展其功能只能通过函数的方式。    
> 所谓“扩展其功能”的意思是是，对于内置类型如int,double等，我们可以正常使用等于、大于、小于等功能。但是如果是我们自定义的类的实例，则无法正常使用这些操作符。这种情况下我们对操作符进行重载，来使既符合原先的含义，又能在我们的实例间正常使用。    

**注意事项：**   
1 重载不能改变操作符的基本功能（脱离实例情况下），以及该操作符的优先级顺序。    
2 重载**不应**改变操作符的本来含义。     
3 只能对已有的操作符进行重载，不能重载新符号。   
4 操作符重载只对类有效。   
5 以下操作符不能被重载：   
指向成员的指针星号  
::作用域解析符     
?:问号条件运算符    
sizeof操作数的字节数    
**不同条件下操作符重载函数参数的限定**    
1 非成员函数：   
单目运算符：参数表中只有一个参数；   
双目运算符：参数表中只有两个参数；   
2 成员函数：     
单目运算符：参数表中没有参数；   
双目运算符：参数表中只有一个参数。     
**声明及定义一个操作符重载函数**   
1 操作符重载函数为类成员函数，代表左操作数的参数已经被隐式指定为了自己类实例。    
```c
//以重载==为例   
//person.h   
class person   
{    
private:    
	int age;    
public:   
	person(int a)   
	{    
		this->age= a;   
	}     
	//operator加上符号为函数名。   
	//如果是单目运算符则不需要参数，比如自增自减，因为参数就是实例本身的成员   
	//如果是双目运算符则需要一个参数，比如加号减号，加上本身自己就是一个参数，对自己及传进来的参数进行处理。    
	bool operator==(const person& ps) const   
	{  
		//函数内定义了对该操作符的具体处理方式，其实就是比较两个实例里的成员的大小。这里必须手动定义，因为编译器无法自动替我们进行比较。    
		return this->age== ps.age;   
	}    
};   
   
//main.cpp   
#include "person.h"   
using namespace std;   
int main()   
{   
	person p1(10);   
	person p2(20);   
	if(p1==p2)	//由于是person类的2个实例进行比较，这里调用了操作符重载函数。      
		cout << "the age is equal" << endl;    
	return 0;    
}      
```    
2 操作符重载函数为非类成员函数（全局函数），代表左操作数的参数必须被显示指定。   
```c
#include <iostream>      
class Student   
{   
public:    
	Student(int a):age(a){}   
	int age;    
};    

class Teacher   
{   
public:    
	Teacher(int a):age(a){}   
	int age;   
};    

bool operator==(const Student& age1, const Teacher& age2)   
{    
	return age1.age == age2.age;   
}    
   
int main()   
{   
	Student st(20);   
	Teacher tea(20);   
	if (st == tea)    
		std::cout << "equal" << std::endl;  
	else    
		std::cout << "not equal" << std::endl;   
	getchar();   
	return 0;   
}   
```     
3 操作符重载中针对自增自减的情况   
自增运算符“++”和自减运算符“--”分别包含两个版本。即运算符前置形式(如 ++x)和运算符后置形式(如 x++)，这两者进行的操作是不一样的。因此，当我们在对这两个运算符进行重载时，就必须区分前置和后置形式。C++根据参数的个数来区分前置和后置形式。     
如果按照通常的方法来重载 ++ 运算符(即作为成员函数重载时不带参数，或者作为非成员函数重载时带有一个参数)，那么重载的是前置版本。要对后置形式进行重载，即 x++ 或 x--，就必须为重载函数再增加一个 int 类型的参数。**该参数仅仅用来告诉编译器这是一个运算符后置形式，在实际调用时不需要给出实际的参数值。**    
```c
#include <iostream>   
using namespace std;  
class A    
{   
public:    
	A(int a) :num(a) {}   
	A operator++()	//无参数则前置自增   
	{   
		num++;    
		return *this;//返回的不是数字而是自己的实例   
	}   

	A operator++(int)	//一个形参int则代表后置自增   
	{    
		A temp = *this;   
		num++;     
		return temp;//后置++要返回原数据再自增，所以返回之前保存下来的copy  
	}   
	int Getvalue()   
	{    
		return num;   
	}   
private:  
	int num;  
};   

int main()   
{   
	A a1(10);   
	cout << a1.Getvalue() << endl;  
	a1.operator++();//实际上也能这么调用，但是不常用      
	cout << a1.Getvalue() << endl;   
	a1++;//后置加加并不需要加上形参int，形参只是为了个编译器区分这是后置自增。     
	cout << a1.Getvalue() << endl;  
	++a1;    
	cout << a1.Getvalue() << endl;    
	getchar();   
	return 0;   
}    
```   
4 操作符重载中针对友元函数的情况   

5 操作符重载中重载数据流的情况
