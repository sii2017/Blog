## 使用CStdioFile操作文件
文件操作在VC编程中使用非常普遍，直接使用CFile对文件进行操作比较繁琐，使用继承自CFile的CStdioFile类就要容易得多，用CStdioFile来处理字符串，是最简单最好理解的的办法。    
CFile类默认的是按照二进制模式操作文件。   
二进制模式：对于一行的结尾我们必须输入'\r\n'，才能表示回车换行的效果。   
另外有一种Text模式：'\r'回车的工作是自动完成的，我们只需要写入'\n'即可。在使用Text模式时从外部读入文件时，'\r\n'会被翻译成'\n'，写入文件时，我们对于回车换行只需提供'\n'，即可，'\r\n'会被写入到文件中。    
### 打开文件
```c
CStdioFile file;   
file.Open(FileName, CFile::modeCreate|CFile::modeReadWrite|CFile::modeNoTruncate);    
```   
打开文件主要需要传入两个参数，FileName文件名以及文件打开模式。   
**几种常见的文件打开模式：**   
> CFile::modeCreate 以新建方式打开，如果文件不存在，新建；如果文件已存在，把该文件长度置零，即清除文件原有内容。   
CFile::modeNoTruncate 以追加方式打开，如果文件存在，打开并且不将文件长度置零，如果文件不存在，会抛出异常。一般与CFile::modeCreate 一起使用，则文件不存在时，新建一个文件；存在就进行追加操作。   
CFile::modeWrite 以只写模式打开    
CFile::modeRead 以只读模式打开    
CFile::modeReadWrite 以读写模式打开    
  
### 读文件
```c   
virtual LPTSTR ReadString( LPTSTR lpsz, UINT nMax ) throw( CFileException );    

BOOL ReadString(CString& rString) throw( CFileException );    
```   
CStdioFile的ReadString方法可以**逐行**从文件中读取内容，该例将文件逐行读出，写入到str字符串里。   
如果需要读出文件所有内容，可以用下面的方法：   
```c
while(file.ReadString(str))      
{    
    filestr=filestr+str+"\r\n";     
}     
```   
这里用”\r\n”来为字符串加上换行。    
### 写入文件
```c
CStdioFile file;  
file.WriteString(str);   
```   
与之前的ReadString不同，WriteString并不提供逐行写入的方法，只有自己在文件内容行的末尾增加"\n"或者"\r\n"实现换行的功能。    
需要注意的是：如果文件的打开模式设置了CFile::modeNoTruncate，那么字符串将以追加的形式写入，并且是从文件指针现在所处位置写起（默认为起始位置）。也就是说，**新加入的文字会从初始位置开始覆盖掉原来的内容。**    
需要在写入之前使用：  
```c
file.SeekToEnd();   
```   
将游标移动到文件末尾，这样就不会覆盖掉原有内容，而是从最后开始追加了。   
### 移动指针
```c
CStdioFile::Seek( LONGLONG Off, UINT nFrom );   
```    
第一个参数为移动的字节数。   
第二个参数为模式，必须为下列值之一：   
CFile::begin:从文件开始将文件指针 移动Off字节。   
CFile::current:从当前位置将文件指针移动Off字节。  
CFile::end:从文件的结尾将文件指针移动Off字节。    
### 关闭文件
同CFile类得实例一样，使用完CStdioFile记得调用Close函数将其关闭。   
```c
file.Close();   
```
### 在Unicode编码环境下使用CStdioFile操作文件
Unicode环境下，由于使用的是unicode而不是一般的ANSI，所以需要对各个地方（比如地址和输入的内容）进行一定的转换，才能正常使用。   
> 关于转换的内容，可以查看本目录下《字符串之间的转换》。   
```c
//将需要写入的内容转换成unicode   
int per= 1234;   
char temp[256];   
sprintf(temp, "%d", per);   
USES_CONVERSION;   
CString s = A2T(temp);  
 
CStdioFile file;    
CString filePath = L"C:\\Users\\LJ2\\Desktop\\interesting.dat";//保存地址也使用unicode         
if (file.Open(filePath, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary | CFile::modeNoTruncate))    
{   
	file.SeekToEnd();   
	file.Write(s.GetBuffer(), s.GetLength() * 2);//需要使用Write并加入字节数，而不是之前的WriteString函数    
	file.Close();   
}   
else   
{   
	int error = 0;   
}    
```    