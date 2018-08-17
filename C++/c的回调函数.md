## c的回调函数
回调函数就是一个通过函数指针调用的函数。如果你把函数的指针（地址）作为参数传递给另一个函数，当这个指针被用来调用其所指向的函数时，我们就说这是回调函数。    
**回调函数不是由该函数的实现方直接调用**，而是在特定的事件或条件发生时由另外的一方调用的，用于对该事件或条件进行响应。   
### 回调函数的意义
1 回调函数并不是实现者用来自己直接调用的，而是用来作为指针以参数的形式被其它人/函数进行调用。  
2 回调函数将调用者与被调用者进行了分离。调用者不用知道回调函数的实际内容，只要知道这个函数指针可以解决问题即可。被调用者不需要知道调用者的情况，只需要提供这种方法即可。这使函数的使用变得更灵活。   
### 例子
```c
#include <iostream>  
using namespace std;  
  
void print1()  
{  
	cout << "call back function" << endl;  
}   

void print2()  
{  
	cout << "caller can choose the function" << endl;  
}  

void PrintWhatIWant(void (*function)())  
{  
	function();  
}  

int main(int argc, char** argv)  
{  
	PrintWhatIWant(print1);  
	PrintWhatIWant(print2); 
	getchar();  
	return 0;  
}   
```  
以上例子可以看出：  
1 print1和print2两个函数作为两个输出的方式，是否调用他们取决于调用者。   
2 PrintWhatIWant函数的参数为一个返回为空参数为空的函数的地址，这个函数可以看作输出文字的一个接口，但是他具有一定的灵活性，想输出什么就放入什么函数，而不用重新写一个函数。   
2.1 灵活性在代码中很重要，意味着我们可以复用代码，同样用在一些，需要使用不同类型的情况，需要使用不同参数的情况下。（在c++中我们使用函数重载以及模板来解决这些问题）    
3 print1和print2并不是被直接调用，而是作为参数传递给PrintWhatIWant来进行调用的，这就是我们说的回调。   
4 print1和print2这两个函数与PrintWhatIWant是完全分离的，PrintWhatIWant也可以以其它合适的函数作为参数，如果有的话。   