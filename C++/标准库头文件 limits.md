## limits标准库头文件
在不同的系统中，由于架构的问题，有时候1个字节为8位，有时候1个字节为16位。因此存在这么一个头文件，里面包含了关于各种基本类型限制的信息。   
### 使用方式
```c   
#include <limits.h>	//c的格式   
#include <climits>  //c++的格式   
```   
### 包含内容
![](https://github.com/sii2017/image/blob/master/limits.jpg)   
### more
由于一个char总是一个字节，因此可以通过CHAR_BIT来获取这个系统一个字节占用几位。  