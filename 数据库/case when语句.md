## case when语句
case when语句是sql中类似于c++中的swith case语句。   
可以根据条件返回相应的内容。   
严格的意义上来讲case函数是流程控制语句，不是简单意义上的函数，不过为了方便，很多人将case函数称为流程控制函数。    
case when语句有2种用法。   
### 用法一
```
case expression  
when value1 then returnvalue1   
when value2 then returnvalue2  
when value3 then returnvalue3  
else defaultvalue   
end   
```   
case函数对表达式expression进行测试，如果expression等于value1则返回returnvalue1。依次类推如果不符合条件的所有的when条件，就返回默认值defaultvalue。   
上面的用法显得很抽象，可以看下面的举例。  
比如T_customer表中的flevel字段是整数类型，它记录着客户的级别，如果是1是VIP用户，如果是2就是高级用户，如果是3就是普通用户，在制作报表的时候不应该把1,2,3这样的数字显示在报表中而应该显示它的文字，这里就可以用case函数来实现。   
```
select fname,
(
　　case flevel
　　when 1 then 'VIP客户'
　　when 2 then '高级客户'
　　when 3 then '普通客户'
　　else '客户类型错误'
　　end
) as flevelName from T_customer
```   
判断的是flevel作为一个整数的值，是否与各个when后面的值相等，返回的是字符串，也就是说，结果会以字符串进行返回。   
### 用法二
上面的case用法，仅仅使用简单的“==”相等的逻辑进行判断，有时候可能需要判断一些复杂的，比如不等于，比如大于小于，则需要用到另外一种case when的用法。  
```
case 
when condition1 then returnvalue1
when condition2 then returnvalue2
when condition3 then returnvalue3
else   defaultvalue
end
```   
与上面显而易见的区别，case后面是不跟具体的值的；   
conditions1、2、3是表达式，并不是一个值，也就是说我们可以在conditions里进行任意值的比较。其他部分与用法一一致。   
举例说明下面的sql语句判断一个人的体重是不是正常，如果体重大于50偏重，小于40偏轻，介于40到50之间正常。   
```
select
fname,fweight,(
case
when fweight <40 then 'thin'
when fweight > 50 then 'fat'
else 'ok'
end
) as isnormal
from T_person.
```   
值得注意的是，返回值不止能返回字符串，也能返回值。   
比如下面这张交易表中，如果交易方向side等于1或2，则返回filled_turnover的值。   
```
select run_id, 
	SUM(case when side=1 then filled_turnover else 0 end) as bid_cash,
	SUM(case when side=2 then filled_turnover else 0 end) as ask_cash
FROM trade   
```   
### 注意
值得注意的是，case when语句是流程控制语句，也就是说，如果满足第一个条件以后，它就会返回，并不会去判断后面顺序的语句，这一点在使用的时候需要格外注意。  