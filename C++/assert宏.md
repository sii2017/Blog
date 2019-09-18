## assert宏
在一些代码里经常看到ASSERT，一开始还以为是函数，经查询发现是宏。  
其中文名为“断言”。   
### 作用
assert作用并不是报错，也不能仅仅当作if来用。  
assert的用法像是一种契约式编程，个人认为应该用在只会发生严重错误的地方。   
**assert一旦触发，则会调用abort来中止程序运行**。  
### 用法
assert的作用是计算表达式expression。   
```c
#include <assert.h>   
void assert(int expression);   
```   
如果expression为假，则向 stderr 打印一条出错信息,然后通过调用 abort 来终止程序运行。  
使用 assert 的缺点是，频繁的调用会极大的影响程序的性能，增加额外的开销。   
### 注意事项
1 建议assert每次只检查一个条件，因为同时检查多个条件的话，当触发assert，我们并不知道是哪个条件引起的。   
2 不要在assert内使用会改变环境的语句比如++和--，因为assert只在dubug中有效，如果在release中则不会调用，会影响正常代码的执行。   