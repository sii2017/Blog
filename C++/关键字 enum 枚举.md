## 枚举
### 枚举的声明和定义
枚举的声明和定义形式如下：   
```c
enum enumType{a,b,c,d,e};		
```   
enum是枚举关键字；   
后面的enumType是枚举的类型，可以根据实际情况换成其他类型名；   
大括号内的内容是枚举的符号常量，通常称之为枚举量，其值默认从0开始，逐个加1，当然也可以自定义。    
以上的形式比较难懂，下面给出几个实例：   
```c
enum Weekday { Monday, Tuesday, Wednsday, Thursday, Friday, Saturday, Sunday};   
enum Direction { up, down, right, left};   
enum Class{ one, two, three, four, five, six};   
```   
通过上面的形式我们可以看出来，枚举通常来表达某种状态，比如：  
```c
Weekday weekday= Monday;	//状态为周一   
weekday= Tureday;	//状态为周二   
……    
Direction direction= up;	//状态为往上   
direction= down;	//状态为往下  
Class class= one;	//状态为1班   
class= size;	//状态为6班    
```   
当我们使用枚举类型时，跟其他类型相似。需要先声明，然后赋值。   
我们也可以在声明枚举类的时候就给出枚举变量，如下：   
```c
enum Direction {up, down, right, left} direction;   
```   
这里我们直接获得了direction这个枚举变量，可以直接使用它。   
### 枚举量的值   
枚举量的值默认情况下，为从0开始，依次加一。比如Direction中，up为0，down为1，right为2，left为3。   
枚举量也可以自定义值，比如：   
```c
enum Class{ one=1, two, three=1, four, five, six};   
```   
当我们只定义部分的枚举量时，未被自定义的枚举量的值默认比前面的枚举量的值大1，即one为1，two没有被定义因此比one大1为2，three为1，four为2，five为3，six为4。    
给枚举量指定的值必须时整数。    
我们不能把非枚举量（即整数或者其他类型）赋值给枚举变量。枚举变量只能被赋予枚举量或者其他同枚举类型的枚举变量。    
不同枚举类型的枚举变量不能互相赋值。    
枚举变量可以赋值给非枚举变量，比如：   
```c
int a= Monday;   //a为0   
```   
尽管枚举变量可以互相赋值，但是它不能进行运算，不能用++或--，或其他任何算术运算。枚举，只定义了赋值运算符，没有定义算术运算符。    
我们可以通过强制类型转换给枚举变量赋值，比如：   
```c
direction= Direction(2);   //direction为right   
direction= Direction(100);	//超出原有范围的话，direction的值时不确定的，是危险的值。   
```      
### 枚举的取值范围  
在给枚举变量进行强制转换赋值的时候，会有一个枚举的取值范围。   
枚举的上限是大于最大枚举量的值的最小的2的幂减1。   
枚举的下限有两种情况：   
1 枚举量的最小值不小于0，则枚举下限取0。   
2 枚举量的最小值小于0，则枚举下限是小于最小枚举量的最大的2的幂加1。   
举例来说：   
```c
enum enumType{ first=-5, second=14, third=10}   
```   
枚举的上限时16-5=15。16是大于最大枚举量的值14的2的最小幂。   
枚举的下限是-8+1=-7。-8是小于最小枚举量的值-5的2的最大幂。   
### 枚举的应用   
枚举的应用，一种是作为状态。如上面的例子一样，枚举变量可以作为当前的颜色，当前的班级，当前的方向等等。   
另外一追踪可以与switch进行搭档。   
```c
enum enumType{step1, step2, step3};    
enumType step;    
switch(step)   
{   
case step1:      
case step2:     
case step3:  
}  
```    
另外枚举还有一种少见的的用法。   
```c
enum{one, two, three};   
```  
不指定一个名字，这样我们也没法通过枚举类型去定义枚举变量了。此时相当于：  
```c
static const int one=0;   
static const int two=1;  
static const int three=2;   
```  
使用的话可以把他们赋值给int类型。   
### 强类型枚举   
强类型枚举（Stringly-typed enums），也称为枚举类型，是c++11推出的新语法。   
传统c++中枚举有一个缺陷是，枚举量暴露在外层作用域中，如果同一作用域里，两个不同的枚举类型有着相同的枚举常量，那他们是不能使用的。   
```c
enum side{right, left};   
enum thing{wrong, right};   
```   
这里，由于他们都有right这个枚举常量会导致命名冲突，编译阶段会报错。   
另一个缺陷是，旧枚举的枚举量默认为整型，无法自定义枚举的底层数据类型。   
强类型枚举解决了这2个问题。   
我们只需要给普通枚举加上class或者struct就可以将其变成强类型枚举。   
```c
enum class type1{one, two, three};   
enum struct type2{one, two, three};   
```  
如此声明，也不会有问题，因为他们是强类型枚举。   
```c
type1 t1= one;	//error   
type1 t1= type1::one;	//赋值要带上作用域。  
```   
此外我们还可以指定枚举常量的底层数据类型。   
```c
enum class A: char{ one='a', two='b', three};   
A a= A::one;   
cout << sizeof(a) << endl;	//大小为1   
char b= a; 	//error，尽管底层数据为char，但是无法被用于赋值   
```   
可以看到尽管可以指定底层数据类型，但是无法被用于赋值。   