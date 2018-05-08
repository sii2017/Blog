## 使用CStdioFile操作文件
文件操作在VC编程中使用非常普遍，直接使用CFile对文件进行操作比较繁琐，使用继承自CFile的CStdioFile类就要容易得多，用CStdioFile来处理字符串，是最简单最好理解的的办法。    
### 打开文件
```c
CStdioFile file;   
file.Open(FileName, CFile::modeCreate|CFile::modeReadWrite|CFile::modeNoTruncate);    
```   
打开文件主要需要传入两个参数，FileName文件名以及文件打开模式。   
**几种常见的文件打开模式：**   
CFile::modeCreate 以新建方式打开，如果文件不存在，新建；如果文件已存在，把该文件长度置零，即清除文件原有内容。   
CFile::modeNoTruncate 以追加方式打开，如果文件存在，打开并且不将文件长度置零，如果文件不存在，会抛出异常。一般与CFile::modeCreate 一起使用，则文件不存在时，新建一个文件；存在就进行追加操作。   
CFile::modeWrite 以只写模式打开    
CFile::modeRead 以只读模式打开    
CFile::modeReadWrite 以读写模式打开    
