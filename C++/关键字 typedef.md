## typedef关键字
typedef：为现有类型创建别名。    
使用方法如下：  
```c
typedef existing_type new_type_name;   
```   
### typedef的简单使用
```c
typedef int size;   //用size给int当别名   
typedef unsigned int WORD;	//用WORD当unsigned int的别名   

size i;	//=int i;   
WORD J;	//=unsigned int J;   
```    
typedef 并不创建新的类型。它仅仅为现有类型添加一个同义字。  
### typedef和数组、指针  
```c
char line[100];   
char text[100];  
```   
像上面的char数组，我们也可以通过typedef来进行定义。   
```c
typedef char Line[81];		 
Line a;		//=char a[81];   
Line second;	//= char second[81];   
```  
可以看出来，typedef并不是像define进行简单的替换的，它是有一定的自己的逻辑在里面的。    
```c
typedef char* pchar;   //将pchar作为char*的别名  
pchar cc;	//= char* cc   
```   
通常也可以用来隐藏指针。    
### typedef和函数指针  
我们还可以用typedef来给函数指针取别名。   
```c
void function(int a);  	//比如有这么一个函数   
void (*fun)(int);	//我们如此定义一个函数指针，返回值是void，参数是int，函数指针变量名是fun       
fun= &function;	//我们将函数指针指向function函数   

void (*fun1)(int);	//我们定义第二个相同的函数指针，但是每次定义很麻烦，我们就可以使用typedef   
typedef void (*pfun)(int);    //我们将pfun作为该函数指针类型的别名   
pfun p1;   //等价于 void (*p1)(int)    
p1= &function;    
(*p1)(100);	//调用   
pfun p2;	//。。。。就可以比较方便的定义很多这个类型的指针了  
```   
如上所述，typedef可以帮我们“创建”一个函数指针的类型的别名，然后很方便的去声明同样的函数指针。    
> 这里的创建是引号，因为实际上typedef并不会创建任何东西，它永远只是给出一个别名。   
    
函数指针之所以让初学者畏惧，最主要的原因是它的括号太多了；某些用途的函数指针，往往会让人陷在括号堆中出不来。typedef方法可以有效的减少括号的数量，以及理清层次，所以受到推荐。    
### typedef和struct
在以前的c的代码中，声明struct对象一定要带上struct，形式为：struct 结构名 对象名：   
```c
struct st   
{  
	int x;   
	double y;   
};     
struct st s;	//声明s既需要struct关键字又需要st结构名      
```  
> 当然在c++中已经不需要了，可以直接写：结构名 对象名。    
   
出于省略一个stuct关键字的想法，于是就使用typedef来进行声明：   
```c
typedef struct st  
{  
	int x;   
	double y;   
}ST;    
ST s;	//这样就不用加struct了    
```   
### 跨平台的使用   
用typedef来定义与平台无关的类型。    
比如定义一个叫 REAL的浮点类型，在目标平台一上，让它表示最高精度的类型为：   
```c
typedef long double REAL;     
```   
在不支持 long double 的平台二上，改为：   
```c
typedef double REAL;    
```   
在连 double 都不支持的平台三上，改为：   
```c   
typedef float REAL;    
```    
也就是说，当跨平台时，只要改下typedef本身就行，不用对其他源码做任何修改。    
标准库就广泛使用了这个技巧，比如size_t。   
另外，因为typedef是定义了一种类型的新别名，不是简单的字符串替换，所以它比宏来得稳健（虽然用宏有时也可以完成以上的用途）。   
### typedef是一个存储类的关键字    
typedef在语法上是一个存储类的关键字（如auto、extern、mutable、static、register等一样），虽然它并不真正影响对象的存储特性，如：    
```c
typedef static int INT2; //不可行   
```   
编译将失败，会提示“指定了一个以上的存储类”。    
### typedef和const  
标准函数 strcmp()有两个‘const char *’类型的参数。因此，它可能会误导人们象下面这样声明 mystrcmp()：   
```c
int mystrcmp(const pstr, const pstr);    
```  
**这是错误的，按照顺序，‘const pstr’被解释为‘char * const’（一个指向char的常量指针），而不是‘const char *’（指向常量 char 的指针）。**    
这个问题很这样解决：   
```c
typedef const char * cpstr; int mystrcmp(cpstr, cpstr); // 现在是正确的   
```   
注意：不管什么时候，只要为指针声明typedef，那么都要在最终的 typedef名称中加一个const，以使得该指针本身是常量，而不是对象。   
