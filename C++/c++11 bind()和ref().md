## c++11 bind()   
与std::function()相关，bind返回值是function类型的对象。   
那么bind函数与function函数有什么区别呢？  
从同目录下《c++11 function()》我们可以知道，function可以声明一个可调用对象，我们可以将各种可调用对象赋值给它。   
以及，function函数是可以像原来的函数一样使用的，给予他对应的参数。   
**而bind函数，则是可以提前将参数与function对象进行绑定。**   
### 头文件
```c
#include <functional>   
```   
bind与function一样，在std名字空间中。   
### 代码   
```c
void fun(int& a, int& b)
{
	cout << a << ", " << b << endl;
}

int main()
{
	int a = 1;
	int b = 2;

	auto f1 = bind(fun, a, b);	//支持提前将参数与函数绑定起来，并返回function类型的对象
	f1();	//1, 2

	//f1 = bind(fun, placeholders::_1, placeholders::_2);		//error,不支持重复赋值

	auto f2 = bind(fun, placeholders::_1, placeholders::_2);	//也支持不绑定参数。
	f2(a, b);	//1, 2

	auto f3 = bind(fun, placeholders::_2, placeholders::_1);	//可以看到placeholders实际绑定的是参数的位置。  
	f3(a, b);	//2,1

	auto f4 = bind(fun, placeholders::_1, b);	//也可以只绑定一部分参数，另外一部分参数后面设置
	f4(a);	//1, 2

	getchar();
	return 0;
}
```
可以看到通过bind函数，我们可以提前绑定好固定的参数，也可以绑定部分，空出部分。   
注意placeholder::\_x，x这个参数代表的是，从已经设计好的参数往后数，而不是实际的参数位置。   
### 引用的使用
```c
void fun(int& a, int& b)
{
	a++;
	b++;
	cout << a << ", " << b << endl;
}

int main()
{
	int a = 1;
	int b = 1;

	auto f1 = bind(fun, a, b);	//支持提前将参数与函数绑定起来，并返回function类型的对象
	f1();	//2, 2
	cout << a << ", " << b << endl;	//1, 1

	auto f2 = bind(fun, a, placeholders::_1);	//可以看到，只有实时传入的b作为引用自增了，a还是原来的样子
	f2(b);	//2,2
	cout << a << ", " << b << endl;	//1, 2

	getchar();
	return 0;
}
```
可以看到，当我们进行**提前绑定**的时候，即使函数本身的参数设定为引用传入，但是实际上仍然遵循的是值传入，a和b本身是没有变化的。   
而在f2中，提前传入的a仍然是值传入，而实时传入的b则实现了自增。   
显而易见，实时传入的值，是遵循函数的引用传入的。   
> 提前绑定的参数，是不支持引用传入的，始终是值传入。   
   
那么当我们使用实时传入参数的时候，怎么才能实现引用传入呢？   
### ref()  
使用std::ref可以在模板传参的时候传入引用，以替代值传递。   
std::ref只是尝试模拟引用传递，并不能真正变成引用。   
在非模板情况下，std::ref根本没法实现引用传递，只有模板自动推导类型时，ref能用包装类型reference_wrapper来代替原本会被识别的值类型，而reference_wrapper能隐式转换为被引用的值的引用类型。   
所以我们用ref，可以在bind函数中实现引用传递。   
```c
void fun(int& a, int& b)
{
	a++;
	b++;
	cout << a << ", " << b << endl;
}

int main()
{
	int a = 1;
	int b = 1;

	auto f1 = bind(fun, ref(a), ref(b));
	f1();	//2, 2
	cout << a << ", " << b << endl;	//2, 2

	getchar();
	return 0;
}
```  
可以看到，在ref的帮助下，a和b成功自增了。   