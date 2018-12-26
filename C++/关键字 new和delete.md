# 关键字new和delete
在c++中，分配内存的方式大抵有三种。  
一种是自动变量，也成为局部变量，栈变量，是在栈上进行分配的。他们的链接性为内部，当作用域结束则被系统自动释放/回收。他们被存储在栈区。   
第二种是静态变量/全局变量。他们在程序开始的时候初始化一次，静态变量和全局变量的作用域都是全局，静态变量的连结性为内部，而全局变量的连结性为外部可被其它文件调用。直到程序结束，由系统自动释放回收他们。他们被存储在静态全局存储区。   
第三种是本篇博客要说的，动态变量。通过关键字/运算符new来进行分配。   
## new 动态分配内存
new的使用在于运行时动态的分配内存。  
它是c++用来替代malloc和free的方式，而new和delete与malloc和free的区别可以参考同目录下《new和malloc的区别》。   

new运算符的使用方式如下：  
```c
type* t1= new type;   
type* t2= new type(value);   
type* t3= new type{value};  
```   
当new申请成功则返回该内存的地址，所以一般需要以指针来接受。   
如果new申请内存失败，没有找到空余的内存，那么会出现bad\_alloc异常。   
### new不跳异常的方式
有些编译器提供一个标记，让用户选择，当new分配内存失败的话，不会出现bad\_alloc异常而仅仅返回空指针。   
```c
int* num= new(std::nothrow) int;   
```   
这样我们在处理代码的时候，仅仅需要检查返回的这个指针是不是空指针，就可以知道这个动态分配成功还是失败了。  
## delete 动态释放内存
delete关键字是用来释放new申请的内存。  
与malloc和free相似，动态申请的内存必须由程序员手动来释放。同时需要了解，malloc和free与new和delete必须对应使用，混合有可能会造成不可预料的结果。   
delete运算符的语法如下：   
```c
delete t1;  	//直接delete指针名即可  
t3= t2;  
delete t3;   //由于t3指向t2的地址，因此delete t3相当于释放了t2指向的内存空间   
delete t2;   //error。由于t2指向的空间已经被t3释放了，重复释放将会出现无法预料的问题。   
//t3原本指向的内存空间没有被释放，长此以往有可能会造成内存泄漏，且难以被发现。   
```   
## 为数组动态分配和释放内存
当为数组分配内存的时候更体现了动态分配的优势。  
打个比方，一般我们在栈上声明数组的话，需要在编译的时候就要确定申请的内存数量。   
```c
const int n = 10;   
int num1[n];		//valid  
int v = 10;	//如果通过运行时赋值     
int num2[v];		//invalid   
const int w = v;   
int num3[w];	//invalid 即使将v赋值给一个const int   
```   
可以看到如果我们要使用一个int数组，我们必须在编译的时候就确定好内存的大小，而不能在运行时通过赋值来确认。  
而new打破了这种局限。   
```c
int value = 10;		//在运行时通过赋值来获得需要的内存的数量   
int* num = new int[value];	//通过[]运算符来进行多个数量的内存分配     
delete[] num;	//如果new中有[]则delete的时候也要有[]。   
```   
## new中包含的重载
运算符new和new[]分别调用如下函数：   
```c
void* operator new(std::size_t);   //used by new  
void* operator new[](std::size_t);   //used by new[]  
```   
这些函数被成为分配函数（allocation function），它们位于全局名称空间中。同样，也是由delete和delete[]调用的释放函数（deallocation function）。   
```c
void operator delete(void*);   
void operator delete[](void*);    
```   
std::size_t是一个typedef，对应于合适的整型。对于下面这样的基本语句：   
```c
int* pi= new int;  //将被转换为   
int* pi= new(sizeof(int));  

int* pa= new int[40];  //将被转换为   
int* pa= new(40 * sizeof(int));   
```   
使用运算符new的语句时也可能包含初始值，因此使用new运算符的时候，可能不仅仅是调用new()函数。   
同样，delete的语句转化如下：   
```c
delete pi;	//被转换为   
delete(pi);   
```   
## 定位new运算符
通常，new负责在堆中找到一个足以满足要求的内存块。new运算符还有另外一种变体，被成为定位（placement）new运算符，它可以让我们指定使用特定位置的内存。   
程序员可以使用这种特性来设置其内存管理规程、处理需要通过特定地址进行访问的硬件或在特定位置创建对象。   
要使用这种定位new特性，需要包含头文件new。   
```c
#include <new>    
```   
句法与一般的new没有太大区别，只不过定位new运算符需要多一个参数，即所需的内存地址。  
```c
char buffer1[50];   
char buffer2[500];
int* p1= new (buffer1) int;  
int* p2= new (buffer2) int[10];   
```   
可以看到，new也支持单个内存以及复数内存的申请，但是需要先有一个内存的地址。  
这里，由于buffer1和buffer2都是栈内存，所以我们不能对p1和p2进行delete，栈内存不能被动态释放，会引发错误。   
```c
delete p1;	//error   
delete[] p2; //error too!   
int* p3= new (buffer1) int;   
int* p4= new (buffer2+ 10*sizeof(int)) int[10];   
```  
上面的p3，由于使用了和p1同样的一块内存，因此p1被覆盖了，不存在了。   
p4使用了p2同一块内存，但是它使用了buffer2加上p2使用的大小的偏移量，避免了覆盖p2。   
### 定位new运算符delete的使用
```
char buff1[100];   
int* buff2 = new int[100];   
int* p1 = new (buff1) int[10];	//通过栈内存buff1进行定位分配内存   
int* p2 = new (buff2) int[10];	//通过堆内存buff2进行定位分配内存  
```   
对于定位new运算符，我们不需要对该内存进行释放，因为我们只是“借用”，而不是申请。  
当然，“借用”不用释放，而原本的使用者是需要释放的，如果有必要的话。   
对于p1来说，p1是借用者，而buff1是使用者，buff1本身是需要进行释放的。由于buff1是栈内存，由系统进行分配和回收，我们不用主动去释放他。等超出作用域，生命周期结束后，系统自动会释放它。  
对于p2来说，p2是借用者，而buff2是内存的使用者。buff2是通过new来分配的，是堆内存，因此我们需要通过delete[] buff2来进行释放空间。   
由于p2和buff2理论上指向的是同一个位置，因此delete p2也是可以的。  
### 定位new运算符中类的注意事项
当定位new运算符用域类对象时，情况将更复杂。   
当我们类的对象是局部变量（栈）或者普通new申请的动态对象（堆）时，当释放他们的时候，类都会自动调用该对象的析构函数，正常完成析构。  
```c
class T  
{  
public:  
	T()   
	{  
		cout << "call T()" << endl;  
	}  

	~T()  
	{   
		cout << "call ~T()" << endl;   
	}  
};  
   
int main()   
{     
	{   
		T t1;	//局部对象，退出局部后自动调用析构函数   
	}  
	T* t2 = new T;	   
	delete t2;	//动态对象，delete释放内存的时候自动调用析构函数    

	{   
		char buff1[100];	   
		T* t3 = new (buff1) T;	//通过定位new操作符，在局部栈内存生成t3，但是内存回收时不会调用t3的析构函数   
	}   

	int* buff2 = new int[100];   
	T* t4 = new(buff2)T;	//通过定位new操作符，在动态内存生成t4   
	delete buff2;	//删除buff2空间不会调用t4的析构函数   
```
可以看到，当我们实例化类对象的时候，普通的局部变量和动态变量，当变量被释放的时候系统都会正常调用析构函数。   
但是当我们使用定位new操作符生成对象，则只会在实例化的时候调用构造函数而不会在释放的时候调用析构函数。   
这是典型的“管杀不管埋”，会造成内存泄漏。   
所以在使用new定位操作符为类生成对象的时候要注意，当释放内存空间的时候，手动调用析构函数。   
```c
t3->~T();   
t3->~T();   
```   
另外，如果两个对象依次在同一个内存空间里，比如：   
```c
int* buff = new int[100];   
T* t1 = new(buff)T;   
T* t2 = new(buff+ sizeof(T)) t;  
```   
在手动析构他们的时候需要注意，要按后进先出的顺序来析构，即与创建顺序相反的顺序进行删除。原因在于，晚创建的对象可能依赖于早创建的对象。   
```c
t2->~T();   
t1->~T();   
```   
当所有对象都被销毁后，才能释放用域存储这些对象的缓冲区。   
```c
delete[] buff;   
```   
## 总结
1 new后必须delete。new[]后必须delete[]。   
2 new和delete与malloc和free不能混用。   
3 对于用new定位操作符实例化的对象要手动调用析构函数来释放空间避免内存泄漏。  
4 一个new对应一个delete，但是定位new运算符不需要delete。   