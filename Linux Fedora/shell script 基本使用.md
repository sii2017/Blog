## shell script 基本使用
shell script是针对shell写的脚本文件。   
即利用shell的功能所写的一个“程序”，这个程序使用纯文本文件，将一些shell的语法和命令（含外部命令）写在里面，搭配正则表达式、管道命令和数据流向等功能，达到我们所想要的处理目的。   
### 注意事项及规则
1 命令的执行是从下而下，从左而右的分析和执行；  
2 命令与参数间的多个空白都会被忽略掉；   
3 空白行也会被忽略掉，tab所得的空白会被认为是空格；  
4 如果读取到一个Enter符号（CR）则尝试开始执行命令；   
5 如果一行的内容太多，可以使用\加上回车，来扩展到下一行；   
6 \#符号可以作为批注。任何家在后面的数据都被视为批注文字而被忽略。   
### 指定命令解释器  
通常在shell scrpit的第一行，会通过#!符号指定该脚本的命令解释器。     
\#!/bin/bash    
是的，通常，\#这个符号代表着批注、注释，是会被忽略的。但是与!想结合，则代表着指定命令解释器。   
\#!/bin/sh    
以上两条分别表示选择bash和选择sh作为解释器运行这个脚本的命令。   
> 在一些linux系统中sh与bash相同，但是在一些系统中他们属于子集的关系。   
> ps，在fedora系统中，实测bash和sh为相同的。  
   
另外也可以选在在第一行并不指定解释器，那么会使用默认的解释器，如果有一些解释器不支持的命令，则会无法执行脚本文件。   
### 最简单的shell script的编写和执行
脚本内容如下：  
```
#! /bin/bash  
PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin   
export PATH   
echo -e "Hello World! \a \n"   
exit 0   
```   
如上所示，  
第一行是选择解释器；   
第二行第三行则是指定环境路径，这样，当我们的脚本中涉及到一些外部命令的时候就可以直接使用，而不用写绝对路径了。当然本脚本里的echo并不需要这个PATH也可以正常运行。。   
第四行则是返回值，我们可以使用$?来获取上一条命令的返回值。这样我们可以自定义返回码，来确认是否执行成功了，或者作为错误码指出执行发生了什么错误。   
最后使用   
```
sh xxx.sh    
```    
来执行命令。    
另外也可以给脚本文件加上可执行权限，然后直接使用它来执行命令。   
```   
chmod a+x xxx.sh   
./xxx.sh   
```  
### 简单的交互式脚本
以下脚本用到了2个常用的基本功能；   
1 跟用户交互，获取输入的值；   
2 将一些数值保存在了变量当中。  
```
#! /bin/bash   
read -p "PLease input your first name: " firstname
read -p "Plaease input your last name: " lastname
echo -e "\nYour first name is $firstname, last name is $lastname"
```  
上面这个脚本的内容，是显示字符串让用户分别输入姓和名，并且保存在变量firstname和lastname中，最后一起输出出来。   
firstname和lastname两个变量是通过read命令来保存的。   
使用是比较简单的。  
### 简单的利用日期进行
以下脚本则用到了这么几个功能：  
1 变量的使用；  
2 通过$来获取其他命令返回的值；  
3 将文件名和时间组合起来；  
4 最后通过touch输出。   
```
#! /bin/bash  
filename=back_
date=$(date +%Y%m%d)
file=${filename}${date}
touch "$file"
```
### 使用算术运算符   
以下脚本让用户输入两个数字，然后进行相乘。最后得出结果。  
```
#! /bin/bash  
PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin
export PATH
read -p "Please input first number: " firstnum  
read -p "Then input second number: " secondnum
total=$(($firstnum*$secondnum))
echo -e "\nThe result of first number * second number is $total"

```  
值得注意的是，total这边需要用两层括号包括起来。   
$(())是固定的做计算的格式。   
### 通过source执行脚本  
我们有另外一种方法执行脚本，就是使用source命令。  
它与直接执行脚本或者使用sh执行脚本是有区别的。  
如果我们使用sh或者直接执行脚本，系统将会新建一个子进程，来执行这个脚本。所有的保存的变量都是在子进程中，当脚本结束，进程结束，那么保存的变量或者其他的变更也就不存在了。   
可以做个测试，当使用sh执行前面的算数脚本后，通过命令  
```
echo $firstnum  
```  
可以看到并没有这个变量的存在。  
但是如果使用source执行脚本，   
```c
source xxx.sh   
```  
再看firstnum，是有值的。  
这是因为source命令是直接在当前进程环境中执行的命令。   
所以让有需要在当前进程中执行脚本的话，source可以帮上忙。  