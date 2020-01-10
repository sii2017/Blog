## @property装饰器
python内置的@property装饰器可以**把类的方法伪装成属性调用的方式**。即将原来Foo.func()的调用方法，变成Foo.func的方式。   
目前属性调用分为三种，分为是getter，setter和deleter。   
### 装饰器的初始化
假设我们有这么一个类，包含两个私有的成员变量。   
```Python
class People(object):   
    def __init__(self):   
        self.__name = "default"  
        self.__id = 0  

if __name__ == '__main__':
	pp = People()
	print(pp.name, pp.id)	//error   
	print(pp.__name, pp.__id)	//error
```   
由于私有特性，所以是不能外部访问这些成员的。   
但是如果完全不能访问，我们无法从外部来获取这些成员的属性和状态。   
我们在c++中会封装一个公有函数来处理这些私有的成员函数。   
python中的处理方法其实也是类似，但是能更进一步优化方法，使该方法伪装成属性调用的方式。   
```Python
class People(object):
    def __init__(self):
        self.__name = "default"
        self.__id = 0

    @property
    def name(self):
        return self.__name

if __name__ == '__main__':
	pp = People()
	print(pp.name)  
```    
实际上，下面的三个器都依赖于装饰器，也就是说，如果你要使用getter，setter，deleter都需要有@property装饰器进行开始，或者说进行声明。   
同时，@property具有getter访问器的作用，当使用了@property装饰器后，getter访问器实际上就不需要了。   
### getter访问器
如上面所说，@property装饰器和getter访问器的作用其实是相同的。但是用法还是说一下。   
```Python
class People(object):
    def __init__(self):
        self.__name = "default"
        self.__id = 0

    @property
    def name(self):
        return self.__name
    
    @name.getter
    def name(self):
        return "abc"

if __name__ == '__main__':
	pp = People()
	print(pp.name)  	//abc
	pp.name = 'aaa' 	//error，仅有只读属性   
```   
可以看到实际上，再调用getter的话会覆盖之前的@property的内容。   
目前还想不到为什么property与getter作用相同，以后知道了来补全。   
值得注意的是，访问器仅给外部调用提供该成员的只读属性，并不能进行修改和删除。   
### setter修改器
setter修改器用来给私有成员赋值，通过方法，通过修改器的伪装，就觉得好像真的是直接给私有成员赋值了一样，但是实际上并不是这样的。    
```Python
class People(object):
    def __init__(self):
        self.__name = "default"
        self.__id = 0

    @property
    def name(self):
        return self.__name

    @name.setter
    def name(self, value):
        self.__name = value

if __name__ == '__main__':
	pp = People()
	pp.name = 'abc'   
```
当我们设置了修改器，我们对该成员可以进行修改了。  
### deleter删除器
实际上我们可以通过修改器就删除成员变量的值，删除器应该是用来防止耦合的吧。   
看一下删除器的调用方式。   
```Python   
class People(object):
    def __init__(self):
        self.__name = "default"
        self.__id = 0

    @property
    def name(self):
        return self.__name

    @name.setter
    def name(self, value):
        self.__name = value

    @name.deleter
    def name(self):
        self.__name = ''
        print("删除数据")

if __name__ == '__main__':
    pp = People()
	del pp.name   	//删除
```   
值得注意的是，删除器的使用，是通过del来实现的。    
并不像访问和修改，只要放在等号两边就行。   
### property函数
除了使用装饰器的方式将一个方法伪装成属性外，Python内置的builtins模块中的property()函数，为我们提供了第二种设置类属性的手段。   
```Python
class People(object):   
    def __init__(self):   
        self.__name = "default"   
        self.id = 0   

    def get_name(self):  
        return self.__name  

    def set_name(self, value):   
        self.__name = value  

    def del_name(self):   
        self.__name = ""   
        print('delete data')   

    name = property(get_name, set_name, del_name, "name")    
```   
上面代码中，最后一行代码很关键。他将三个函数名分别加入自己前三个参数中，并且赋值给name这个对象。   
那当我们在调用name的时候就会自动的映射到这三个函数了。    
```Python   
if __name__ == '__main__':  
    pp = People()   
    print(pp.name, pp.id)   # get_name   
    pp.name = "cba" # set_name   
    del pp.name # del_name  
    print(pp.name, pp.id)  
```  
第四个参数据说是对该装饰器的描述，怎么用目前不知。   