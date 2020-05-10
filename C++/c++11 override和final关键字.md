## override和final关键字
override和final关键字是c++11新出的特性，针对于虚函数方面的一种声明。  
在以前，通常情况下，基类的虚函数需要加上virtual，子类重写的虚函数对于virtual关键字可写可不写，由编译器自己来判定。   
但是编写代码的时候，对于一些庞大的项目，对于程序员来说，很难判断，一个虚函数是否重写基类的，是否被子类重写。   
```c
class father
{
public:
	virtual void test(int a)
	{
		cout << "father test" << endl;
	}
};

class son: public father
{
public:
	virtual void test(int a)
	{
		cout << "son test" << endl;
	}
};
```  
比如以上函数，如果在大型项目中，当我们第一眼看到father的test时，并不知道它时作为基类的虚函数，还是子类的虚函数。   
也不知道它有没有被继承，或者有没有重写其他虚函数。  
### override关键字
override关键字显式的表示，这个虚函数，将会重写基类的虚函数。  
```c 
class father
{
public:
	virtual void test(int a)
	{
		cout << "father test" << endl;
	}
};

class son: public father
{
public:
	virtual void test(int a) override
	{
		cout << "son test" << endl;
	}

	virtual void test1(int a) override
	{
		cout << "son test" << endl;
	}
};
```  
如上面的代码，son的test能正常经过编译。   
但是test1则会发生编译错误，因为它显式的表示自己会重写基类的虚函数，但是基类却没有它可以重写的虚函数。  
### final关键字
final关键字显式的表示，这个虚函数将不能再被子类的任何虚函数重写。  
```c
class father
{
public:
	virtual void test(int a)
	{
		cout << "father test" << endl;
	}
};

class son: public father
{
public:
	virtual void test(int a) override final
	{
		cout << "son test" << endl;
	}
};

class sonson : public son
{
public:
	virtual void test(int a)
	{
		cout << "sonson test" << endl;
	}
};
```
如以上代码，在son的test后加了override，显式表明它将会重写父类的虚函数。  
同时，final关键字，表示此虚方法已经是最终实现, 任何派生类中重载这个方法的企图都将引发一个编译错误。   
所以，sonson中的test将会编译失败，因为它不能重写基类的虚函数。   
#### 注意
在不加入各种关键字的情况下，如果子类和父类有2个同名的函数。编译器会认为这两个函数仅仅是同名函数，并不是重写的关系，并且子类会覆盖父类的同名函数。是可以正常通过编译的。   
但是在基类中同名函数加入了final的情况下，编译器就不会这么认为了。它会严格的把子类中的同名函数，当作尝试重写父类虚函数的这么个动作，并且给出编译错误。  
这点是需要注意的。  