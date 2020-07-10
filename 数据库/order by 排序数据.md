## order by 排序数据
在select数据都时候，显示是以默认在数据库里的顺序进行显示的。如果需要排序可以用order by关键字。   
### 根据列名进行排序
order by可以取一个或多个列的名字。   
如果只取一个，则根据这一个进行排序；  
如果取多个列，则先根据第一个进行排序，如相同再根据后一个排序，一次类推。   
> 应该保证order by子句是select语句中的最后一条子句。   
  
```
select prod_name from Products   
order by prod_name   
```  
以上是根据prod\_name进行排序。   
```
select prod_id, prod_price, prod_name from Products  
order by prod_price, prod_name   
```  
以上是先根据prod\_price进行排序，如果相同则再根据prod_name进行排序。   
### 根据位置进行排序  
order by子句也支持根据列位置进行排序。   
```
select prod_id, prod_price, prod_name from Products  
order 2, 3   
```   
但是通常这是不建议使用的，因为不明确给出列名可能造成错用列名排序。   

### 指定排序方向 
order by默认情况下是根据升序排序的。   
如果希望根据降序进行排序，则需要指定DESC关键字，即为desending的缩写。   
```
select prod_name from Products   
order by prod_name DESC  
```  
如果要对多个列都进行排序的时候，DESC关键字只对当前列有效，如果有多个列都需要进行降序排序的话，则需要对指定列都添加DESC关键字。   
```
select prod_id, prod_price, prod_name from Products  
order by prod_price DESC, prod_name DESC  
``` 
> 升序其实也有关键字ASC，但是并没有什么用处，因为order by子句默认就是升序的。   
### 注意
由于数据库底层的设计，如果order by的关键字有重复的现象，需要警觉。  
一些由于关键字重复而没有被排序的数据，并不会总是以数据库中默认的顺序，返回到我们这里。而是数据库先读取到谁，则显示谁。   
因此，如果order by的关键字有重复的现象，那些没有被排序的数据，**将会以随机的顺序出现**。有时候会造成无法估计的问题。   
比如，如果order by的关键字有重复的现象，再使用offset fetch next语法来分页，**则分页很有可能会有重复的数据**。   