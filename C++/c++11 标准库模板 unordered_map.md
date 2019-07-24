### 标准库模板 unordered_map
在C++11中有新出4个关联式容器：unordered\_map/unordered\_set/unordered\_multimap/unordered\_multiset。   
这4个关联式容器与map/multimap/set/multiset功能基本类似，最主要就是底层结构不同，使用场景不容。   
如果需要得到一个**有序**序列，使用红黑树系列的关联式容器，如果需要**更高的查询效率**，使用以哈希表为底层的关联式容器。     
### 头文件支持
```c
#include <unordered_map>   
```   
### 初始化
作为标准库模板，它的初始化方式与其它的模板类似。   
```c
unordered_map<string, string> umap1;	//缺省初始化    
umap1["one"] = "oneone";  
umap1["two"] = "twotwo";    
unordered_map<string, string> umap2(umap1.begin(), umap1.end());	//区间初始化[)   
unordered_map<string, string> umap3(umap2);	//copy初始化   
unordered_map<string, string> umap4(unordered_map<string, string>{pair<string, string>{"three", "threethree"}});	//（右值）移动构造初始化 move   
unordered_map<string, string> umap5{ pair<string,string>{"four","fourfour"}, pair<string,string>{"five","fivefive"} };	//初始化列表初始化   
```  
### 添加元素
### 删除元素
### 调整空间
### 功能函数
### 迭代器的使用及遍历
### 总结