## distinct 去重关键字
通常在表中查询数据的时候，有时候会查询出许多一模一样的数据。  
这时候通过distinct关键字，可以仅返回显示唯一不同的值。   
比如一张学校学生信息的表，包含学生的姓名、班级、年龄等。  
如果我们要查询学生的班级，想知道这个表里有几个班，那么所有在同一个班的学生的班级信息都会是重复的。   
```
select class from Students  
```  
会显示出非常多重复的数据。   
class   
1  
1  
1  
1  
1  
...   
2  
2   
2  
2   
2   
...   
3   
3   
3   
...  
这时候就能用到distinct关键字进行去重了。   
### distinct关键字用法  
通常distinct与select是一起使用的，与select相连，在select关键字之后。   
```
select distinct class from sutdents   
```  
这样，显示出来的班级，仅仅显示唯一的，去除了重复的。   
class  
1  
2  
3   