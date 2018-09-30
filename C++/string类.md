## std::string类
string是c++用来处理字符串的一个类别。   
### 头文件支持
```c  
#include <string>   
```   
### 初始化
string可以用相当多的形式进行初始化。   
```c
string str1 = "str1";	//直接赋值初始化   
string str2(str1);	//使用str1进行初始化  
string str3(str2, 2);	//使用str2第二个位置开始的字符串初始化 r1   
string str4(str2, 2, 1);	//使用str2第二个位置开始开始的1个字符进行初始化 r   
char a[] = "string";   
string str5(a);	//使用字符数组进行初始化   
string str6(a, 3);	//使用a的前3个字符进行初始化   
const char* b = "string";   
string str7(b);	//使用char指针进行初始化   
string str8(b, 3);	//使用b的前三个字符进行初始化   
string str9(10, 'u');	//用10个u进行初始化   
string str10(str7.begin() + 1, str7.begin() + 3);	//使用str7的第二个字符串到第4个字符串进行初始化 [) tr   
``` 
### 添加删除元素 
**添加元素**   
```c
/* push_back 从最后插入单个字符*/   
string str1 = "understand the string class";   
str1.push_back('S');	//通过push_back把字符放到最后     

/* insert 从指定位置插入字符串或字符*/   
string str2;    
str2.insert(0, str1);	//从str2第0个位置开始把str1拷贝进去 understand the string class   
string str3;    
str3.insert(0, str1, 2, 2);	//从str3的第0个位置开始拷贝str1字符串的从第2个位置开始的2个字符  de    
string str4;    
str4.insert(0, str1, 2);	//第三个参数不写的话，默认从第二个位置开始后面的所有字符。 derstand the string class    
string str5;   
const char* temp = "Gucc";   
str5.insert(0, temp, 3);	//将字符串指针的前三个字符赋值进去    
str5.insert(0, temp);	//将字符串指针的所有字符赋值进去 GucGucc   
string str6;    
str6.insert(0, 6, 'c');	//从位置0开始插入6个c cccccc   
str6.insert(str6.begin(), 3, 's');	//也可以用迭代器作为位置，从开始插入3个s ssscccccc    
str6.insert(str6.end(), 'S');	//当中不写数字就意味着只插入一个 sssccccccS   
string str7;    
str7.insert(str7.begin(), str6.begin(), str6.end());	//通过迭代器插入段    
str7.insert(str7.begin(), 'c');	//插入单个字符   

/* assign 消除原有的字符，重新插入新的字符*/   
string str8;  
str8.assign(str7);	//将str7赋值进去   
str8.assign(str7, 3, 5);	//将str7的第三个位置开始的5个字符放进去 scccc   
str8.assign(str7, 1);	//将str9第一个位置开始的全部字符放进去
char buff[] = "fate grand order";   
str8.assign(buff);	//将buff全部放进去    
str8.assign(buff, 4);	//将buff的前四个字符放进去   
str8.assign(4, 'c');	//放入4个c    
str8.assign(str7.begin(), str7.end());	//通过迭代器插入段    

/* append 从尾部追加字符串*/   
string str9 = "begin ";   
str9.append(str8);	//从尾部加入str8   
str9.append(str8, 1, 3);	//从尾部加入str8第一个位置开始的3个字符   
str9.append(str8, 3);	//从尾部加入str8第三个位置开始的所有字符     
char buff1[] = "xiao mi";    
str9.append(buff1);	//尾部加入字符指针    
str9.append(buff1, 3);	//尾部加入字符指针的前三个字符      
str9.append(5, 'p');	//尾部加入5个字符p    
str9.append(str8.begin(), str8.end());	//尾部通过迭代器追加      
```   
**删除元素**   
```c
/* erase 通过位置或迭代器删除字符或字符串 */   
string str = "fate grand order";  
str.erase(5, 6);	//从第5个位置删掉6个字符 fate order   
str.erase(str.begin(), str.begin() + 5);	//删掉迭代器内的段 order    
str.erase(str.end() - 1);	//删掉迭代器位置的字符 orde   

/* pop_back 删除末尾的字符 */   
string str1 = "abc";   
str1.pop_back();  

/* clear 删除所有的字符 */   
str.clear();	//删除所有的字符   
```  
**定点替换字符串**  
```c
/* replace 定点替换字符串 */   
string str = "replace";   
string str_re = "ne";   
str.replace(2, 3, str_re);	//将str从第二个位置开始的3个字符替换成str_re的字符串   renece   
str.replace(str.begin(), str.end(), str_re);	//通过迭代器来替换 ne   
str_re = "abcdefghijk";   
str.replace(1, 5, str_re, 2, 3);	//将str从第一个位置开始的5个字符替换成str_re从第二个位置开始的3个字符 ncde   
str.replace(1, 1, str_re, 0);	//将str从第一个位置开始的5个字符替换成str_re从第0个位置开始的全部字符  nabcdefghijk     

const char* temp = "continue to replace";   
str.replace(0, 100, temp);	//从第0个位置后开始将后面100个字符全部替换为temp   
str.replace(str.begin(), str.end(), temp);	//通过迭代器将全部替换成temp      
str.replace(0, 100, temp, 8);	//从第0个位置开始将后面100个字符替换成temp的前8个字符 continue    
str.replace(str.begin(), str.end(), temp, 8);	//同上，使用迭代器来指定范围  continue    

str.replace(0, 99, 3, 'l');	//将str从第零个位置开始的后面99个字符替换成3个l  lll    
str.replace(str.begin(), str.end(), 5, 'c');	//同上，使用迭代器来指定范围     

str.replace(str.begin(), str.end(), str_re.begin(), str_re.end());	//通过迭代器来将str_re的指定范围替换到str的指定范围里   
```
### 赋值操作 
可以通过下标进行单个字符的赋值。   
也可以使用string对象，或者char指针以及数组进行赋值，这方面已经优化的很方便了。   
```c
string str;   
str = "abc";	//直接通过字面值常量进行赋值 abc   
str[0] = 'g';	//通过下标来赋值  gbc   
str.at(2) = 'q';	//通过at来进行赋值 gbq   

string str1;   
str1 = str;	//通过其他string来进行赋值   
  
const char* buff1 = "nilu saigao";   
str1 = buff1;	//通过字符串指针进行赋值  
char buff2[] = "saber the best";  
str1 = buff2;	//通过字符数组赋值    
```
### 空间调整

### 功能函数
### 总结