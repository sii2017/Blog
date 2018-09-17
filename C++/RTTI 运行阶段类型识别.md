# RTTI 运行阶段类型识别
RTTI是运行阶段类型识别（Runtime Type Identification)的简称。   
## RTTI用途
通常，在我们使用c++类时，会将基类的指针指向一个派生类的地址，来使用该派生类的一些函数。但是由于我们直接使用的是基类的指针，因此我们不知道，该派生类是哪个类型。   
那么我们该如何知道，基类指针指向的是哪个派生类的类型呢？    
在大多数情况下，我们不需要知道。由于虚函数以及多态的存在，当我们用基类指针指向派生类后，我们可以直接使用该指针来调用派生类已经重写的虚函数。   
然而当我们**没有办法使用虚函数的情况下**该怎么办呢？这时候我们就需要知道该基类的指针指向的派生类是什么类型，再根据该类型来进行安全的函数调用了。那么这时候RTTI可以提供解决方案。   
## RTTI的组成
C++有3个支持RTTI的元素。   
> dynamic\_cast运算符可以安全的将一个指向基类的指针来生成一个指向派生类的指针。失败则返回0。   
> typeid运算符返回一个指出对象的类型的值。   
> type_info结构存储了有关特定类型的信息。   
   
**注意：RTTI只适用于包含虚函数的类。因为RTTI需要虚函数表的支持。**   
**注意2：包含虚函数不等于能使用特定的虚函数，只有当我们没法使用特定的虚函数的时候才会去使用RTTI。**      
## dynamic\_cast运算符
dynamic_cast运算符是最常用的RTTI组件，它能告诉我们“是否可以安全地将对象的地址赋给特定类型的指针”。  
注意：与“指针指向的是哪种类型的对象”相比，“类型转换是否安全”更通用。   
有条件转换，动态类型转换，**运行时类型安全检查**：    
1. 安全的基类和子类之间的相互转换。    
2. 类中必须要有虚函数。   
3. 相同基类不同子类之间的交叉转换。但结果是NULL。  
4. 支持RTTI的元素之一，其他两个分别为typeid运算符和type\_info类。   
5. 只有当类中有虚函数，但是并不能定义我们需要的虚函数的时候，才会使用RTTI功能。   
6. 尽可以转换成指针、引用和右值引用三种。  
7. 我们可以对一个空指针执行dynamic\_cast，结果是所需要的类型的空指针。   
```c
class BaseClass {  
public:   
	int m_iNum;    
	virtual void foo(){}; //基类必须有虚函数。   
};   

class DerivedClass: public BaseClass {   
public:   
	char* m_szName[100];   
	void bar(){};   
};    

BaseClass* pb =new DerivedClass();   
DerivedClass *pd1 = static_cast<DerivedClass *>(pb); //子类->父类，静态类型转换，正确但不推荐    
DerivedClass *pd2 = dynamic_cast<DerivedClass *>(pb); //子类->父类，动态类型转换，正确    

BaseClass* pb2 =new BaseClass();    
DerivedClass *pd21 = static_cast<DerivedClass *>(pb2); //父类->子类，静态类型转换，危险！访问子类m_szName成员越界    
DerivedClass *pd22 = dynamic_cast<DerivedClass *>(pb2); //父类->子类，动态类型转换，安全的。结果是NULL     
```   
### 指针类型的dynamic\_cast
```c
#include <windows.h>  
#include <iostream>   
using namespace std;  

class base   
{  
public:   
	virtual void need(){}   
};  

class derived:public base   
{   
};   

int main()  
{   
	//基类转派生类会失败   
	base *pb= new base;  
	if(derived* db= dynamic_cast<derived*>(pb))   
	{  
		cout << "successful" << endl;  
	}   
	else    
		cout << "failed" << endl;  

	//派生类转基类会成功   
	derived* db1= new derived;  
	if(base* bp1= dynamic_cast<base*>(db1))   
		cout << "sucessful" << endl;     
	else   
		cout << "failed" << endl;   
	getchar();    
	delete pb;   
	delete db1;  
	return 0;    
}     
```   
由于转换指针转换失败会返回0，因此可以放在if条件中进行判断。   
### 引用类型的dynamic\_cast
```
#include <windows.h>  
#include <iostream>   
using namespace std;   

class base   
{  
public:   
	virtual void need(){}  
};   
   
class derived:public base  
{   
};   

int main()   
{  
	//依旧是基类转派生类失败。   
	base b1;   
	try{   
		derived& d1= dynamic_cast<derived&>(b1);   
	}catch(bad_cast)  
	{    
		cout << "基类转派生类falied" << endl;   
	}  

	//派生类转基类成功。   
	derived d2;   
	try{  
		base& b2= dynamic_cast<base&>(d2);   
	}  
	catch(bad_cast)   
	{   
		cout << "派生类转基类failed" << endl;   
	}   
	getchar();   
	return 0;    
}
```  
由于转引用失败返回的是异常而不是0，因此需要用try和catch来抓取。   
### dynamic\_cast小结
可以看到大部分情况下，基类的指针直接转子类都是失败，这看上去令人很困扰，那么这个转换对于基类转子类有什么用呢？
实际上，当基类的指针指向的是子类的地址，这时候将该指针转换成子类的类型，这是安全的。或者是基类的指针指向的是子类的子类的地址，这时候这个基类的指针（实际上是子类的子类）转换成子类，相当于子类转换成基类，是安全并且可以成功转换的。   
```c
#include <windows.h>  
#include <iostream>  
using namespace std;  

class base  
{  
public:   
	virtual void need(){}  
};  

class derived:public base  
{  
};  

int main()  
{   
	base* pb=new derived;  
	if(derived* pd= dynamic_cast<derived*>(pb))   
	{  
		cout << "successful" << endl;   
	}   
	else  
		cout << "failed" << endl;   
	delete pb;  
	getchar();   
	return 0;  
}
```
可以看出就基类与子类的互相转换而言，dynamic\_cast与static\_cast的区别是，对于dynamic\_cast而言，基类子类可以互相转换并且都是安全的（尽管基类转子类大概率失败），但是对于static\_cast而言，子类转换成基类是可以的，然而基类转换成子类是危险的，会造成内存越界。    
**为什么dynamic\_cast动态类型转换一定要虚函数呢？**    
Dynamic_cast转换是在运行时进行转换，运行时转换就需要知道类对象的信息（继承关系等）。而在运行时获取该信息的途径就是———虚函数表。   
在C++对象模型内存分布中，对象实例最前面的就是虚指针，指向虚函数表，通过这个指针可以获取到该类对象的所有虚函数，包括父类的。以及通过虚函数表-1的位置，可以得到type_info信息。      
因为派生类共用基类的虚函数表，所以通过这个虚函数表以及type_info信息，我们就可以知道该类对象的父类，在转换的时候就可以用来判断对象有无继承关系。     
## typeid运算符
typeid运算符的作用是在运行时确定对象的类型。   
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
## type_info类
第三个支持RTTI的就是type_info类了，但是关于这个类，少说一些，因为实际接触是通过typeid关键字，并不是通过这个类的。   
type_info类的精确定义对于不同的编译器有着略微的差异，但是C++规定要求该类必须至少提供以下的操作：   
> 1 t1==t2 支持两个type_info对象（即typeid的返回值）进行比较，返回true和false。   
> 2 t1!=t2 同上。   
> 3 t.name() 返回一天个C风格字符串，来表示类型名字。   
> 4 t1.before(t2) 返回一个bool值，表示t1是否位于t2之前。不过before采用的顺序关系是依赖于编译器的。    
 
type_info是没有默认构造函数的，它自己定义的构造函数为私有，是无法直接由我们来调用的。所以我们唯一使用这个类的方法就是使用typeid关键字。   
**关于具体的实现：在vs中，每个具有虚函数的类型的type\_info对象存放在虚函数表-1的位置上。当我们使用上面说到的dynamic\_cast和typeid的时候，都会访问位于虚函数表-1位置的type\_info对象存放的关于类型的信息。**   