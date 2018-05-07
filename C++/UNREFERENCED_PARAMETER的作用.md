## UNREFERENCED_PARAMETER的作用
UNREFERENCED_PARAMETER是一个宏，其定义在winnt.h下：  
```c
#define UNREFERENCED_PARAMETER(P) (P)   
```   
换句话说 UNREFERENCED_PARAMETER 展开传递的参数或表达式。其目的是**避免编译器关于未引用参数的警告**。    
在一些情况下，程序员会使用最高级别的警告Level 4(/W4)进行编译。Level 4 属于“能被安全忽略的事件”的范畴。虽然它们可能使你难堪，但很少破坏你的代码。   
当我们的程序中有这样一些代码：  
```c
int x=1;   
```   
但是我们在代码中从未用过x这个参数，有可能是以前使用的，后来删除了调用过程但是没有删除定义。那么Warning Level 4会找到他并且警告。     
再比如一个函数带来两个参数，但你只使用其中一个：   
```c   
int SomeFunction(int arg1, int arg2)    
{     
	return arg1+5;    
}        
```    
编译器会提示：   
“warning C4100: ''arg2'' : unreferenced formal parameter.”   
此时可以加上UNREFERENCED_PARAMETER(arg2)。那么编译器在编译你的引用 arg2 的函数时便会住口。并且由于语句：  
arg2;   
实际上不做任何事情，编译器不会为之产生任何代码，所以在空间和性能上不会有任何损失。   