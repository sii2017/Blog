## offset 和fetch next 数据分页
offset and fetch是Sql Server 2012中的新特性。  
其语法简介，功能强大，效率也不错。主要功能是用来分页返回数据的。  
### 使用方法
```
select * from Product order by order_id   
offset 100 fetch next 100 rows only   
```  
以上sql语句意味，从Product里取所有列，取101到200的行数。   
offset的值，代表移动到多少行以后。   
fetch next的值，代表取多少行的数据。   
最后rows only不要忘记。   
这个语法比之前的ROW_NUMBER()要简单的多。  
> 值得注意的是，offset和fetch next的值也支持表达式的形式。  