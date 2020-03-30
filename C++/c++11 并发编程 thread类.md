## c++11 并发编程 thread类
从C++11开始，C++标准库已经支持了线程库了，其实在底层，仍旧使用的是平台相关的线程API。   
有了std::thread之后，我们就不用在不同的平台使用不同的API了，比如Unix平台使用pthread， windows平台使用WinSDK的CreateThread了，接口使用去掉了平台差异性，使得项目开发具有更好的移植性。   
### 所需头文件
```c
#include <thread>   
```   
### 构造函数
1 默认构造函数   
```c
thread() noexceptr   
```   
2 初始化构造函数   
```c  
template<class Fn, class... Args>
explicit thread(Fn&& fn, Args&&... args);   
```   
带模板，支持不同参数，支持多个参数。   
```c
void threadfun1()
{
	cout << "call threadfun1" << endl;
}

void threadfun2(int a, string str)
{
	cout << "call threadfun2, parameters are " << a << " and " << str << endl;
}

int main()
{
	thread t1(threadfun1);
	thread t2(threadfun2, 10, "dk");
	return 0;
}
```   
3 拷贝构造函数   
拷贝构造函数被禁用，thread对象不可拷贝构造。   
4 Move构造函数  
```   
thread(thread&& x)noexcept   
```
调用成功原来x不再是std::thread对象。   
```c
void threadFun(int& a)
{
    cout << "this is thread fun !" << endl;
}

int value = 2;
thread t1(threadFun, std::ref(value));
thread t2(std::move(t1));
t2.join();
```   
### 成员函数
1 get\_id()   
获取线程ID，返回类型std::htread::id对象。   
```c
void threadfun1()
{
	cout << "call threadfun1" << endl;
}

void threadfun2(int a, string str)
{
	cout << "call threadfun2, parameters are " << a << " and " << str << endl;
}

int main()
{
	thread t1(threadfun1);
	thread t2(threadfun2, 10, "dk");
	thread::id id1 = t1.get_id();
	thread::id id2 = t2.get_id();
	cout << "t1线程id " << id1 << endl;
	cout << "t2线程id " << id2 << endl;
	return 0;
}
```   
2 join()  
创建线程执行线程函数，调用该函数会阻塞当前线程，直到线程执行完join才返回。   
```c
void threadfun1()
{
	cout << "call threadfun1" << endl;
}

void threadfun2(int a, string str)
{
	cout << "call threadfun2, parameters are " << a << " and " << str << endl;
}

int main()
{
	thread t1(threadfun1);
	t1.join();
	thread t2(threadfun2, 10, "dk");
	t2.join();
	return 0;
}
```   
如果不带join函数，t1和t2的线程函数仍然会执行。但是他们是同时执行的，也就是我们在输出的时候"call threadfun1"和"call threadfun2, parameters are "很有可能会混在一起。   
即使不输出，我们在具体场景使用的时候，也可能导致冲突。   
而使用了join函数后，直到t1结束调用后，t2才会继续调用。   
3 detach()   
detach调用之后，目标线程就成为了守护线程，驻留后台运行，与之关联的std::thread对象失去对目标线程的关联，无法再通过std::thread对象取得该线程的控制权。    
4 swap()   
交换2个线程对象。  
```c
thread t1(threadFun1);  
thread t2(threadFun2);
cout << "线程1的ID：" << t1.get_id() << endl;
cout << "线程2的ID：" << t2.get_id() << endl;

t1.swap(t2);

cout << "线程1的ID：" << t1.get_id() << endl;
cout << "线程2的ID：" << t2.get_id() << endl;
```   
### 使用类的成员函数作为线程函数
使用类的成员函数作为线程函数时，与普通的构造有些不同。   
第一个参数传函数地址，第二个参数传类的对象，第三个参数才开始传参数。   
```c
class Solution 
{
public:
	void fun(string info)
	{
		cout << info << endl;
	}
};

int main()
{
	Solution solution;
	thread t1(&Solution::fun, &solution,  "call fun");
	return 0;
}
```   
### 进程的启动
在初始化thread对象后，应该第一时间考虑，是join还是detach。   
因为如果不做这个操作，有可能发生，thread对象先一步生命周期结束，而线程函数可能会访问已经释放的内存空间，引起错误。   
### 进程的结束   
当thread对象消亡时，如果thread是joinable的（associated应该翻译为可关联的，也就是joinable的），析构函数会调用terminate()，terminate()会调用abort(), abort()是非正常结束进程，不进行任何清理工作，直接终止程序，其典型实现是输出标准错误流(即cerr使用的错误流)。    
如果thread被调用过join()或者detach()，那它就不是joinable的，所以不会引发terminate，进程正常终止，并且会进行正常的回收资源。  