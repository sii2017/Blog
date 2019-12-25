## char二级指针的声明和使用  
在和友商联调接口的时候，他们有个接口函数需要用到char**传值。  
个人觉得char**还挺恶心的，平时不怎么用，且比较容易弄错或者内存越界，并且即使弄懂了，我仍然觉得挺恶心的。   
记录一下，免得下次又被恶心到……   
另外吐槽一下，在百度上搜了不少关于这个问题的内容，有不少是错的，让我走了不少弯路……   
### 声明和定义  
思路是这样的，先为二级指针声明空间，空间大小为N个char*即一个字符指针占用的大小，在64位下这个大小为8个字节。   
随后，分别为每个一级指针，申请内存空间，并且赋值。  
以下例子，是声明并定义一个，包含3个一级字符指针的二级指针。   
```c
char** arrSecurity = new char*[3];   

arrSecurity[0] = new char[9];  
strcpy(arrSecurity[0], "10001827");   
arrSecurity[1] = new char[9];   
strcpy(arrSecurity[1], "10001828");  
arrSecurity[2] = new char[9];   
strcpy(arrSecurity[2], "10001829");  

cout << arrSecurity[0] << arrSecurity[1] << arrSecurity[2] << endl;   
```  
步骤一中，为arrSecurity申请内存的时候，实际上即使申请1个char*的指针的大小也是可以的。   
因为当内存连续的情况下，我们访问arrSecurity[1]和arrSecurity[2]的时候，编译器会找到后面连续的位置在1和2的字符串。   
但是如果说，超出位置0的部分，被占用、被覆写了，那么便会产生难以排查的错误。所以保险起见申请3个是没错的。    
### 释放内存
结束的时候，释放内存的顺序，先释放一级指针，再释放二级指针。   
```c
for (int i = 0; i < 3; i++)   
	delete arrSecurity[i];   
delete arrSecurity;  
```   
### 最后的吐槽
我觉得传二级指针，不如传逗号隔开的字符串了。  