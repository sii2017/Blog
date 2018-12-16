# auto关键字
c++11新推出了auto关键字。   
## auto类型推断
auto可以在声明变量的时候根据变量初始值的类型自动为此变量选择匹配的类型（类似的关键字还有decltype）。    
举个例子：   
```c
int a=10;
auto b= a;	//根据a进行推断，得知a为int，则b也为int   
```   
auto的自动类型推断发生在编译期，所以使用auto并不会造成程序运行时效率的降低。   
auto更多的用于代替冗长复杂、变量使用范围专一的变量声明。   
比如：   
```c   
//未使用auto   
for(std::vector<std::string>::iterator i= vec.begin(); i!=vec.end(); i++)   
{   
	...  
}       

//使用了auto    
for(auto i= vec.begin(); i!=vec.end(); i++)    
{   
	...   
}  
```   
使用了auto可以简化代码。   
## auto作为占位符   
auto为函数提供了一种**后置返回类型**的选择。   
一般函数，我们都是将返回值写在最前面的，但是出于某些情况（后面会说到），我们希望返回值写在最后，这时候auto提供了这个功能。   
```c  
//原始版本的函数   
int add(const int& a, const int& b)  
{   
	return a+b;   
}   

//后置返回类型函数   
auto add(const int& a, const int& b)->int   
{   
	return a+b;   
}      
```   
这里，auto作为一个占位符，放在函数的最上面，在声明的最后以->类型的形式指明类型。   
那么问题来了，什么情况下我们需要后置返回类型呢？   
### 后置返回类型的应用场景  
参考同目录下《decltype关键字》，我们可以知道decltype与auto类似，也可以推断数据的类型。不同的是，decltype是对特定的表达式进行推断，而不是初始值。   
当我们使用函数模板，有时候会遇到一种情况：   
```c
template<typename T1, typename T2>   
?type? add(T1 a, T2 b)  
{   
	return a+b;   
}    
```   
比如以上函数，由于a和b未必是同一种类型，那么我们无法确定返回值。   
我们是否可以用  
```c 
decltype(a+b)   
```   
作为返回值呢？   
答案是不行，由于处在a和b声明之前，这时候还没有a和b。   
这时候，后置返回类型的应用场景就出现了，那么我们在a和b声明之后确定返回值就行了。   
```c
template<typename T1, typename T2>   
auto add(T1 a, T2 b)-> decltype(a+b)    
{   
	return a+b;   
}    
```   
以上就是后置返回类型的应用场景了。   
## decltype和auto的区别
auto和decltype都是类型推断的两种方式，但之间又有区别。主要体现在这几个方面：    
1 auto是通过编译器计算变量的初始值来推断类型的，decltype同样也是通过编译器来分析表达式进而得到它的类型，但是它不用将表达式的值计算出来。    
2 编译器推断出来的auto类型有可能和初始值类型不同，比如对于顶层const，auto会忽略顶层const性质，但是decltype是保留下来的。     
3 decltype的结果类型与表达式形式有密切关系。比如decltype（）内层没有括号，那么得到的类型就是变量的类型，如果有多层括号decltype（（））那么返回的就是引用。但是auto没有这个现象。        
