## select基础查询语句
select语句用于从表中选取数据。  
通常select与from进行结合使用。   
### select语法
```
select 列名称 from 表  
```  
sql语句对大小写不敏感，因此大小写都有着同样的效果。   
### select实例  
```
select ID from Persons   
```  
以上语句意为，从Persons这张表中提取所有的ID字段列。   
```
select * from Tables  
```  
以上语句意为，从Tables这种表中提取所有的字段。   
> \*号代表所有的字段。   