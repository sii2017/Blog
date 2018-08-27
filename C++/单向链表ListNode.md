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
### 添加元素  
单向链表添加元素（节点）的行为比较容易理解，分为以下几步：  
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
