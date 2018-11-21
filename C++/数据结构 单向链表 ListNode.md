## 单向链表 ListNode
这不是STL标准库的链表，只是一个很简单的单向链表，以指针为主要表达形式保存int类型。（当然也可以使用模板保存其它类型）   
由于每保存一个元素，就要使用对应的一个指针，因此在空间占用上要高于其它的容器。不过他的好处在于，可以快速的在任何地方插入元素，毕竟他不需要像vector一样，改变大部分内存，而只要改变指针的指向就可以了。     
### 基本语法
```c
struct ListNode   
{  
    int val;  //当前节点的数字
    ListNode *next;   //指向下一个节点，如果为NULL则说明这是最后一个节点了。  
    ListNode(int x) : val(x), next(NULL) {}   
};   
```  
以上就是单向链表的基础原型，包括一个值，一个指向下一个链表节点的指针以及一个构造函数。单项链表实际上就是通过指针连接起来的。   
ListNode节点本身是一个指针，其中包含值以及指向下一个节点的指针（当然还包括构造函数）。   
如果链表只有一个元素，不要忘记将他的next指针指向NULL。即使链表有多个元素，也要记得将最后一个元素的指针指向NULL。   
### 初始化单向链表
首先看一下单向链表的初始化。   
```c
//1 直接进行赋值，只有一个元素的话，作为末尾元素next手动指向NULL   
ListNode* list1 = new ListNode(5);  
list1->next = NULL;  

//2 后赋值。   
ListNode* list2 = new ListNode(0);   
list2->val = 5;  
list2->next = NULL;  

//3 初始化多个值   
ListNode* list3 = NULL;;  
ListNode* curList;   
for (int i = 0; i < 5; i++)  
{   
	ListNode* templist = new ListNode(i);  
	templist->next = NULL;	//由于是新节点，那么它的next将总是NULL。     
	if (list3 == NULL)		//如果是第一个节点，则保存该节点，并保存当前节点     
	{   
		list3 = templist;  
		curList = templist;  
	}  
	else   //如果不是第一个节点，那么将上一个节点（即curList）的next指向这个临时新节点后，再将临时新节点赋值给当前节点。    
	{  
		curList->next = templist;  
		curList = templist;  
	}  
}    

//比较朴素的（难看的）初始化多个元素。不断通过第一个节点的next的next添加元素，记得给最后一个next赋值为NULL。    
ListNode* list4 = new ListNode(5);  
list4->next = new ListNode(10);  
list4->next->next = new ListNode(15);  
list4->next->next->next = new ListNode(100); 
list4->next->next->next->next = NULL;      
```  
以上为4种常用的初始化链表的方式。   
### 添加节点  
单向链表添加节点（元素）的行为比较容易理解，分为以下几步：  
1 把前一个节点的next指向自己。  
2 把自己的next指向后一个元素。  
这样就将自己融入其中，完美的连接了起来。   
```c
ListNode* list = new ListNode(0);  
list->next = new ListNode(10);  
list->next->next = NULL;   

//原始的链表为0->10，我们将在其中安插一个5。     
ListNode* newlist = new ListNode(5);     
newlist->next = list->next;	//先将前一个节点的next赋值给新节点，不然一会儿就被覆盖了。       
list->next = newlist;	//然后将前一个节点的next指向自己。    
```  
### 删除节点   
由于单向链表的节点通过new来像堆区申请内存，因此当我们不需要该节点的时候，需要进行手动释放。尽管程序结束后系统会自动回收内存，在程序结束前，未释放且不需要的节点可能会占用大量的内存。   
当然，这很简单，通过我们与new配套的delete即可。   
```c
void deletelist(ListNode* list)  
{  
	while (list != NULL)  
	{  
		ListNode* next = list->next;  //先保存好下一个节点的指针，不然一会儿释放掉当前指针了，就再也找不到后面的节点了。  
		delete list;  
		list = next;  
	}  
}   
```
### 链表的倒转
```c
ListNode* reverse(ListNode* list)  
{   
	//倒转链表的话需要注意，最后一个元素的next指向的是NULL，由于我们以顺序倒转，因此先倒转第一个元素，它将变成新链表的最后一个元素，需要将其newxt指针指向NULL。   
	ListNode* pre = NULL;	//为当前第一个元素/新链表的最后一个元素的next指针做准备   
	while (list != NULL)  
	{   
		ListNode* temp = list->next;	//临时保存下个元素的指针，它将会被覆盖。  
		list->next = pre;	//把当前指针的next指针变成pre，如果是首次循环，当前指针在反转后则作为新链表的最后一个元素，它的next指针应该指向NULL。    
		pre = list;	//将当前的指针变成pre，来给下一个元素的next指针赋值。下一个元素应该在新链表中应该作为前一个元素，并且next指针指向现在的这个元素。  
		list = temp;	//以上操作完成后，将之前临时保存的下个元素的指针赋值给当前元素，继续循环操作下个元素。    
	}  
	return prev;	//注意，最后list已经为NULL，所以它的前一个元素就是当前链表的第一个元素。     
}  
```  
链表的倒转主要是通过将每个节点的next指针反向指向前一个指针完成的，需要注意的是当前的第一个节点将变成最后的节点，它的next需要手动指向NULL。   
### 链表的逆向输出
通常情况下，我们将链表倒转以后就可以逆向输出了。但是某些时候我们并不能改变链表的结构，这时候该怎么办呢？   
方法一：通过标准库模板stack，遍历链表将链表节点依次压入stack中，然后通过stack后进先出的规则，依次输出链表就能达到逆向输出的目的。   
```c
void reverseprint(ListNode* head)  
{  
	stack<ListNode*> st;  
	while (head)  
	{  
		st.push(head);  
		head = head->next;   
	}  

	while (!st.empty())  
	{   
		cout << st.top()->value;  
		st.pop();   
	}  
}   
```
方法二：通过递归，递归的思想与stack是相似的。      
```c
void reverseprint(ListNode* head)  
{   
	if (!head)  
		return;  
    
	if (head->next) 
	{   
		reverseprint(head->next);   
	}   
	cout << head->value << endl;  
}   
```   
方法二只是个开阔思路的方式，实际上经测试，通过stack的效率比通过递归的效率高不少。毕竟递归效率不太行。   
### 删除单个节点   
由于单向链表不支持随机访问，因此我们通常是通过从头节点往后遍历，找到需要删除的节点，然后删除它并且把前一个节点的next指针指向后一个节点。   
需要注意的有四种情况：  
1 头节点与待删除节点相等，并且一共只有一个节点。这种情况下需要删除节点并且给头节点置为NULL。   
2 头节点与待删除节点相等，并且之后还有节点。这种情况需要删除节点并且将头节点指向下一个节点。   
3 删除的节点在末尾，那么删除后前一个节点就是尾节点了，next指向NULL。   
4 删除的节点在当中，删除后将前一个节点的next指向后一个节点使其再串联起来。   
```c
void DeleteNode(ListNode** head, ListNode* tobedel)  
{  
	if (!head || !tobedel||!(*head))   
		throw exception("point is empty");  
	
	if (*head == tobedel)  
	{    
		if (!tobedel->next)	//头节点与待删除节点相等且后续没有节点了  
		{   
			delete tobedel;  
			*head = NULL;    
		}   
		else  //头节点与待删除节点相等且后续还有节点    
		{   
			ListNode* newhead = tobedel->next;  
			*head = newhead;  
			delete tobedel;   
		}   	
		tobedel= NULL;   
	}    
	else   //头节点不与待删除节点相等  
	{   
		while (*head)  
		{   
			if ((*head)->next == tobedel)   
			{    
				(*head)->next = tobedel->next;   
				delete tobedel;   
				tobedel = NULL;  
				break;     
			}   
			*head = (*head)->next;    
		}   
	}  
}   
```   
以上删除方式的效率是O(n)。  
还有一个删除效率为O(1)的骚操作。   
大致思路是这样的：不要用遍历，直接将待删除节点的下个节点的内容拷贝给待删除节点，然后删除下个节点，这样就能达成O(1)的效率了。   
需要注意的是，如果头节点等于待删除节点以及头节点等于待删除节点并且只有一个节点，按之前的方法操作也是O(1)。   
另外如果待删除节点在最后则只能通过遍历来操作。   
尽管如此，平均效率仍然是O(1)。   
```c
void DeleteNode(ListNode** head, ListNode* tobedel)  
{   
	if (!head || !tobedel||!(*head))  
		throw exception("empty point");   

	if (*head == tobedel)  
	{   
		if (!tobedel->next)	//头节点与待删除节点相等且后续没有节点了  
			*head = NULL;   
		else    //头节点与待删除节点相等且后续还有节点   
			*head = tobedel->next;  

		delete tobedel;  
		tobedel = NULL;  
	}   
	else if(!tobedel->next)	//如果是最后一个节点就没法用骚操作，要用正常的方式  
	{   
		while (!(*head))  
		{  
			if ((*head)->next == tobedel)  
			{  
				(*head)->next = NULL;   
				delete tobedel;  
				tobedel = NULL;  
				return;  
			}  
			*head = (*head)->next;   
		}  
		throw exception("tobedel point is not in the ListNode");  
	}   
	else  //节点在最后，这个骚操作只要O(1)的效率   
	{  
		ListNode* realtobedel = tobedel->next;  
		tobedel->val = realtobedel->val;  
		tobedel->next = realtobedel->next;   
		delete realtobedel;  
		realtobedel = NULL;   
	}   
}   
```   
这个方法有一个地方需要额外注意的是，如果待删除节点不是这个链表里的节点，它就并不能发现。而如果要验证是否是链表里的节点，则需要进行遍历来进行对比，那么效率仍然是O(n)的。   
所以这个追求效率的方法，必须在输入的时候保证该节点是链表内的节点才行。   
### 总结 
链表看上去复杂，实际上是对指针的操作，通过指针指向指针来建立的连续（sequence）的容器。   
增删查以及更多的功能基本上都可以通过从头到尾指针的顺序遍历来完成的，对此不再赘述。只是需要额外在意的是，无论增加还是减少都要通过next指针将前后连接起来，以及最后的next指针始终是NULL。       