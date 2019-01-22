## 关键字 sizeof
sizeof关键字返回的结果为size_t类型，它是包含文件STDDEF.H中定义的整数类型。   
利用此关键字，可以避免在程序中指定依赖于计算机的数据大小。   
sizeof的操作数可以是下列项之一：    
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
1 计算类的大小的时候，sizeof不计算类内static成员变量的内存，static成员变量，是所有对象共享的，所以不属于某个对象，也就是说不属于类，在静态区。      
2 32位系统的指针的大小是4个字节，64位系统的指针是8字节，而不用管指针类型。   
3 sizeof关键字永远不会产生0，即使对于空类也是如此。    
4 一个空类占1个字节，单一继承的空类占1个字节，虚继承涉及到虚指针所以占4个字节（并且由于里面有虚指针，就不分配1个字节来占位了）。   
5 数组的长度：  
若指定了数组长度，则不看元素个数，总字节数=数组长度*sizeof（元素类型）；   
若没有指定长度，则按实际元素个数类确定；   
Ps：若是字符数组，则应考虑末尾的空字符。   
6 当sizeof关键字应用到class、struct或union类型时，结果为该类型的对象中的字节数，以及添加的用于在字边界上对齐成员数据的任何填充。结果不一定对应于通过将各个成员的存储需求相加计算出的大小。  
7 unsigned影响的只是最高位的意义，数据长度不会改变，所以sizeof（unsigned int）=4。   
8 对函数使用sizeof，在编译阶段会被函数的返回值的类型代替。   
9 sizeof后如果是类型名则必须加括号，如果是变量名可以不加括号，这是因为sizeof是运算符。   
10 当使用结构类型或者变量时，sizeof返回实际的大小。当使用静态数组时返回数组的全部大小，sizeof不能返回动态数组或者外部数组的尺寸。   
11 当 sizeof关键字应用于引用时，结果与sizeof应用到对象本身时的结果相同。   
12 sizeof关键字通常用于通过使用以下形式的表达式计算数组中的元素数量：   
```c
sizeof array / sizeof array[0]    
```
