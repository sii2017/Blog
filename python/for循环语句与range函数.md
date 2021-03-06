## for循环语句与range函数
### for循环语句
python的for循环语句可以直接迭代“序列对象”的所有成员。在迭代结束后，自动结束循环，语法如下：   
```Python
for itr in list:   
```   
其中itr就是从序列对象第一个开始的对象，list则是需要迭代的序列对象。   
比如可以这么迭代   
```Python
list1 = [1, 2, 3, 4]   
for i in list1:   
	print(i)   
```   
这样就能依次输出list1中的所有内容了。  
> 值得注意的是，for循环中的迭代对象与序列对象中实际对象，有着不同的内存地址，因此在for循环中直接修改元素，是无法影响到原来的序列对象的。    
### range函数
前面介绍的for循环是一种迭代的循环机制，和Java、C++等传统编程语言的for循环有所不同。那么，Python能不能提供类似于传统的for循环功能呢？实现循环从一个数字开始计数到另一个数字，一旦到达最后的数字或者某个条件不再满足就立刻退出循环。    
Python提供的range函数可以让for循环实现上面的功能，可以让for循环从0到10计数，或者从10到100每次递增5。   
语法如下：   
```Python
range(start, end, step=1)   
```   
range会返回一个整数序列，statr为整数序列的起始值，end为整数序列的结束值，在生成的整数序列中，不包含结束值。step为整数序列中递增的步长，默认为1。   
如果只有一个参数，那么默认从0执行到参数减一。   
```Python
for i in range(10):
    print(i)
for i in range(0, 10):
    print(i)
for i in range(0, 10, 1):
    print(i)
```   
以上都会输出0-9。   
如果有需求，也可以以不同的起点不同的步骤进行输出。   
```Python
for i in range(10, 1000, 15):
    print(i)  
```  
上面的代码将会从10开始，每次增加15。   
对于一些支持下标访问的序列对象，我们可以用range来实现for循环中下标访问。   
```Python
list1 = [1, 2, 3, 4]

for i in range(len(list1)):
    list1[i] += 10  
```  
这样就可以修改list1的值了。   
不过值得一提的是，Python并不建议在for循环中修改，删除，增加元素。   
这会导致不同的新的和旧的内存空间，有可能会影响正常的迭代。   