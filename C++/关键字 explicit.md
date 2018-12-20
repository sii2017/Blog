## explicit关键字
C++中的explicit关键字只能用于修饰**只有一个参数的类构造函数**，它的作用是表明该构造函数是显式的，而非隐式的。   
跟它相对应的另一个关键字是implicit，意思是隐式的。类构造函数默认情况下即声明为implicit(隐式)。      
当我们使用explicit关键字的时候就意味着，该构造函数不能引发c++编译器的**隐式类型转换**功能。   
### 隐式类型转换是什么
```c
class CxString  // 没有使用explicit关键字的类声明, 即默认为隐式声明    
{    
public:     
    char *_pstr;    
    int _size;   
    CxString(int size)  
    {  
        _size = size;                // string的预设大小  
        _pstr = malloc(size + 1);    // 分配string的内存  
        memset(_pstr, 0, size + 1);  
    }  
    CxString(const char *p)  
    {  
        int size = strlen(p);  
        _pstr = malloc(size + 1);    // 分配string的内存  
        strcpy(_pstr, p);            // 复制字符串  
        _size = strlen(_pstr);  
    }  
    // 析构函数这里不讨论, 省略...  
};  
  
int main()   
{   
    CxString string1(24);     // 正常调用构造函数, 为CxString预分配24字节的大小的内存  
    CxString string2 = 10;    // 隐式类型转换调用构造函数, 为CxString预分配10字节的大小的内存  
    CxString string3;         // 这样是不行的, 因为没有合适的默认构造函数   
    CxString string4("aaaa"); // 正常调用构造函数  
    CxString string5 = "bbb"; // 隐式类型转换调用构造函数, 调用的是CxString(const char *p)  
    CxString string6 = 'c';   // 隐式类型转换调用构造函数, 其实调用的是CxString(int size), 且size等于'c'的ascii码    
    string1 = 2;              // 隐式类型转换调用构造函数, 为CxString预分配2字节的大小的内存  
    string2 = 3;              // 隐式类型转换调用构造函数, 为CxString预分配3字节的大小的内存  
}   
```  
上面的代码中：  
```c
CxString string2 = 10;   
```  
如果构造参数只有一个参数（或有多个参数，但是其它参数都有缺省数值，只有一个参数没有），那么在编译的时候，编译器会自动做隐式类型转换。实际上等同于：  
```c
CxString string2(10);   
```   
> 注意，并不会用到默认的赋值运算符函数。我曾经以为是先构造一个默认实例，然后再进行赋值，但是实际上并不是如此。是直接并仅仅调用了构造函数。   

但是, 上面的代码中的_size代表的是字符串内存分配的大小，那么调用的第二句    
```c
CxString string2 = 10;     
```   
和第六句    
```c
CxString string6 = 'c';    
```   
就显得不伦不类，而且容易让人疑惑，亦或产生逻辑上的问题。有什么办法阻止这种用法呢？答案就是使用explicit关键字。 我们把上面的代码修改一下，如下：   
```c
class CxString  // 使用关键字explicit的类声明，显示转换  
{  
public:  
    char *_pstr;  
    int _size;  
    explicit CxString(int size)  
    {  
        _size = size;  
        // 代码同上, 省略...  
    }  
    CxString(const char *p)  
    {  
        // 代码同上, 省略...  
    }  
};  
  
    // 下面是调用:  
  
    CxString string1(24);     // 正常调用构造函数  
    CxString string2 = 10;    // 错误，因为explicit关键字拒绝了隐式转换  
    CxString string3;         // 错误，因为没有默认构造函数  
    CxString string4("aaaa"); // 正常调用构造函数  
    CxString string5 = "bbb"; // 因为没有加explicit关键字，因此调用的是CxString(const char *p)  
    CxString string6 = 'c';   // 错误，其实调用的是CxString(int size), 且size等于'c'的ascii码, 但explicit关键字取消了隐式转换  
    string1 = 2;              // 错误，因为取消了隐式转换  
    string2 = 3;              // 错误，因为取消了隐式转换  
```  
explicit关键字的作用就是防止类的构造函数发生隐式自动转换。   
explicit关键字只对有一个参数的类构造函数有效, 如果类构造函数参数大于或等于两个时, 是不会产生隐式转换的, 所以explicit关键字也就无效了，同时也是没有意义的。  
但是，如果构造函数有多个参数，除了第一个外，其它参数都有缺省值，这种情况下，它也具有隐式转换的功能，同时也能被explicit关键字针对。      
因此实际上我认为，explicit关键字针对的是构造函数的隐式类型转换的功能，而非构造函数的参数数量。   