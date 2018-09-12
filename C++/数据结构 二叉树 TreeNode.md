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
### 创建一颗完整的树  
二叉树的元素存放是存在一定规律的。比如平衡二叉树必须左子树的值小于右子树的值，而赫尔曼二叉树最需要左大右小。  
不过一般的树的设计规则可以由我们来定，以下提供一种创建完整树的代码。  
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
### 插入元素  

### 删除元素 
### 前序遍历
### 中序遍历
### 后序遍历
### 层序遍历
### 总结