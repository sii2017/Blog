## c++11 Lambda表达式
c++11引入了Lambda表达式，该表达式比较早就在其它语言中进行使用了。   
### 语法
```c
[capture list] (params list) mutable exception-> return type { function body }   
```   
**1 [capture list]：捕捉列表。**   
捕捉列表总是出现在Lambda函数的开始处。实际上，[]是Lambda引出符。编译器根据该引出符判断接下来的代码是否是Lambda函数。捕捉列表能够捕捉上下文中的变量以供Lambda函数使用。   
1.1 [var]表示值传递方式捕捉变量var；  
1.2 [=]表示值传递方式捕捉所有父作用域①的变量（包括this）；  
1.3 [&var]表示引用传递捕捉变量var；  
1.4 [&]表示引用传递方式捕捉所有父作用域的变量（包括this）；   
1.5 [this]表示值传递方式捕捉当前的this指针。   
> ①父作用域即包含Lambda函数的语句块“{}”。   
  
例如：  
[=,&a,&b]表示a和b变量用引用的方式捕捉，除他们之外的变量由值传递的方式来捕捉。   
[&,a,this]表示a和this由值传递的方式捕捉，除他们之外的变量全部由引用的方式捕捉。   
需要注意的是，捕捉列表不允许变量重复的传递。   
[=,a]这里的=已经表示所有值以值传递的方式捕捉，那么后面再重申一次a以值传递的方式捕捉则会报错。   
[&,&this]已经表示全部以引用的方式进行捕捉，那么再写一次this以引用捕捉则重复了，会报错。   
如果捕捉列表[]为空，则表示任何变量都不会传递给这个Lambda表达式。   
**2.(parameters)：参数列表。**     
与普通函数的参数列表一致。如果不需要参数传递，则可以连同括号“()”一起省略。   
**3.mutable：mutable修饰符。**    
默认情况下，Lambda函数总是一个const函数，也就是说在值传递捕获的情况下，Lambda函数体内无法改变捕获的参数的值（引用传递不受此限制）。mutable关键字可以取消其常量性。在使用该修饰符时，参数列表不可省略（即使参数为空）。    
**4.->return-type：返回类型。**    
用追踪返回类型形式声明函数的返回类型。我们可以在不需要返回值的时候也可以连同符号”->”一起省略。此外，在返回类型明确的情况下，也可以省略该部分，让编译器对返回类型进行推导。  
**5.{statement}：函数体。**    
内容与普通函数一样，不过除了可以使用参数之外，还可以使用所有捕获的变量。   
### 例子
```c
#include <iostream>  
#include <string>  
using namespace std;  

int main(int argc, char** argv)  
{  
	//最短的调用   
	auto fun1 = [] {cout << "call Lambda" << endl; };  
	fun1();   

	//简单的调用   
	string str = "call Lambda";  
	auto fun2 = [=] {cout << str << endl; };	//值传递   
	fun2();   
	auto fun3 = [&] {cout << str << endl; };	//引用传递   
	fun3();  
	getchar();  
	return 0;  
}  
```   
### 实用的例子
Lambda目前在我了解的情况中，运用比较好的地方在STL的函数中。   
比如count_if函数，曾经我们需要为其第三个参数来写一个函数，但是有Lambda函数后，仅仅一行代码即可。   
```c
#include <iostream>  
#include <string>  
#include <algorithm>  
using namespace std;  

int main(int argc, char** argv)  
{  
	string str = "fate/extra";    
	int num= count_if(str.begin(), str.end(), [](char s) {return s == 'a'; });	//统计字符串中a的数量   
	cout << "在str中a的数量为：" << num << endl;   
	getchar(); 
	return 0;   
}  
```   
### 总结
Lambda的体量较小，可以用在一些功能代码不需要复用的地方。  
Lambda表达式可以作为回调来使用。  