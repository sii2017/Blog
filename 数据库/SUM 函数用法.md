## SUM 函数用法
SUM函数返回数值列的总数（总额）。    
### 语法
```
select SUM(column_name) from table_name   
```   
### 用法
如果要获取一个表里order_amount字段的总和可以这么写。   
```
select SUM(order_amount) AS order_total from orders  
```  
另外也可以进行统计，比如orders表里，除了order_amount，有不同的顾客姓名name。那么如果想知道每个顾客的商品总数。   
```
select name, SUM(order_amout) AS order_total from orders  
```  
那么就会以name，order_total的形式返回，会根据name进行分类计算。   