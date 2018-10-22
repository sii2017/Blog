## sizeof空类相关问题
sizeof空类会有一些关于内存分配的知识盲点，在这里记录一下。   
关于sizeof关键字可以查看同目录下《sizeof关键字》的博客。  
### 以码说明
```c
#include <iostream>   

class A  
{   
  
};   
  
class B     
{  
public:   
	B() {}  
	void function(int a)   
	{  
		int b;  
		b = a;  
		return;  
	}   
};  

class C  
{   
	int a;	//4  
};  

class D  
{  
	int a;	//4  
	char b;	//1   
};  
  
class E 
{   
public:   
	virtual void function() {}  
private:  
	char a;  
};   

class F: public E   
{  
public:  
	virtual void function(){}   
private:  
	int d;  
};   

class G  
{  
	static double d;    
};  

class H : public virtual E   
{  
	double c;	//8  
};   

int main()   
{   
	cout << sizeof(A) << endl;	//1 即使是空类只要它可以被实例化，就需要分配空间才能被使用   
	cout << sizeof(B) << endl;	//1 成员函数无论是构造函数还是其它成员函数，都不会占用空间   
	cout << sizeof(C) << endl;	//4 当类内有成员需要占用空间了，那之前占位的1子节就不再需要了，不用将其计算在内。int在32位占用4个子节，在64位占用8个子节   
	cout << sizeof(D) << endl;	//8 考察了类和结构体的子节对齐    
	cout << sizeof(E) << endl;	//8 类中只要有虚函数，就会有一个隐藏的虚指针指向虚函数表，指针占用4个子节。加上a为5个子节，对齐到8    
	cout << sizeof(F) << endl;	//12 类中哪怕有多个虚函数也只有一个虚指针，为4，父类的a占用1，自己的d占用4，总的为9，对齐到12   
	cout << sizeof(G) << endl;	//1 静态变量存储在静态全局区，不属于实例的一部分，不占用空间，仅仅用1个子节占位。   
	cout << sizeof(H) << endl;	//24 如果是虚继承的话，派生类拥有自己的虚指针，    
	getchar();   
	return 0;  
}   
```   
### 总结
1 一个空类理论桑是不占用资源的，但是为了使其可以被实例化，编译器一般会分配少许子节给它占用一定的空间。Microsoft visual studio编译器通常分配1个子节。   
> 当一个类有任何可以占用空间的变量，之前占位的一个子节不再被分配，意味着不再被计入。   
   
2 类的构造函数，析构函数，成员函数，是不占用类的实例空间的。   
3 类的成员变量会占用空间。   
4 静态成员变量将会被分配在静态/全局区，不属于类的实例，不会占用类的存储空间，因此不会被siezof检测到。   
5 如果一个类有虚函数，虚函数本身与正常函数一样不占用空间，但是有虚函数意味着就会有隐形的虚指针，指针占用4个子节。   
6 如果类有继承关系，那么子类占用的空间为派生类占用的空间加上自己占用的空间。对于一个有或者继承虚函数的类来说，虚指针有且永远只有一个。   
7 与c的结构体相似，类的实例占用的内存也要遵从对齐原则。   
8 虚继承。    