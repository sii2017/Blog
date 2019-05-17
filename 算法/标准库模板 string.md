## 标准库类型 string
string也是标准库的一员，但是与vector等相比，它并不是一个模板类。   
string用来处理各种字符串，比起普通的字符置真，string用起来更加便捷。   
### 头文件支持
```c
#include <string>   
```    
### 初始化
支持()及{}的初始化。   
```c
string str1; 	//默认初始化为空  
string str2("abc");	//调用char*为参数的构造函数   
string str3{"abc"};	//初始化列表初始化   
string str4{'a','b','c'};	//使用初始化列表初始化   
string str5(str2);	//使用其它string进行初始化   
string str6(str2.begin(), str2.begin()+1);	//使用范围初始化   
```   
### 添加元素
与vector类似，支持pushback和insert。   
```c
string str;   
str.push_back('a');		//在末尾的位置添加字符    
str.push_back('b');   
str.insert(str.begin(), str.begin(), str.end());	//在begin的位置添加一个范围的元素
```  
支持assign函数，assign会删除缘有的内容进行覆盖。   
```c
str.assign("abc");   //参数char*   
str.assign(str.begin(), str.begin() + 1);	//参数为一个范围   
```
更是支持其它标准库模板几乎不支持的符号+    
```c
string str1= "abc";   
string str2= "efg";   
str1= str1+str2;	//abcefg    
```
### 删除元素
删除末尾单个字符，pup_back   
```c
string str= "abc";   
str.pop_back();	//ab    
```    
erase函数   
```c   
string str = "abcdefg";    
str.erase(str.begin());	//删除某个迭代器指向的字符  bcdefg     
str.erase(1, 2);	//删除从某个位置pos开始的n个字符  befg     
str.erase(str.begin(), str.begin() + 1);	//删除一个范围内的字符 efg    
```  
完全清空字符内容   
```c
str.clear();   
```   
### 预分配空间
通过预分配空间来（微弱的）提高效率   
```c
string str="abc";   
str.reserve(100);	//将str能容纳的空间提升为100，当然其内容实际上没有改变    
str.resize(1);	//将str实际的字符数量调整到1，容纳空间没有改变仍然是100，内容则变为a   
str.resize(3, '+');	//将字符数量调整到3，如有不足则以+代替。a++    
str.shrink_to_fit();	//将空间缩小到实际需要的大小，因为a++，所以为3   
```    
### 功能函数  
string str= "abc";  
str.size();	//返回大小   
str.length();	//返回长度，实际与上面一样   
str.max_size();	//返回当前环境下能达到的最大大小   
str.capacity();	//返回实际在内存中占用的大小   
str.empty();	//返回是否为空   
str.front();	//返回第一个字符串   
str.back();	//返回最后一个字符串   
str1.replace(str2);	//交换两个string  
str.c_str();	//返回一个c字符串   
str.data();	//返回一个不带结尾符的数组   

char buff[20];   
str.copy(buff, 