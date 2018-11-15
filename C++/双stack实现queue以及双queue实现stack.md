# 双stack实现queue以及双queue实现stack
书上看到一道题，双stack实现queue以及双queue实现stack。觉得比较有趣记录下来。   
stack，栈的特性是后进先出，即后压入的元素将会先弹出。而queue，队列的特性是先进先出，先压入的元素将会先弹出。   
如何通过两个相同的stack和queue转换其特性呢？   
## 双stack实现queue
需要实现的函数有两个，一个就是将元素压入头部，另外一个就是从头部弹出元素，即queue原有的push和pop函数。   
### 解题思路
既然有两个stack，意味着我们可以将元素在他们之间倒来倒去。什么时候倒？   
显然，当我们只是单纯压入元素的时候，顺序是没有问题的，因此压入元素的时候正常压入其中的一个stack，即stack1就行。   
当我们需要弹出头部的元素，由于stack只能弹出尾部的元素，因此我们将stack1的元素从尾部以后进先出的顺序逐个弹出然后压入stack2中。这时候在stack2中元素的顺序是反的，但是因此我们弹出stack2的元素的时候，由于负负得正，stack2弹出的元素恰恰是我们需要弹出的元素，也就是我们最先压入这个模拟queue的元素。   
至此我们可以进行归纳，stack1负责压入元素，有任何元素则压入stack1，它的压入顺序是对的，只是弹出顺序不对。   
因此当我们需要弹出元素的时候，将stack1以栈的后进先出的顺序压入stack2中，在stack2中由于元素顺序为反，则弹出的顺序反而是正确的。   
值得一提的是，当再次压入元素的时候，我们不需要将stack2中的元素重新装回stack1。由于我们并不需要实现其他功能，仅仅是压入与弹出，因此stack2中的元素慢慢等待弹出即可。当stack2的元素用完，再将stack1的元素压入stack2就可以了。    
### 代码
```c
template<typename T> class CQueue  
{   
public:     
	CQueue() {};  
	~CQueue() {};   
	void appendTail(const T& node);  
	T deleteHead();  
private:  
	stack<T> stack1; //负责压入元素   
	stack<T> stack2; //负责弹出元素   
};  

template<typename T> void CQueue<T>::appendTail(const T& node)  
{   
	stack1.push(node);    
}  

template<typename T> T CQueue<T>::deleteHead()  
{   
	if (stack2.empty() && stack1.empty())     
		throw exception("CQueue is empty");    
	else if (stack2.empty())   
	{  
		while (!stack1.empty())   
		{   
			stack2.push(stack1.top());  
			stack1.pop();  
		}  
	}   
	T head = stack2.top();  
	stack2.pop();   
	return head;   
}  
```
## 双queue实现stack
需要实现的仍然是两个函数，一个stack的压入，一个是stack的弹出，后进先出的弹出。   
### 解题思路
由于queue都是先进先出的，因此当压入的时候我们正常压入元素。   
当弹出的时候如何实现后进先出呢？   
获取queue1的元素数量，然后依次将queue1元素压入queue2，直到最后一个元素，将其删除。下次则是将queue2往queue1压入。以此类推。   
### 代码
```c
template<typename T> class CStack  
{   
public:  
	CStack() {};   
	~CStack() {};  
	void appendTail(const T& node);   
	T deleteHead();  
private:   
	queue<T> queue1;  
	queue<T> queue2;   
};   

template<typename T> void CStack<T>::appendTail(const T& node)  
{   
	if (queue1.empty())  
		queue2.push(node);  
	else if (queue2.empty())  
		queue1.push(node);  
}   
 
template<typename T> T CStack<T>::deleteHead()   
{  
	if (queue1.empty() && queue2.empty())   
		throw exception("CStack is empty");   
	//判断哪个queue是空的哪个是有元素的，将有元素的压到空的里面去并弹出最后一个元素。   
	if (!queue1.empty())  
	{   
		int size = queue1.size();  
		if (size == 1)  
		{  
			T head = queue1.back();   
			queue1.pop();  
			return head;  
		}   
		for (int i = 0; i < size - 1; i++)   
		{   
			queue2.push(queue1.front());  
			queue1.pop();   
		}  
		T head = queue1.front();   
		queue1.pop();  
		return head;   
	}   
	else /*if (!queue2.empty())*/   
	{  
		int size = queue2.size();    
		if (size == 1)   
		{   
			T head = queue2.back();  
			queue2.pop();   
			return head;  
		}   
		for (int i = 0; i < size - 1; i++)   
		{   
			queue1.push(queue2.front());   
			queue2.pop();  
		}   
		T head = queue2.front();   
		queue2.pop();   
		return head;   
	}   
}   
```  
### 相关信息
关于stack可以参考同目录下《标准模板库 stack》   
关于queue可以参考同目录下《标准模板库 queue》   