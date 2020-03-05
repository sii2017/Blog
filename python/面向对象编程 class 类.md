## 面向对象编程
python也支持面向对象编程，与c++类似，也使用类。   
本篇记录一下如果使用python来进行面向对象编程。   
### class
与c++类似，python也是使用class关键字的。   
同时结合python的规则，没有大括号，而是通过缩进来确定包含关系。   
因此，如下：   
```
class People:  
	def __init__(self):  
		# code      
```     
以上就是一个People类，并且有一个构造函数。   
### 构造函数  
说到构造函数，python的构造函数并不是像c++一样，以与类名相同的函数名进行设定的，而是有一个固定的形式。  
```
def __init__(self):   
```   
\_\_init\_\_是一个特殊方法用于在创建对象时进行初始化操作。   
self是必须的，代表着类本身，并且在每个函数里都要显式的表达出来。   
与c++的this是相似的，但是c++的this是隐藏的。   
如果说，有多个成员变量需要初始化，则如下操作：   
```
def __init__(self, name, age):   
	self.name= name
	self.age= age   
```   
成员变量都要以self.进行开头。   

### 类对象的声明
在传统的c++中，定义类对象有多种方法比如：   
```c
People pp();   
```   
但是以上语法在python中是不成立的。python需要如此：   
```Python
pp = People()    
```   
这是需要注意的。   
### 访问可见性问题
在c++中，所有成员都有公有、私有、保护三种访问特性。  
在python中，只要公有和私有两种访问特性。   
如果希望成员变量或者函数为私有的，那么可以在名称前加两个下划线，编译器会理解为，对该成员设置私有的访问特性。   
```Python   
class People(object):  
    def __init__(self):  
        self.__name = "default"  
        self.__id = 0  

    def __print_message(self):  
        print(self.__name, self.__id)  


if __name__ == '__main__':  
    pp = People()  
    pp.print_message()   //AttributeError: 'People' object has no attribute 'print_message'   
```  
### 强行访问私有成员
但是，Python并没有从语法上严格保证私有属性或方法的私密性，它只是给私有的属性和方法换了一个名字来妨碍对它们的访问，事实上如果你知道更换名字的规则仍然可以访问到它们，下面的代码就可以验证这一点。之所以这样设定，可以用这样一句名言加以解释，就是"We are all consenting adults here"。因为绝大多数程序员都认为开放比封闭要好，而且程序员要自己为自己的行为负责。    
```Python
pp._People__print_message()   
```   
是的，在私有函数名前加上单下划线和类名。   
### 隐喻意味上的保护成员
在实际开发中，我们并不建议将属性设置为私有的，因为这会导致子类无法访问。    
所以大多数Python程序员会遵循一种命名惯例就是让属性名以单下划线开头来表示属性是受保护的，本类之外的代码在访问这样的属性时应该要保持慎重。   
```Python   
class People(object):
    def __init__(self):
        self._name = "default"
        self._id = 0

    def _print_message(self):
        print(self._name, self._id)
```   
**这种做法并不是语法上的规则，单下划线开头的属性和方法外界仍然是可以访问的，所以更多的时候它是一种暗示或隐喻。**     