## ifstream ofstream对象
ostream是ofstream类的基类，istream是ofstream类的基类，因此可以使用所有ostream和istream的方法。   
### 头文件
使用ifstream和ofstream对象需要包含头文件。  
```c
#include <fstream>   
```  
对于大多数实现来说，博阿寒fstream便自动包含了iostream文件。      
### 输出流
1 通过创建ofstream对象来管理输出流。  
2 将该对象与特定的文件关联起来。   
3 以使用类似于cout的方式使用该文件，唯一的区别是输出将写入文件，而不是显示在屏幕上。   
```c
ofstream fout;   //创建对象  
fout.open("xxx.txt");  //通过open将对象与文件关联起来   
```   
另外ofstream类也提供了相关的构造函数，可以直接初始化并关联。   
```c
ofstream fout("xxx.txt");   
```   
然后就是如同cout的方式来写入文件了。   
```c
fout << "now I input some words";   
fout.close();   //断开流与文件关联  
```
ofstream类使用被缓冲的输入，因此程序在创建fout这样的ofstream对象时，将为输出缓冲区分配空间。如果创建了两个ofstream对象，程序将创建两个缓冲区，每个对象各一个。   
像fout这样的ofstream对象从程序那里逐字节的收集输出，当缓冲区填满后，它便将缓冲区内容一同传输给目标文件。由于磁盘驱动器设计成以大块的方式传输数据，而不是逐字节的传输，因此通过缓冲可以大大提高从程序到文件传输数据的速度。   
> 注意，以默认模式打开文件进行输出，如果没有这样的文件将创建一个新文件，如果有这样的文件将会清空文件。   
### 输入流
1 创建一个ifstream对象来管理输入流；  
2 将该对象与特定的文件关联起来；   
3 以使用cin的方式使用该对象。   
```c
//分两步创建和绑定文件   
ifstream fin;   
fin.open("xxx.txt");   
//通过构造函数一步完成   
ifstream fin("xxx.txt");   
```
接下来可以像使用cin一样将文件内的一些数据输入到我们的变量中。   
```c
char ch;   
fin>> ch;   //读一个字符到ch中  
char buf[80];   
fin>> buf;  //读一个词到ch中  
fin.getline(buf, 80);	//读一行   
string line;   
getline(fin, line); 	//读一行到string中  
```  
断开关联也一样。  
```
fin.close();  //断开流与文件的关联  
```   
### 流状态检查
c++文件流类从ios_base类那里继承了一个流状态成员，可以检测当前流的状态。   
```c
fin.open("acb.txt");  
if(fin.fail()){}	
if(!fin){}    
if(!fin.good()){}   
//以上三种是比较旧的方式，下面是新的c++实现方式  
if(!fin.is_open()){}   
```   
### 重置流状态
对于流对象有一个clear函数。   
```c
fin.clear();   
fout.clear();   
```  
clear函数用来重置流的状态，以便可以绑定一个新的文件。   
有些c++实现要求在程序末尾使用fin.clear，有些则不要求，这取决于将文件与ifsream对象关联起来时，是否自动重置流状态。但是使用这个函数总是无害的。   
### 文件模式
如同其它打开文件的方式，fstream也有自己的文件模式，通过继承而来。   
模式参数是放在open函数的第二个参数或者是构造函数的第二个参数。   
```c
ifstream fin("xx.xtx", mode1);   
ofstream fout;  
fout.open("sss.txt", mode2);    
```    
模式有如下可选：   
ios_base::in 只读   
ios_base::out 只写   
ios_base::ate 移动到文件尾   
ios_base::app 追加到文件尾   
ios_base::trunc 如果文件存在则截短文件，即删除以前的内容    
ios_base::binary 二进制方式打开  
其中ate和app的区别在于，app只允许将数据添加到文件尾，而ate模式将指针放在文件尾。   
#### 二进制使用

