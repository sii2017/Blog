## 列表
列表（`list`），是一种结构化的、非标量类型，它是值的有序序列，每个值都可以通过索引进行标识，定义列表可以将列表的元素放在`[]`中，多个元素用`,`进行分隔，可以使用`for`循环对列表元素进行遍历，也可以使用`[]`或`[:]`运算符取出列表中的一个或多个元素。    
### 定义及遍历
下面的代码演示了如何定义列表、如何遍历列表以及列表的下标运算。   
```Python
list1 = [1, 3, 5, 7, 100]
print(list1) # [1, 3, 5, 7, 100]
# 乘号表示列表元素的重复
list2 = ['hello'] * 3
print(list2) # ['hello', 'hello', 'hello']
list2 = ['hello' * 3]   
print(list2) # ['hellohellohello']   
# 计算列表长度(元素个数)
print(len(list1)) # 5
# 下标(索引)运算
print(list1[0]) # 1
print(list1[4]) # 100
# print(list1[5])  # IndexError: list index out of range
print(list1[-1]) # 100
print(list1[-3]) # 5
list1[2] = 300
print(list1) # [1, 3, 300, 7, 100]
# 通过循环用下标遍历列表元素
for index in range(len(list1)):
    print(list1[index])
# 通过for循环遍历列表元素
for elem in list1:
    print(elem)
# 通过enumerate函数处理列表之后再遍历可以同时获得元素索引和值
for index, elem in enumerate(list1):
    print(index, elem)
```
实际上即使是类型不同的元素也可以放在同一个列表中   
```python
list3 = [1, 2, "name", 'sym']   
print(list3)  # [1, 2, 'name, 'sym']    
```  
### 移除元素
下面的代码演示了如何向列表中添加元素以及如何从列表中移除元素。   
```Python
list1 = [1, 3, 5, 7, 100]
# 添加元素
list1.append(200)
list1.insert(1, 400)
# 合并两个列表
# list1.extend([1000, 2000])
list1 += [1000, 2000]
print(list1) # [1, 400, 3, 5, 7, 100, 200, 1000, 2000]
print(len(list1)) # 9
# 先通过成员运算判断元素是否在列表中，如果存在就删除该元素
if 3 in list1:
	list1.remove(3)
if 1234 in list1:
    list1.remove(1234)
print(list1) # [1, 400, 5, 7, 100, 200, 1000, 2000]
# 从指定的位置删除元素
list1.pop(0)
list1.pop(len(list1) - 1)
print(list1) # [400, 5, 7, 100, 200, 1000]
# 清空列表元素
list1.clear()
print(list1) # []
```
值得注意的是，remove根据值来删除元素，且只能删除一个元素，如果有多个元素相同，但是也只删除第一个。   
pop则是根据位置删除，需要确认是否存在该位置。   
### 切片操作
和字符串一样，列表也可以做切片操作，通过切片操作我们可以实现对列表的复制或者将列表中的一部分取出来创建出新的列表。   
```Python
fruits = ['grape', 'apple', 'strawberry', 'waxberry']
fruits += ['pitaya', 'pear', 'mango']
# 列表切片
fruits2 = fruits[1:4]
print(fruits2) # apple strawberry waxberry
# 可以通过完整切片操作来复制列表
fruits3 = fruits[:]
print(fruits3) # ['grape', 'apple', 'strawberry', 'waxberry', 'pitaya', 'pear', 'mango']
fruits4 = fruits[-3:-1]
print(fruits4) # ['pitaya', 'pear']
# 可以通过反向切片操作来获得倒转后的列表的拷贝
fruits5 = fruits[::-1]
print(fruits5) # ['mango', 'pear', 'pitaya', 'waxberry', 'strawberry', 'apple', 'grape']
```
### 排序操作
下面的代码实现了对列表的排序操作。
```Python
list1 = ['orange', 'apple', 'zoo', 'internationalization', 'blueberry']
list2 = sorted(list1)
# sorted函数返回列表排序后的拷贝不会修改传入的列表
# 函数的设计就应该像sorted函数一样尽可能不产生副作用
```
也可以通过通过reverse关键字来进行倒叙排序。             
```Python  
# 倒叙排序    
list3 = sorted(list1, reverse=True)    
```   
通过key关键字根据长度排序。   
```Python
# 通过key关键字参数指定根据字符串长度进行排序而不是默认的字母表顺序  
list4 = sorted(list1, key=len)     
```   
以及在原列表对象进行排序。   
```Python
# 给列表对象发出排序消息直接在列表对象上进行排序
list1.sort(reverse=True)  
print(list1)  
```  
### 颠倒顺序
上面的是根据值来排序，还有一个颠倒顺序的操作也是日常用的比较多的，通过reverse成员函数。   
```Python
list1.reverse()   
```  
这样就能在原有基础上直接颠倒顺序了。  