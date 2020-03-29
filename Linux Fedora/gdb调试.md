## gdb调试
在linux程序调成中gdb是最常用的工具。   
关于gdb的说明可以在linux下直接 man gdb或者gdb --help。   
如果需要程序支持gdb调试，在编译的时候需要加入-g的参数。   
```
gcc main.c -g   
```  
### gdb命令
gdb使用shell命令gdb来调用，一旦开始，就从终端读取命令直接gdb退出，你可以通过help命令获取帮助信息。   
可以不带任何参数或选项执行gdb命令，但是最常用的启动gdb的方式是带一个或者两个参数，指定一个可执行文件来作为参数:    
```
gdb program(gdb+可执行文件名称)    
```
也可以再gdb文件后面指定可执行文件 和 core文件的名称:    
```
gdb program core（gdb + 可执行文件 +core文件）     
```
下面是调试命令：   
```
break [file:]function/行数
```
设置一个断点在函数中(在文件中)
```
run [arglist]    
```
启动程序带上指定的参数，run是直接运行程序。    
```
start   
```   
start与run相似，但是start运行到第一句命令后会停住，等你按n或s继续。   
```
bt    Backtrace
```
显示堆栈    
```
print expr
```
显示表达式的值    
```
continue/c      
```
继续执行你的程序(程序停住后，例如:在断点处停止)    
```
next/n  
```
执行程序的下一行代码(程序停止以后)；跨过任何当前行的函数调用。   
```
step  单步调试
```
执行程序的下一行（程序停住后），进入当前行的函数调用的内部。 
```
display disp   
```
跟踪查看某个变量,每次停下来都显示它的值。   
```
watch  
```
监视变量值的变化，每次变化都会提示。  
```
edit [file:]function
```
查看当前程序停在哪。   
```
list [file:]function
```
显示程序当前停住的代码行附近的代码  
```
help [name]
```
显示gdb命令的相关信息。     
```
quit  
```
退出gdb。    