## sizeof运算符
sizeof 运算符的结果为size_t类型，它是包含文件STDDEF.H中定义的整数类型。   
利用此运算符，可以避免在程序中指定依赖于计算机的数据大小。   
sizeof 的操作数可以是下列项之一：    
1 类型名称。 若要将 sizeof 用于类型名称，则该名称必须用括号括起。    
2 一个表达式。 当用于表达式时，无论是否使用括号都可指定 sizeof。 不计算表达式。   
### 例子
```c
#include <iostream>
using namespace std;

int main(int argc, char** argv) {
	char temp[256]= "hello world!";
	char temp1[]= "hello world!";
	char* temp2= "hello world!";
	cout << sizeof(char) << endl;	//1
	cout << sizeof temp << endl;	//256
	cout << sizeof temp1 << endl;	//13
	cout << sizeof temp2 << endl;	//8
	getchar();
	return 0;
}
```
第一种情况使用了类型名称char，因此得出char占用1个字节。  
第二第三种情况使用了两种不同的数组，因此得出了不同的大小。尽管内容相同，但是因为其实际占用的内存是不同的。   
第三种情况获得了指针的大小。   
### 总结
当sizeof运算符应用到class、struct或union类型时，结果为该类型的对象中的字节数，以及添加的用于在字边界上对齐成员数据的任何填充。结果不一定对应于通过将各个成员的存储需求相加计算出的大小。   
sizeof 运算符永远不会产生 0，即使对于空类也是如此。    
当 sizeof 运算符应用于引用时，结果与 sizeof 应用到对象本身时的结果相同。   
如果某个未确定大小的数组是结构的最后一个元素，则 sizeof 运算符将返回没有该数组的结构的大小。   
sizeof 运算符通常用于通过使用以下形式的表达式计算数组中的元素数量：   
```c
sizeof array / sizeof array[0]    
```
