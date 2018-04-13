## C++模板 template用法
模板（Template）指C++程序设计语言中采用类型作为参数的程序设计，支持通用程序设计。C++ 的标准库提供许多有用的函数大多结合了模板的观念，如STL以及IO Stream。   
### 函数模板
先举一个简单的例子，以下函数：  
```c
void swap(int& a, int& b)    
{    
	int temp= a;    	
	int a= b;    
	b= temp;    
}    
```    
这个函数以引用传参的方式来交换a和b的值。然而，它只针对int类型的值，如果要支持long，string类型，这个函数就无法使用了。     
那么一般情况下，如果要支持别的类型，需要重新定义一个（或多个）极度相似的函数（仅仅将int类型改变成其它需要的类型）。    
如果使用函数模板，就不用定义重复的函数，只需要使用一个函数及模板，就能在不同类型的数据上复用了。     
函数模板的声明形式如下：     
```c   
template <class identifier> function_declaration;     
template <typename identifier> function_declaration;   
```     
之前的swap函数模板的声明和定义如下：   
```c   
//method.h
template<typename T> viod swap(T& t1, T& t2);	//声明   

#include"method.cpp"//这里使用swap函数，必须包含swap的定义，否则编译会出错，这个和一般的函数使用不一样。所以必须在method.h文件的最后一行加入#include "method.cpp"。     
   
//method.cpp    
template<typename T> void swap(T& t1, T& t2)   //定义   
{    
	T temT;    
	tmpT= T1;   
	T1= T2;   
	T2= tempT;    
}     
   
//main.cpp    
#include <stdio.h>    
#include "method.h"    
int main()    
{    
	int num1= 1, num2= 2;    
	swap<int>(num1, num2);     
	printf("num1:%d, num2:%d\n", num1, num2);     
	return 0;     
}   
```      

## 类模板
考虑我们写一个简单的栈的类，这个栈可以支持int类型，long类型，string类型等等。如果不利用类模板，我们就要写三个以上的stack类，其中代码基本一样。而通过类模板，我们可以定义一个简单的栈模板，再根据需要实例化为int栈，long栈，string栈。     
```c
//stack.h
template<class T> class Stack	//注意这里的格式    
{     
public:     
	Stack();   
	~Stack();    
	void push(T t);   
	T pop();     
	bool isEmpty();   
private:    
	T* m_pT;   
	int m_maxSize;   
	int m_size;    
};    

#include "stack.cpp" 		//注意在h文件最后一行需要包含cpp文件    

//stack.cpp     
template<class T> Stack<T>::Stack()	//注意这里的格式     
{    
	m_maxSize= 100;    
	m_size= 0;    
	m_pT= new T[m_maxSize];   
}     

template<class T> Stack<T>::~Stack()    
{     
	delete []m_pT;    
}    
    
template<class T>void Stack<T>::push(T t)    
{     
	m_size++;     
	m_pT[m_size-1]= t;    
}    
    
template <class T> T Stack<T>::pop()     
{    
    T t = m_pT[m_size - 1];    
    m_size--;   
    return t;    
}   
    
template <class T> bool Stack<T>::isEmpty()    
{    
    return m_size == 0;      
}   
    
//main.cpp     
#include <stdio.h>   
#include "stack.h"    
int main()      
{   
    Stack<int> intStack; 	//注意这里的格式   
    intStack.push(1);   
    intStack.push(2);   
    intStack.push(3);     
    
    while (!intStack.isEmpty())     
	{         
        printf("num:%d\n", intStack.pop());     
    }    
    return 0;   
}       
```    
在声明文件stack.h中，只要在class前加上template<class T>就可以了。注意这里也需要在文件最后一行加入“包含cpp文件”的声明。    
在定义文件stack.cpp中，除了在开头加入template<class T>以外还需要将类名写成Stack<T>。   
在main.cpp中使用模板类的时候，在类名后加入类型来具现化该模板类：   
```c   
//以下都可以
Stack<int> intStack;      
Stack<string> strStack;    
Stack<double> douStack;     
```
## 模板参数
模板中可以加入参数这个概念，如果使用者没有进行设置，那我们还可以加入缺省参数的概念。例如：   
```c
template<class T, T def_val> class Stack{...}    
```   
在上一个模板中，我们可以用模板参数配置这个栈的最大元素数， 如果使用者不进行配置，则我们可以将其设为100个，代码如下：   
```c
//stack.h    
template <class T,int maxsize = 100> class Stack   //这里注意，我们在<>中设置了一个参数，并且设置了缺省值     
{       
public:   
    Stack();   
    ~Stack();  
    void push(T t);     
    T pop();    
    bool isEmpty();   
private:    
    T *m_pT;            
    int m_maxSize;   
    int m_size;   
};  
   
#include "stack.cpp"	//这里同样需要注意     
   
//stack.cpp    
//模板括号<>加入了参数以后需要同样写在定义中，如同普通的缺省参数一样，缺省值只写在声明里就行了。    
template <class T,int maxsize> Stack<T, maxsize>::Stack()
{        
   m_maxSize = maxsize;   //这里将模板参数定义给了最大值          
   m_size = 0;    
   m_pT = new T[m_maxSize];   
}     
template <class T,int maxsize>  Stack<T, maxsize>::~Stack()    
{    
   delete [] m_pT ;   
}       
        
template <class T,int maxsize> void Stack<T, maxsize>::push(T t)     
{     
    m_size++;    
    m_pT[m_size - 1] = t;       
}    
template <class T,int maxsize> T Stack<T, maxsize>::pop()
{    
    T t = m_pT[m_size - 1];   
    m_size--;   
    return t;    
}      
template <class T,int maxsize> bool Stack<T, maxsize>::isEmpty()     
{    
    return m_size == 0;    
}    
     
//main.cpp   
#include <stdio.h>   
#include "stack.h"     
int main()      
{    
    int maxsize = 1024;     
    Stack<int,1024> intStack;	//这里对模板参数进行了传值，如果不传则为缺省值100     
    for (int i = 0; i < maxsize; i++)     
	{    
        intStack.push(i);  
    }    
    while (!intStack.isEmpty())     
	{      
        printf("num:%d\n", intStack.pop());    
    }    
    return 0;    
}               
```
需要注意的是，在加入模板参数后，声明与定义的函数名称也会有相应的改变。    
模板参数的缺省参数的改变与一般的缺省参数一致，在声明中写出缺省值后，定义的时候不用再重复写。  
实例化class的时候，参数直接写在模板类型后就可以了：    
```c
Stack<int,1024> intStack;    
```    

