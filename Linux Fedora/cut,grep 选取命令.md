## 选取命令cut,grep
选取命令通常是将一段数据分析后，取出我们想要的内容，展示出来。   
选取命令一般用在管道命令（|）后比较多一些。   
### cut
cut命令可以将一段信息的某一段根据要求切出来。   
处理的信息是以“行”为单位的，也就是说如果有多行信息，那么的操作会依次对“每一行”进行处理。   
cut只有3个可选参数，其中-d和-f是一起用的：   
-d，后面接分割字符，也就是根据什么字符，进行数据的分割。   
-f，根据-d的分割字符，将一段信息切割为数段，-f后跟的数字，意味着第几段的意思。   
> 通常，一个数字就是一段。为什么是数段呢，当你输入多个数字以后（以逗号分隔），那么就能分割出数段信息来。   
  
-c，以字符的位置，取出某一段数据。   
#### -d -f的使用
当我们输入   
```
echo $PATH   
```   
的时候，会显示PATH里的路径，并且以冒号间隔。   
/home/sii/.local/bin:/home/sii/bin:/usr/share/Modules/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/root/bin   
如果我们只想显示第2个地址呢？   
```c
echo $PATH| cut -d ':' -f 2   
```   
就能显示出/home/sii/bin了。   
如果想显示第二个和第四个呢？    
```c
echo $PATH| cut -d ':' -f 2,4     
```   
以上就是-d，-f的用法。当然并不一定要冒号作为分隔符，可以随机应变。   
#### -c的使用
-d和-f是以间隔符作为条件，取出特定段落。而-c是以字符位置为间隔取段，有点像string的substr。   
同样是   
```
echo $PATH   
```    
如果我们想显示第三个字符到第五个字符，那么   
```
echo $PATH| cut -c 3-5   
```  
注意，这里的字符位置是从1开始算的，而不像代码中从0开始。   
如果我们想要5开始后的所有数字，那么  
```
echo $PATH| cut -c 5-   
```   
如果我们想要10之前的所有数字，那么   
```
echo $PATH| cut -c -10      
```   
### grep
grep的特点是，根据筛选条件，在多行数据中，给我们展现满足条件的几行。   
如果比较一下的话cut展现的是一行中的段落，而grep展现的是满足条件的整行。   
grep的用法如下：   
grep [-acinv] '查找字符串' filename   
参数如下：   
-a 将binary文件以text文件的方式查找数据。   
-c 计算找到‘查找字符串’的次数。  
-i 忽略大小写的不同，即不区分大小写。   
-n 输出行号。（并非重新排序，不满足条件的行号仍不显示）   
-v 反向选择，即显示没有出现过关键字的行。   
-A A后跟数字，即after结果的n行也显示出来。   
-B B后跟数字，即before结果的n行也显示出来。  
[] 在搜索的字符串中，加入[]，在该括号中，无论有多少字母，都只代表一个字母，是或的意思。   
打个比方：   
通常查进程用的是   
```
ps -ef   
```  
然后会出现一两百行进程，如果我们只想看包含root字符串的进程，那么我们应该输入    
```
ps -ef| grep root   
```  
那么所有包含root字符串的行，都会显示出来。   
### 组合
grep是能与cut进行组合使用的，通过管道命令。   
比如，我们在last的输出信息中，只要有root行便取出，并且只显示第一列。   
```
last| grep root| cut -d ' ' -f 1    
```