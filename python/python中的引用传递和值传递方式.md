## python中的引用传递和值传递方式
python不允许程序员选择采用传值还是传引用。Python参数传递采用的肯定是“传对象引用”的方式。实际上，这种方式相当于传值和传引用的一种综合。如果函数收到的是一个可变对象（比如字典或者列表）的引用，就能修改对象的原始值——相当于通过“传引用”来传递对象。如果函数收到的是一个不可变对象（比如数字、字符或者元组）的引用，就不能直接修改原始对象——相当于通过“传值’来传递对象。   
当人们复制列表或字典时，就复制了对象列表的引用，如果改变引用的值，则修改了原始的参数。    
为了简化内存管理，Python通过引用计数机制实现自动垃圾回收功能，Python中的每个对象都有一个引用计数，用来计数该对象在不同场所分别被引用了多少次。每当引用一次Python对象，相应的引用计数就增1，每当消毁一次Python对象，则相应的引用就减1，只有当引用计数为零时，才真正从内存中删除Python对象。    
**python3六种数据类型：**   
- Number（数字）   
- string（字符串）   
- list（列表）   
- tuple（元组）   
- set（集合）    
- dictionary（字典）   
其中不可变数据（3个）：number，string，tuple    
可变数据（3个）：list，dictionary，set  
### 不可变数据类型
不可变数据类型在传递的时候，以传值来进行传递，会创造一个新的内存赋新值，不会影响原来的数据。   
#### str 字符串
字符串就是作为不可变数据进行传递，每次赋值或者传递都会创造一个新的值，并且也有着不同的内存地址。   
```Python
def test(str1: str):
    str1 = "uvg"


if __name__ == '__main__':
    start = time.time()
    solution = Solution()

    # code area
    str0 = "abc"
    test(str0)
    print(str0)     # abc
    
    str1 = str0
    str1 = "cog"
    print(str0)     # abc

    print(id(str1))  # 2047510550432
    print(id(str0))  # 2047466786976
```
#### 数字
数字无论是整型还是浮点型都是不可变数据，赋值简单，代码略去。   
#### tuple 元组
显然，元组在赋值后，内存地址也变的不同。   
```Python
t1 = (1, 2, 3, ["a", "b", "c"])
t2 = t1
t1 = (0, 0)

print(t1)    # (0, 0)
print(t2)    # (1, 2, 3, ['a', 'b', 'c'])

print(id(t1))    # 1529394303048
print(id(t2))    # 1529394416920
```
### 可变数据类型
可变数据类型在传递的时候，（无论是赋值，还是函数参数的传递）会以引用的方式传递。   
#### list 列表
```Python
def test(list1: list):
    list1.append("end")


if __name__ == '__main__':
    # code area
    list0 = [1, 2, 3]
    test(list0)
    print(list0)    # [1, 2, 3, 'end']

    list1 = list0
    list1.append("another end")
    print(list0)    # [1, 2, 3, 'end', 'another end']   

	print(id(list0))    # 2238654311432
    print(id(list1))    # 2238654311432
```   
可以看到list0，在作为函数传递后，以及赋值后，都作为引用被修改了。并且list0和list1的地址也是相同的。      
#### dict 字典
字典与list一样都是可变数据类型，在赋值或传参的时候以引用传递。   
```Python
d1 = {"name": "cm", "age": "30"}
d2 = d1
d2["name"] = "mc"

print(d1)   # {'name': 'mc', 'age': '30'}
print(d2)   # {'name': 'mc', 'age': '30'}

print(id(d1))   # 1579713318776
print(id(d2))   # 1579713318776
```
### 总结
不可变数据类型的使用其实没什么区别，但是要注意，当使用可变数据类型，并且进行传递和赋值的时候要特别注意，因为很有可能在别处修改了该变量会影响到正在使用的变量。   
如果需要保证得到一个新的变量，那需要用到浅拷贝和深拷贝。  