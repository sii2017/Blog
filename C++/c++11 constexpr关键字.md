## constexpr关键字
constexpr关键字与const相似但是不相同。   
### 常量表达式
先了解常量表达式的概念。   
常量表达式是指：数值不会改变并且在编译过程中就能得到计算结果的表达式。      
比如字面值属于常量表达式，因此用常量表达式初始化的const对象也是常量表达式。   
> const变量并不一定是常量表达式，const只是告诉编译器和编程者，这个const变量不会被改变，也不能被改变。   

一个对象是不是常量表达式由它的**数据类型和初始值共同决定**。   
```c
const int maxsize= 10;	//maxsize是常量表达式   
const int limit= maxsize+1;	//limit也是常量表达式  
int staff_size= 20;	//staff_size不是常量表达式   
const int c_size= get_size();	//c_size也不是常量表达式，无法在编译时就获取   
```   
### constexpr
c++11新标准规定，允许将变量声明为constexpr类型以便由编译器来验证变量的值是否时一个常量表达式。   
```c
constexpr int mf= 20;	//是常量表达式正常通过编译   
constexpr int limit= mf+1;	//是常量表达式正常通过编译   
constexpr int sz= size();	//只有当size是一个constexpr函数时才能正常通过编译。   
```  
普通函数不能成为constexpr变量的初始值，不过可以定义一种特殊的constexpr函数，这种函数应该足够简单到编译的时候就可以计算结果，这样就能用constexpr函数去初始化constexpr变量了。   
### constexpr函数  
之前说到constexpr函数必须足够简单，以下：  
```c
constexpr int fun(){return 42;}	//这就是有一个足够简单的contexpr函数  
constexpr int fun1(int param){return fun()*param;}	//这是一个接收参数的constexpr函数。   
```  
需要注意的是，接收参数的constexpr函数的参数，也必须要常量表达式。这样才能在编译期间计算出结果。   
> 注意：constexpr函数不一定返回常量表达式。   
```c
int noconst= 10;
int ret= fun1(noconst);	//可以返回非常量表达式。   
constexpr int ret= fun1(noconst);	//错误，因为参数为非常量表达式，所以返回的也是非常量表达式，所以不能赋值给constexpr的ret。   
```   
### constexpr和指针
如果使用constexpr定义了一个指针，那么constexpr仅对指针有效，与指向的对象无关。  
```c
const int* p= nullptr;	//p是一个指向整型常量的指针  
constexpr int* q= nullptr;	//q是一个指向整数的常量指针  
```