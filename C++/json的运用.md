## json的运用
JSON(JavaScript Object Notation) 是一种轻量级的数据交换格式。易于人阅读和编写。同时也易于机器解析和生成。它基于JavaScript Programming Language, Standard ECMA-262 3rd Edition - December 1999的一个子集。    
JSON是Douglas Crockford在2001年开始推广使用的数据格式，在2005年-2006年正式成为主流的数据格式，雅虎和谷歌就在那时候开始广泛地使用JSON格式。    
### json语法
JSON是一个标记符的序列。这套标记符包含**六个构造字符、字符串、数字和三个字面名**。    
JSON是一个序列化的**对象或数组**。     
#### 六个构造字符
begin-array（数组开始符号）= [ 左方括号    
begin-object（对象开始符号）= { 左大括号    
end-array（数组结束符号）= ] 右方括号   
end-object（对象结束符号）= } 右大括号   
name-separator =  : 冒号
value-separator = , 逗号
#### 空白符
在以上在这六个构造字符的前或后允许存在无意义的空白符(ws):   
ws = 空间; 水平标签; 换行或换行; 回程    
#### JSON的值
JSON的构成: **ws 值 ws**    
值可以是**对象、数组、数字、字符串或者三个字面值(false、null、true)中的一个**。   
值中的字面值中的英文必须使用小写。     
对象由花括号括起来的逗号分割的成员构成，成员是字符串键和上文所述的值由逗号分割的键值对组成，如：   
{"name": "John Doe", "age": 18, "address": {"country" : "china", "zip-code": "10000"}}
**数组**是由方括号括起来的一组值构成，如：    
[3, 1, 4, 1, 5, 9, 2, 6]    
字符串与C或者Java的字符串非常相似。字符串是由双引号包围的任意数量Unicode字符的集合，使用反斜线转义。一个字符（character）即一个单独的字符串（character string）。     
数字也与C或者Java的数值非常相似。除去未曾使用的八进制与十六进制格式。除去一些编码细节。     