## decltype关键字
有时候会遇到这种情况：希望从表达式的类型推断出要定义的变量的类型，但是不想用该表达式的值初始化变量（反之则可以用auto关键字）。   
为了满足这一要求，c++11新标准引入了第二种类型说明符decltype，它的作用是选择并返回操作数的数据类型。在此过程中，编译器分析表达式并得到它的类型，却不实际计算表达式的值。   
### 使用方式
```c
decltype(f()) sum=x;	//sum的类型就是函数f的返回类型  
```  
编译器并不实际调用函数f，而是使用当调用发生时f的返回值类型作为sum的类型。   
### 处理顶层const的方式
decltype处理顶层const和引用的方式：如果decltype使用的表达式是一个变量，那么decltype返回该变量的类型（**包括顶层/底层const和引用在内**）：  
```c
const int ci= 0;   
const int& cj= ci;  
decltype(ci) x= 0;	//x是const int      
decltype(cj) y= x;	//y是const int&， y绑定到x     
decltype(cj) z;	//错误，由于是引用，必须初始化      
```    
### 处理表达式的方式
如果decltype使用的是表达式而不是一个变量，那么decltype返回表达式对应的类型。   
```c
int i=42;
int& r= i;
decltype(r+0) b;	//r+0这个表达式是int类型的，所以b为int   
```   
如果表达式的内容是解引用，那么decltype加那个得到引用类型。  
> 正如我们所指，解引用指针可以得到指针所指向的对象，还能赋值。因此，decltype(指针)的结果类型是引用。   
   
```c
int* p;   
decltype(*p) d;	//d为int&类型  
```   
如果decltype的表达式是变量名加上了一对括号，所得到的类型与不加括号时会有所不同。  
如果decltype使用的是一个不加括号的变量，所得到的结果就是该变量的类型。但是如果加了一层或多层括号，编译器会把它当成一个表达式。变量是一种可以作为赋值语句左值的特殊表达式，所以这样的decltype会得到引用类型。   
```c
int a= 5;    
decltype(a) b;	//int类型   
decltype((a)) c;	//int&类型，当然这里是错误的，引用必须初始化    
```   
> 切记：decltype((variable))的结果永远是引用，而decltype(variable)结果只有当variable本身是一个引用时才是引用。   
### decltype和auto的区别
auto和decltype都是类型推断的两种方式，但之间又有区别。主要体现在这几个方面：    
1 auto是通过编译器计算变量的初始值来推断类型的，decltype同样也是通过编译器来分析表达式进而得到它的类型，但是它不用将表达式的值计算出来。    
2 编译器推断出来的auto类型有可能和初始值类型不同，比如对于顶层const，auto会忽略顶层const性质，但是decltype是保留下来的。     
3 decltype的结果类型与表达式形式有密切关系。比如decltype（）内层没有括号，那么得到的类型就是变量的类型，如果有多层括号decltype（（））那么返回的就是引用。但是auto没有这个现象。        