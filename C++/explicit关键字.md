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