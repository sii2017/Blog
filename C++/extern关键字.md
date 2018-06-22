## extern关键字
extern关键字有三种用途：  
1 通过extern "C"修饰的函数表明，该函数不要用c++的方式来编译，而要用c的方式来编译。  
2 通过extern修饰的变量和函数表示该变量定义在别的文件里，编译器在编译的时候不要在本文件中找定义。如此编译器在本文件中没找到定义的时候就不会报错，而去别的文件中找了。   
### extern修饰变量和函数
在C语言中，修饰符extern用在变量或者函数的声明前，用来说明“**此变量/函数是在别处定义的，要在此处引用**”。   
extern是声明不是定义，即不分配存储空间。   
```c
//test.cpp  
#include <iostream>   
using namespace std;  
int a= 2;   

void function()  
{  
	cout << a << endl;   
}   

//main.cpp  
#include <iostream>   
using namespace std;   

extern int a;  
extern void function();    

int main()   
{   
	cout << a << endl;//调用test.cpp中的a  
	function();//调用test.cpp中的function函数   
	 
	getchar();    
	return 0;  
}   
```    
如果没有这两个extern关键字的声明，main中的调用会报错。但是加上后，就能使用test.cpp中的变量和函数了。   
### extern "C"
extern "C"的主要作用就是为了能够正确实现C++代码调用其他C语言代码。加上extern "C"后，会指示编译器这部分代码按C语言的进行编译，而不是C++的。   
**extern "C"的惯用法:**   
（1）在C++中引用C语言中的函数和变量，在包含C语言头文件（假设为cExample.h）时，需进行下列处理：   
```c
extern "C"   
{   
#include "cExample.h"   
}   
```  
（2）在C中引用C++语言中的函数和变量时，C++的头文件需添加extern "C"，但是在C语言中不能直接引用声明了extern "C"的该头文件，只需要在C源文件中将C++中定义的extern "C"函数声明为extern类型。  
```c
//C++头文件 cppExample.h  
#ifndef CPP_EXAMPLE_H  
#define CPP_EXAMPLE_H   
extern "C" int add( int x, int y );//声明该函数以C的方式编译      
#endif    
//C++实现文件 cppExample.cpp  
#include "cppExample.h"  
int add( int x, int y )   
{   
	return x + y;  
}   

// C实现文件 cFile.c    
/* 这样会编译出错：#include "cppExample.h" */   
extern int add( int x, int y );//声明该函数在外部     
int main( int argc, char* argv[] )   
{  
	add( 2, 3 );  
	return 0;   
}   
```  
**总结**    
C和C++对函数的处理方式是不同的。  
extern "C"是使C++能够调用C写的库文件的一个手段，如果要对编译器提示使用C的方式来处理函数的话，那么就要使用extern "C"来说明。   