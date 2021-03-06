## sed命令
sed命令也是一个管道命令，与grep不同的是，它有着更强大的功能，除了支持各种筛选，还支持增删查改等功能，甚至可以改变源文件。   
### 命令参数  
sed [-nefri] [动作]   
-n，使用安静模式。一般在sed的用法中，当你进行筛选以后，除了你删选的内容，原本的内容也会一起输出在cmd中，就会造成重复输出。当选择了n以后，仅输出set特殊处理过的那几行。   
-e，直接在命令行模式进行sed的动作编辑。   
-f，执行一个文件内的sed动作。   
-r，sed的动作默认支持基础正则表达式语法，如果加了r则支持扩展型正则表达式语法。   
-i，直接修改读取的文件内容，而不是由屏幕输出。   
动作说明：   
[n1,n2]function   
n1和n2一般代表进行动作的行数。   
动作行为有以下参数：   
a，新增，会在选择行的下一行显示。   
c，替换，c后面接的字符串可以替换n1和n2之间的行。  
d，删除，通常不接任何参数。   
i，插入，可接字符串，会在目标行的上一行新增一行内容。   
p，打印，讲某个选择的数据打印出来。   
s，替换，可以进行替换工作。   
### 新增删除功能例子 
新增分两种，一种是在指定行之前[i]，一种是在指定行之后[a]。  
```c
nl /etc/passwd | sed '2a abc'   
nl /etc/passwd | sed '3i uuu'   
nl /etc/passwd | sed '3i uuu\
ccc\
aaaa'
```   
上面的第一个命令是在第二行的后面加入abc，然后是在第三行之前插入uuu。   
而第三个命令则是插入多行。   
```c
nl /etc/passwd | sed '10d'   
nl /etc/passwd | sed '10,15d'   
nl /etc/passwd | sed '10,$d'  
```   
上面的第一个命令是删除第十行，第二个命令是删除10-15行。   
而第三个命令代表删除10到最后，$代表最后一行。   
### 整行替换
```c
nl /etc/passwd | sed '2,5c uuuuu'   
```  
以上命令将2-5行替换成了uuuu，但是值得注意的是，只替换成一行uuuu，而不是每一行。   
### 定点输出  
```c
nl /etc/passwd | sed -n '5,7p'   
```  
以上命令可以直接输出5-7行。   
### 字符串替换
与之前整行替换不同，字符串替换，仅替换掉选中的字符串，不影响该行其他的内容。  
替换字符串有着自己的格式。   
sed 's/要替换的内容/新的字符串/g'   
做个例子   
```c
nl /etc/passwd | sed 's/sii/peter/g'   
```  
以上命令将所有sii字符串替换成peter。   
```c
nl /etc/passwd | sed 's/^.*sii/peter/g'  
nl /etc/passwd | sed 's/abc$/peter/g'  
```   
这两个命令用到了基础正则表达式规则，稍显复杂。  
第一个命令是找到所有开头包含sii的字符串替换成peter。  
第二个命令是找到所有abc结尾的字符串替换成peter。   
具体的正则表达式的内容可以参考同目录下《正则表达式》   
### 直接修改文件内容
最后，我们不将set作为管道命令使用，而是直接作为命令来修改文件内容。   
这种做法是危险的，不要用在系统文件上。   
```c
sed -i 's/\.$/\!/g' abc.text   
```  
将abc中所有点的解位，替换成感叹号。   
主要还是-i这个参数。   
值得注意的是.和！在命令中都有着特殊意义，所以需要用\来进行转义。  