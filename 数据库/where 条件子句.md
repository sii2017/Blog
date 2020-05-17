## where 条件子句
where子句用于过滤记录。   
当我们需要利用一些特定的条件来筛选并显示sql数据，会用到where。  
### where用法
```
select colume from table_name where colume operator value   
```  
上面的用法有一些抽象。  
where的主要用法是在后面跟上需要的条件，条件一般是一个字段名等于（大于小于及一些其他比较的符号）一个值。   
比如，如果我们要从学生表中找到班级是2班的学生。   
```
select * from student_table where class=2  
```  
这样，出来的数据会经过筛选，仅显示class字段为的数据了。  
### where支持的符号
where子句不仅仅支持等于符号：   
=，等于；   
<>，不等于，在一些SQL的版本中，该符号可能是!=；   
\>，大于；   
<，小于；   
\>=，大于等于；   
<=，小于等于；   
BETWEEN，在某个范围内；   
LIKE，搜索某种模式；   
IN，指定针对某个列的多个可能值；   
### 一些特殊条件   
#### 空值判断   
```
select * from student where name is null   
```  
只查询学生中name为空的数据。   
#### between and   
between在杀那个面说，是用来查找某个范围内的值。通常between与and一起使用。   
```
select * from student where number between 1 and 20   
```  
查找学生学号在1-20之间的学生资料。  
注意使用between的时候，上下两个数字是包含的关系。   
#### in  
针对某个列的多个可能值，比较抽象。   
```
select * from student where number in (1,5,6)   
```  
查询学生的学号是1或5或6的资料。   
#### like
like是模糊查询。   
```
select * from student where name like 'M%'   
```  
查询student表中name列中有M的值，M是要查询内容中的模糊信息。   
>% 表示多个字值，_ 下划线表示一个字符；   
>M% : 为能配符，正则表达式，表示的意思为模糊查询信息为 M 开头的。   
>%M% : 表示查询包含M的所有内容。   
>%M_ : 表示查询以M在倒数第二位的所有内容。    
#### 不带比较运算符的where子句
WHERE 子句并不一定带比较运算符，当不带运算符时，会执行一个隐式转换。当0时转化为false，1转化为true。   
```
select * from student where 0   
```  
以上将会返回一个空集。  
```
select * from student where 1   
```  
以上将会返回全部的值。  