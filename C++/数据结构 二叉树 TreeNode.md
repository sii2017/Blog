## 二叉树 TreeNode
二叉树是每个结点最多有两个子树的树结构。  
与链表不同，链表每个节点对应下一个节点，结构图为一条线。而二叉树的每个节点分裂对应两个节点，从上往下，越分裂越多。    
![](https://github.com/sii2017/image/blob/master/%E4%BA%8C%E5%8F%89%E6%A0%91.jpg)
### TreeNode结构   
```c
struct TreeNode  
{  
	int val;   //值   
	TreeNode* left;	//指向左子树   
	TreeNode* right;	//指向右子树   
	TreeNode(int x): val(x), left(NULL), right(NULL) {}   //构造函数   
}   
```   
根据结构可以看出，TreeNode包含值，以及两个指向子树的指针，与链表相似但不同。  
### 初始化  
```c
TreeNode* pTree= new TreeNode(0);	
```   
调用构造函数进行初始化，这个指针我们在整个代码中称为根节点。之后我们的操作都要围绕这个根节点展开，与链表的头节点相似。  
主要不要在操作过程中覆盖掉这个根节点。   
### 二叉树的创建  
二叉树的元素存放是存在一定规律的。比如平衡二叉树必须左子树的值小于右子树的值，而赫尔曼二叉树最需要左大右小。  
不过一般的树的设计规则可以由我们来定，以下提供一种根据实时输入来创建二叉树的代码。  
```c
#include <iostream>  
using namespace std;  

struct TreeNode   
{  
	char c;  
	TreeNode* left, *right;   
	TreeNode(char p):c(p), left(NULL), right(NULL){}   
};  

TreeNode* create(TreeNode* root)  
{  
	char c;   
	cin >> c;  
	
	if (c == '#')   
	{   
		root = NULL;   
		return root;   
	}   
	else   
	{   
		root = new TreeNode(c);   
		root->left= create(root->left);   
		root->right= create(root->right);   
	}  
	return root;   
}   

int main()   
{  
	TreeNode* root= NULL;  
	root=create(root);  
	getchar();   
	return 0;  
}  
```  
当然了，如果每次创建二叉树都输入，显得十分不方便。再提供一种根据字符串来创建二叉树的方式。以D为根，从左到右为ABCDEFGH。   
```c
#include <iostream>  
#include <string>  
using namespace std;   

string passcode = "DBA##C##FE##G#H##";  
int num = 0;   
struct TreeNode  
{   
	char c;  
	TreeNode* left, *right;    
	TreeNode(char p):c(p), left(NULL), right(NULL){}  
};   

TreeNode* CreateTreeByCode(TreeNode* root)   
{  
	char c;   
	if (num < passcode.size())  
		c = passcode[num++];    
	else   
		return root;    

	if (c == '#')  
	{   
		root = NULL;   
		return root;   
	}  
	else   
	{   
		root = new TreeNode(c);   
		root->left = CreateTreeByCode(root->left);   
		root->right = CreateTreeByCode(root->right);   
	}   
	return root;  
}   

int main()   
{   
	TreeNode* root= NULL;  
	root= CreateTreeByCode(root);   
	getchar();  
	return 0;   
}   
```   
### 插入与删除元素  
二叉树与链表相似，无法使用下标访问，需要通过指针结构一个一个遍历。因此二叉树的插入与删除元素需要建立在遍历上，当我们遍历到相关的位置后，就可以进行插入与删除工作了。以下看一看二叉树的四种遍历。  
### 前序遍历
前序遍历首先访问根结点然后遍历左子树，最后遍历右子树。在遍历左、右子树时，仍然先访问根结点，然后遍历左子树，最后遍历右子树。  
因此输出为：DBACFEGH。  
```c
//通过递归的前序遍历   
void PreOrder(TreeNode* root)    
{  
	if (root != NULL)  
	{   
		cout << root->c;  
		PreOrder(root->left);  
		PreOrder(root->right);   
	}   
}    

//非递归的前序遍历  
void PreOrderByCircle(TreeNode* root)   
{   
	stack<TreeNode*> st;  
	TreeNode* p = root;  

	while (p || !st.empty())  
	{  
		if (p)  
		{  
			cout << p->c;   
			st.push(p);  
			p = p->left;  
		}   
		else   
		{  
			p = st.top()->right;  
			st.pop();  
		}  
	}  
}  
```
### 中序遍历  
中序遍历首先遍历左子树，然后访问根结点，最后遍历右子树。   
因此输出为：ABCDEFGH。   
```c
//递归，中序遍历   
void InOrder(TreeNode* root)  
{  
	if (root != NULL)  
	{  
		InOrder(root->left);   
		cout << root->c;   
		InOrder(root->right);   
	}  
}   

//非递归，中序遍历   
void InOrderByCircle(TreeNode* root)  
{  
	TreeNode* p;  
	p = root;  
	stack<TreeNode*> st;  

	while (p || !st.empty())   
	{   
		if (p)  
		{  
			st.push(p);  
			p = p->left;   
		}  
		else   
		{  
			cout << st.top()->c;   
			p = st.top()->right;  
			st.pop();  
		}  
	}  
}  
```  
### 后序遍历
后序遍历是先遍历左子树，再遍历右子树，最后访问根节点。  
```c
//递归，后序遍历  
void PostOrder(TreeNode* root)    
{   
	if (root->left)  
		PostOrder(root->left);  
	if (root->right)   
		PostOrder(root->right);  
	cout << root->c;  
}  
```   
非递归的后序遍历可行，不过比较麻烦，需要在TreeNode结构中增加一个bool值，表示该节点是否被访问过。  
### 层序遍历
层序遍历按顺序遍历每一层，同时每一层的遍历顺序从左到右。  
层序遍历需要借助标准库容器模板的queue。   
```c
void LevelOrder(TreeNode* root)  
{  
	if (!root)  
		return;  
  
	queue<TreeNode*> qt;  
	qt.push(root);  
	while (!qt.empty())  
	{  
		if (qt.front() == NULL)  
		{  
			qt.pop();  
			continue;  
		}   
		cout << qt.front()->c << endl;   
		qt.push(qt.front()->left);   
		qt.push(qt.front()->right);   
		qt.pop();  
	}    
}    
```  
借助queue先进先出的特性，依次按顺序压入TreeNode的节点，当轮到这个节点了那么就输出并且按顺序压入它的两个子节点。整个遍历是相当有序的。   
### 总结
以上所述的二叉树只是最基础的二叉树。  
随着功能的需求，二叉树衍生出许多功能二叉树，并对应着不同的特性，之后会讲到。  