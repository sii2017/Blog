# cin cout流对象相关知识
内容来源于c++primer 第六版的笔记。  
## 设置不同的进制
hex、oct和dec与cin、cout对象一起使用，可以将整数输入解释为十六进制、八进制和十进制。   
```c
int a = 100;  
cout << a << endl;	//默认为十进制，100   
cout << hex;	//设置为16进制   
cout << a << endl;	//16进制为64   
cout << oct << a << endl;	//设置为8进制为144  
cout << dec << a << endl;	//设置回10进制为100   
```   
该设置具有持续性，持续到直至被重置为其他进制。   
## 对c字符串的优化
cin对象为c类型字符串进行了重载。   
如果是读取字符串存放到c类型字符串指针或者是字符数组里，会再最后加上一个空置字符，作为'\0'使用。   
## 返回值
cout和cin对象成功后的返回值为其自身的引用。   
对于cout对象来说，通常情况下   
```c 
cout << a << b;   
```  
实际上是前一个cout返回了一个cout对象的引用，再继续cout后面一个变量。   
对于cin对象来说，如果输入与预期不匹配将导致表达式cin>>input的结果为false。       
## 获取流状态
cin和cout对象包含一个描述流状态的数据成员（从ios_base类那里继承的）。   
流状态为iostate类型，是一种掩码类型，由3个ios_base元素组成：eofbit、badbit或failbit。每个元素占用1位，可以设置成1或0。   
当cin操作到达文件末尾，将设置eofbit；   
当cin操作未能读取到预期格式的字符，将会设置failbit。如果I/O失败（如试图读取不可访问的文件），也可能将failbit设置位；    
在一些无法诊断的失败破坏流时，badbit元素将被设置。   
当三个状态位都为0时，说明一切顺利。   
我们可以通过相关的函数来获取流状态。   
```c
cin.eof();		//如果eof则返回true   
cin.fail();	//如果failbit则返回true   
cin.bad();	//如果badbit则返回true   
```  
注意fail函数将在failbit或eofbit被设置时返回true，因此必须进行排除。  
```c
if(cin.fail() && !cin.eof())   
{}  
```  
fail返回true且eof返回false的时候则说明确实是fail。    
## 设置流状态
cin和cout有两个成员函数，分别为clear()和setstate()。   
在大多数情况下，clear函数很容易被以为清除对象的所有异状态，但是这种想法是错误的。   
clear成员函数用来设置流对象当前的流状态。  
通过默认参数空的重载函数，将所有的三个状态位（eofbit、badbit和failbit设置为0）。  
```c
clear();   
```    
同样，下面的调用状态将eofbit设置为1，其他两个状态为被清除：  
```c
clear(eofbit);   
```   
而setstate成员函数只影响其参数中已设置的位。因此下面的调用将设置eofbit而不会影响其他位：   
```c
setstate(eofbit);  
```   
## IO异常
假设某个输入函数设置了eofbit会不会导致异常被引发呢？不会的。  
但是我们可以使用exceptions成员函数来控制异常如何被处理。换言之，我们手动让eofbit产生的时候引发异常，同理对其他两个情况。   
```c
cin.exceptions(badbit);	//这么一设置，后面如果引发badbit状态了，则回引发异常可以用catch来获取   

try{   
	while(cin>> input)  
	sum++ input;  
}catch(ios_base::failure& bf)  
{  
	cout << bf.what() << endl;   
}    
```   
我们也可以同时设置多种状态：   
```c
cin.exceptions(badbit| eofbit);   
```   
不过是不是有必要去这么做，就看具体的实际情况了。   
## 字符串输入：getline() get() ignore()   
### getline()  
getline可以整行整行输入字符串。他的原型有两种：   
```c
istream& getline(char*, int, char);  
istream& getline(char*, int);   
```   
第一个参数用来保存从输入流中获取的一行字符串，第二个参数要比第一个参数实际的空间大1用来存储额外的结尾空字符（函数会自动加上），第三个参数则是可选的，用作分界符的字符，上述函数都再读取最大数目的字符或遇到换行符/分节符厚停止，**并移除换行符/分节符**。     
```
char line[50];   
cin.getline(line, 50);   
```   
像上面这个情况，只能读取49个字符，因为最后一个字符留给空字符了。   
### get()   
get既可以单独获取字符，也可以获取字符串。   
单独获取字符有两个函数：   
```c
char ch1, ch2;   
cin.get(ch1);  
ch2= cin.get();    
```   
通过get来获取单个字符能正常获取包括空格回车等符号。   
也可以通过单纯的cin.get()来跳过一些不需要的符号。   
get也可以获取字符串。其原型为：   
```c
istream& get(char*, int, char);   
istream& get(char*, int);   
```   
第一个参数为保存的地址，第二个参数要比第一个参数实际的空间大1用来存储额外的结尾空字符（函数会自动加上），第三个地址为分节符。   
**另外这个函数并不会由于空格和tab截断，会保留空格和tab，仅仅遇到回车停止，并且不移除回车符。**        
因此在使用这个函数的时候，如果需要移除回车符，可以酌情使用get函数来进行移除。   
### ignore()
ignore可以从输入流中移除指定数量的字符。其原型为：   
```c
istream& ignore(int=1, int=EOF);  
```   
通常可以这么使用：   
```c
cin.ignore(255, '\n');   
```   
以上移除255个字符，遇到换行符结束。（包括换行符）    
移除两行可以这么操作：   
```c
cin.ignore(255, '\n').ignore(255, '\n');   
```     