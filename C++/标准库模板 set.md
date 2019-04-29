## 标准库模板 set 集合
与map相似，set也是一种关联性容器。与map不同的是，set的键值相同，键就值，键值不能重复，也不能通过迭代器来改变set的值。   
### 头文件支持
```c  
#include <set>   
```      
### 初始化
虽然底层与map相似都是红黑树，但是由于键值相同，它的初始化方法反而与vector相似。   
```c
td::set<int> s1;	//空值初始化    

int arr[] = { 1,2,3,4,5,6 };   
std::set<int> s2(arr, arr + 6);	//通过数组区间进行初始化    
std::set<int> s3(s2);	//通过其它set初始化   
std::set<int> s4(s3.begin(), s3.end());	//通过其它set的区间进行初始化   

std::set<int, comparefuction> s5();	//初始化的时候加入自定义比较函数   
```   
### 添加元素

### 删除元素