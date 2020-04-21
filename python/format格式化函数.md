## format格式化函数
Python2.6 开始，新增了一种格式化字符串的函数 str.format()，它增强了字符串格式化的功能。  
基本语法是通过 {} 和 : 来代替以前的 % 。   
### 通过位置格式化
```Python
print("{} {}".format("hello", "world"))  # hello world
print("{0} {1}".format("hello", "world"))  # hello world
print("{0} {0} {0} {0}".format("hello", "word")) # hello hello hello hello   
```  
可以看到，如果{}中为空，则默认以默认顺序输出后面的参数。这种情况下，后面的参数要大于等于前面{}的数量。   
如果{}中有数字，则将数字当作位置，按顺序输出后面的文字。   
### 通过参数格式化   
```Python
# 通过设置参数
print("name is {name}, age is {age}".format(name="sii", age=18))

# 将字典作为参数
dict1 = {'name': 'sii', 'age': '19'}
print("name is {name}, age is {age}".format(**dict1))

# 将列表作为参数
list1 = ['sii', 20]
print("name is {0[0]}, age is {0[1]}".format(list1))
```   
可以看到，字典和列表也可以作为参数传入。   
### 通过传入对象格式化
```Python
class AssignValue(object):
    def __init__(self, value):
        self.value = value
my_value = AssignValue(6)
print('value 为: {0.value}'.format(my_value))  # "0" 是可选的
```  
这个其实和字典及列表作为参数，是类似的。   
### 数字的格式化
数字的格式化会用的普遍一些。   
```Python
print("{:.2f}".format(3.1315926));  # 3.14
```   
![](https://github.com/sii2017/image/blob/master/python_format.png)   
规则可以按照上图。  
另外，我们可以用大括号来转义大括号。   
```Python
print ("{} 对应的位置是 {{0}}".format("runoob"))    # runoob 对应的位置是 {0}    
```