## 模板专门化  
当我们要定义**同一个模板的特定（specific）实现**，即当常规的类模板无法满足某一种情况时，为了处理这种特定的情况，又不用重新写一个新的模板，我们可以使用模板的专门化。    
### 函数模板专门化
假设我们swap函数要处理一个情况，我们有两个很多元素的vector<int>,在使用原来的swap函数，执行tmpT = t1要拷贝t1的全部元素，占用大量内存，将会造成性能下降。于是我们系统通过别的方法，即vector类本身的swap函数解决这个问题,而不适用我们模板中的方法。代码如下:     
```c
//method.h  //头文件中和之前一样   
template<class T> void swap(T& T1, t& T2);    
   
#include "method.cpp"     
   
//method.cpp  
using namespace std;    
template<class T> void swap(T& t1, T& t2) 	//该函数与之前一样       
{     
	T tmpT;    
	tmpT= t1;   
	t1= t2;    
	t2= tmpT;   
}   

//注意：template<>前缀表示这是一个专门化,描述时不用模板参数。注意这里的格式，template后的括号为空，函数的参数则为确定类型的参数。     
//在这里进行定义后，仅当遇到使用swap函数且参数为vector<int>的情况下，会调用这个专门化模板，而不使用上面的模板。    
template<> void swap(std::vector<int>& t1, std::vector<int>& t2)    
{    
	t1.swap(t2); //使用vector自身的swap来节省资源     
}     
   
//main.cpp  //以下为在main中的调用   
#include <stdio.h>    
#include <vector>    
#include <string>    
#include "method.h"    
int main()     
{     
    using namespace std;    
    //模板方法    
    string str1 = "1", str2 = "2";    
    swap(str1, str2);//这里使用的是swap的默认模板方式    
    printf("str1:%s, str2:%s\n", str1.c_str(), str2.c_str());     
    
    vector<int> v1, v2;    
    v1.push_back(1);   
    v2.push_back(2);    
    swap(v1, v2);//这里使用了swap的专用模板方式    
    for (int i = 0; i < v1.size(); i++)     
	{    
        printf("v1[%d]:%d\n", i, v1[i]);    
    }    
    for (int i = 0; i < v2.size(); i++)    
	{    
        printf("v2[%d]:%d\n", i, v2[i]);    
    }    
    return 0;    
}     
```   
然后vector<int>由于没有使用原始模板的T类型，而是专门化模板，没有办法应对除了int以外的vector，可以这么进行修改：   
```c   
template<class V> void swap(std::vector<V>& t1, std::vector<V>& t2)    
{    
	t1.swap(t2);   
}    
```    
我们将原来空的括号，设定了class V这个参数，并且后面使用V类型来应对不同的数据类型。   
### 类模板专门化    
先看以下的compare代码：   
```c   
//compare.h    
template <class T>   
class compare    
{    
public:    
bool equal(T t1, T t2)   
{    
     return t1 == t2;    
}     
};    
//这里由于声明和定义都在h文件里了，没有compare.cpp文件也就不需要在最后包含cpp文件了。    
     
//main.cpp     
#include <iostream>    
#include "compare.h"     
int main()  
{   
	using namespace std;  
	char str1[] = "Hello";    
	char str2[] = "Hello";   
	compare<int> c1;    
	compare<char *> c2;      
	cout << c1.equal(1, 1) << endl;        //比较两个int类型的参数    
	cout << c2.equal(str1, str2) << endl;   //比较两个char *类型的参数    
	return 0;    
}    
```   
到这里为止只是基本的类模板的操作。但是以上模板，如果模板参数是char指针时，就不能正常工作了，由于指针指向的是地址，地址永远不会相等，永远只能返回false。为此需要如下修改：   
```c    
//compare.h   
#include <string.h>    
template <class T> class compare   //这里还是老样子进行定义  
{    
public:    
	bool equal(T t1, T t2)    
	{    
       return t1 == t2;    
	}   
};   
   
template<>class compare<char *>  //定义专门化类  
{    
public:    
    bool equal(char* t1, char* t2)   
    {    
        return strcmp(t1, t2) == 0;    
    }   
};    
```   
如此char*就能进行正常的比较了，当且仅当参数为char指针时，会使用下面的专门化模板。   
需要注意的是，模板专门化一定要在已经使用模板的情况下才能使用。（经测试，初始模板如果注释的话，专门化模板无法被编译器编译）   
模板专门化的template后的括号并非只能为空，如果有需要也可以加入参数。   
模板专门化的概念与函数重载类似，只是函数重载针对的是“参数的数量”，而模板专门化针对的是“参数的类型”。   
## 模板类型转换   
先看如下代码：    
```c
//shape.h    
class Shape{};    
class Circle: public Shape{};       
    
//main.cpp    
#include <stdio.h>    
#include "stack.h"   
#include "shape.h"     
int main()    
{    
    Stack<Circle*> pcircleStack;    
    Stack<Shape*> pshapeStack;     
    pcircleStack.push(new Circle);   
    pshapeStack = pcircleStack; 	//wrong    
    return 0;   
}   
```   
这种情况下是无法编译的，因为尽管Shape是circle的父类，子类可以赋值给父类，但是他们作为类指针数组就不再是继承关系了。   
然而有时候我们却希望代码可以这么工作，因此我们可以定义转换运算符，代码如下：   
```c
//stack.h   
template <class T> class Stack     
{      
public:    
	Stack();   
	~Stack();   
	void push(T t);    
	T pop();   
	bool isEmpty();     
	template<class T2> operator Stack<T2>();   
private:    
	T* m_pT;   
	int m_maxSize;   
	int m_size;    
};    

#include "stack.cpp"     

//stack.cpp    
template <class  T>  Stack<T>::Stack()   
{     
   m_maxSize = 100;         
   m_size = 0;   
   m_pT = new T[m_maxSize];    
}    
template <class T>  Stack<T>::~Stack()     
{   
   delete [] m_pT ;    
}    
        
template <class T> void Stack<T>::push(T t)    
{   
    m_size++;   
    m_pT[m_size - 1] = t;   
}     

template <class T> T Stack<T>::pop()    
{   
    T t = m_pT[m_size - 1];    
    m_size--;   
    return t;   
}    

template <class T> bool Stack<T>::isEmpty()      
{   
    return m_size == 0;   
}    

//这里是新加的内容：类型转换函数搭配模板中的模板   
//每当类的实例以Stack形式（仅针对该类型）被赋值，则都会调用一次该函数。   
template <class T> template <class T2>  Stack<T>::operator Stack<T2>()     
{   
    Stack<T2> StackT2;    
    for (int i = 0; i < m_size; i++)    
	{    
        StackT2.push((T2)m_pT[m_size - 1]);    
    }   
    return StackT2;   
}   

//main.cpp
#include <stdio.h>   
#include "stack.h"     
#include "shape.h"    
int main()      
{    
    Stack<Circle*> pcircleStack;   
    Stack<Shape*> pshapeStack;    
    pcircleStack.push(new Circle);
	//当含有类型转换函数的类发生赋值时，就会调用类型转换函数    
    pshapeStack = pcircleStack;    
    return 0;    
}    
```   
这样，Stack<Circle>或者Stack<Circle指针>就可以自动转换为Stack<Shape>或者Stack<Shape指针>   
这是在模板类中使用了第二种模板（针对vector）并结合operator类型转换功能对子类和基类进行了类型转换。     
由于语句较为复杂，做一个小分析。   
```c
template <class T>（以上为外层类模板的函数固定句式）   
template <class T2>（以上为声明内层模板的语句，并非函数句式）    
Stack<T>::operator（operator即是关键词也是函数名称）        
Stack<T2>（这里应该是针对的需要被转换的类型）()     
```    
## 其它
一个类没有模板参数，但是成员函数有模板参数是可行的，就如同给一般的函数套模板一样。代码如下:    
```c
class Util 			
{    
public:     
	template <class T> bool equal(T t1, T t2)    
	{    
		return t1 == t2;    
    }    
};     

int main() 	    
{   
    Util util;    
    int a = 1, b = 2;   
    util.equal<int>(1, 2);    
    return 0;   
}      
```