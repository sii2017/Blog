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
str1.push\_back('S');	//通过push_back把字符放到最后     

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

/* pop\_back 删除末尾的字符 */   
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
str.replace(2, 3, str_re);	//将str从第二个位置开始的3个字符替换成st_re的字符串   renece   
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
string类空间的调整分为两种，一种与size相关，为字符串的字符占用的空间。另外一种与capacity有关，为该字符串对象占用的存储空间。后者总是大于或者等于前者的，因此存储空间有时候需要额外的空间来对字符串对象进行优化。   
先看一下size相关的内容。  
```c
string str = "fate grand order";   
cout << str.size() << endl;	//使用size来获取 16   
str.resize(str.size() + 2, '!');	//使用！来初始化增加的长度，当前长度为18 fate grand order!!    
str.resize(str.size() + 2);		//使用空白来初始化增加的长度，当前长度为20  fate grand order!!    
str.resize(16);	//减少长度  当前长度为16  fate grand order    
```   
以下是capacity的相关内容。   
```c
string str= "fate grand order";   
cout << str.capacity() << end;   //来获取存储空间为31，可以看到明显大于size的16。   
str.reserve(35);	//重新配置存储空间占用的空间。需要注意的是，如果比原有的小是无效的，并且它实际分配的存储空间总是大于或等于我们请求的数值。   
str.shrink_to_fit()；	//使存储空间缩减到适合的大小，即回到31   
```
### 功能函数
与stl标准库相似的一些功能函数。   
string str= "string";   
str.size();	//返回str的大小，由于每个字符占1个字节，因此与长度相等       
str.length();	//返回str的长度，由于每个字符占一个字节，因此与size相等   
str.max\_size();	//返回str可以占用的最大大小，与内存大小有关   
str.empty();	//返回字符串是否为空  
str.at(10);	//返回第十个位置上的字符  
str.front();	//返回第一个字符   
str.back();	//返回最后一个字符   
string substr= str.substr(2,4);	//将str从第二个字符开始的四个字符截断出来赋值给substr。   ring  
str1.swap(str2);	//交换两个字符串的内容  
#### 将string转化为c字符串  
以下为两种方式，一种转换为char指针，一种转化为char数组。   
```c
char* temp= str.c_str();	//返回c字符串，但是该指针不要长时间使用，因为如果str的地址发生改变，那么temp指向的内容就不对了   
str.data();	//返回的也是字符串，但是并不是c字符串，因为它不以\0结尾。    

char buff[20];    
std::size_t length= str.copy(buff, 6,5);   //函数返回的是字符串的长度   
buff[length]= '\0';	//将字符串中的第六个字符开始后的五个字符赋值到char数组当中，但是要注意，最后的\0要自己加。   
```
#### find相关函数  
**find函数**是比较常用的功能函数，可以使我们在string对象中寻找string对象、c字符串以及单个字符。   
```c
string str = "fate grand order";  
string str_tofind = "grand";   
int pos = 0;   
pos = str.find(str_tofind);		//搜索另外一个string对象的位置     
pos = str.find(str_tofind, 10);		//从指定的位置开始向后搜索，如果没有搜到到则返回-1，这里从10开始搜显然是搜不到的   
const char* c_tofind = "order";   
pos = str.find(c_tofind);	//搜索c字符串对象的位置   
pos = str.find(c_tofind, 10);	//由于order在第11个位置开始，因此从10开始搜索也能搜到     
pos = str.find(c_tofind, 10, 0);	//第三个参数为c_tofind匹配的前几个数字的数量。0为匹配零个字符（什么都不用匹配），输出为10。如果第三个参数为1，那么至少匹配一个o，输出为11。      
pos = str.find('a', 0);	//从0位置开始搜索字符a，第二个参数可以缺省，缺省默认为0。    
```   
同样还有一个反向搜索函数**rfind函数**：   
```c
string (1)	  
size_t rfind (const string& str, size_t pos = npos) const noexcept;  
c-string (2)	   
size_t rfind (const char* s, size_t pos = npos) const;   
buffer (3)	   
size_t rfind (const char* s, size_t pos, size_t n) const;  
character (4)	   
size_t rfind (char c, size_t pos = npos) const noexcept;  
```  
其使用方法与find完全一致，需要注意有两点：
> 1 rfind是反向搜索，从最后一个字符开始搜索。   
> 2 rdind的返回值所代表的位置pos，为正向所代表的位置。   
  
带条件的搜索函数：   
find_first_of   
find_last_of    
find_first_not_of    
find_last_not_of   
以上四个函数都与find的使用方式完全一致。   
### 总结