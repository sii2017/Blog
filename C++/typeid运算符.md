## typeid运算符
typeid运算符的作用是在运行时确定对象的类型。   
关键字：运行时，确定对象类型。   
由于c++有着多态的特性，基类指针会由于多态而实际上指向子类，并使用子类的虚函数。并且多态在编译期间是无法被确定的，因此当我们在运行时需要做出判断时，就可以使用typeid运算符来进行确定。   
### typeid的使用方法
typeid的结果是const type_info&。 该值是对表示 type-id 或 expression 的类型的 type_info 对象的引用，具体取决于所使用的 typeid 的形式。  
```c
#include <windows.h>  
#include <iostream>  
#include <typeinfo.h>  
using namespace std;  
  
class Base  
{   
public: 
	virtual void output()   
	{   
		cout << "out put is class Base" << endl;  
	}   
};   

class A: public Base   
{  
public:   
	virtual void output()  
	{
		cout << "output is class A" << endl; 
	}
};

class B: public Base
{
public:
	virtual void output()
	{
		cout << "output is class B" << endl;
	}  
};  

struct C: public Base   
{  
	virtual void output()  
	{  
		cout << "output is struct C" << endl;   
	}  
};   

int main()  
{  
	A a;   
	B b; 
	C c;   
	Base& refBase1= a; 
	refBase1.output();	//output is class A   
	Base& refBase2= b;  
	refBase2.output();	//output is class B  
	Base& refBase3= c;  
	refBase3.output();	//output is class C   

	cout << typeid(refBase1).name() << endl;	//class A  
	cout << typeid(refBase2).name() << endl;	//class B  
	cout << typeid(refBase3).name() << endl;	//struct C    

	A* ptra= new A();   
	Base* ptrBase= ptra;   
	cout << typeid(ptrBase).name() << endl;	//class Base*   
	cout << typeid(*ptrBase).name() << endl;	//class A   

	delete ptra;  
	getchar();  
	return 0;  
}   
```   
1 值得注意的是，必须取消引用指针以使用它指向的对象。 如果未取消引用指针，结果将是指针的type_info，而不是它指向的内容。（而指针的type_info实际上就是静态编译时的类型，也就是它看上去的类型，而不是实际指向的地址的类型。）     
> 如上面，直接typeid(ptrBase)，产生的就是class Base*类型，而取消引用指针后，就显示实际多态指向的类型A。   
> 而当我们typeid引用的时候，则不用取消引用指针，可以直接获取类型。   
   
2 如果expression正在取消引用某个指针，并且该指针的值是零， typeid将引发bad_typeid异常。 如果该指针没有指向有效的对象，则会引发
\_\_non\_rtti\_object 异常来指示尝试了分析引发错误（如访问冲突）的RTTI，因为该对象在某种程度上是无效的（无效的指针或代码不是用/GR编译的）。    
3 如果expression既不是指针也不是对对象的基类的引用，只是一般的实例，则结果是表示expression的静态类型的type_info引用，即表达式将引用在编译时已知的表达式的类型。并且忽略执行语义，即忽略运行时实际多态的情况。       
4 typeid是否会进行运行时检查，取决于类型是否含有虚函数。如果类型没有虚函数，则不会进行运行时检查，而直接返回静态编译时的类型。   
5 在确定表达式的静态类型时，将忽略引用：  
```c
#include <typeinfo>    
  
int main()    
{  
   typeid(int) == typeid(int&); //int为确定表达式，那么就忽略引用，int&就是int   
}  
```   
6 typeid运算符不适用于抽象声明符或实例。   
7 不通过name直接进行比较也是可以获取到类型的：   
```c
#include <windows.h>   
#include <iostream>  
#include <typeinfo.h>   
using namespace std;  

class Base  
{   
public:   
	virtual void need(){}  
};   

class Derived: public Base   
{  
};    

int main()   
{  
	Base* pb= new Derived;   
	Derived* pd= new Derived;  
	if(typeid(*pb)==typeid(*pd))   
		cout << "他们是同一个类型" << endl;  	//输出这里
	else   
		cout << "他们不是同一个类型" << endl;   
	delete pb;   
	delete pd;  
	getchar();   
	return 0;  
}   
```   