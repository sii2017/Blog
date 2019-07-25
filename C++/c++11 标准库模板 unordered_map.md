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
目前主要有以下四种方式，与map相似。   
```c
unordered_map<int, string> umap;   
umap[1] = "one";	//通过[]重载进行赋值   
umap.insert({ 2,"two" });	//通过insert函数进行重载   
umap.emplace(pair<int, string>{3, "three"});	//通过emplace进行重载  
```
### 删除元素
主要通过clear函数进行全部删除，以及通过erase函数删除部分或个别元素。   
```c
//erase函数   
umap.erase(1);	//通过key来删除   
unordered_map<int, string>::iterator itr = umap.begin();   
umap.erase(itr);	//通过迭代器来删除  
umap.erase(umap.begin(), umap.end());	//通过迭代器区间来删除(]   
//clear函数   
umap.clear();	//通过clear全部删除  
```   
### 调整空间
与map相似无法调整空间。  
### 功能函数
unordered\_map的功能函数如下。   
unordered\_map unap;
unap.at(5);	//访问key为5的值，与unap[5]相似。不同的在于前者如果没有找到则返回异常，后者则创建key为5的空置。   
umap.backet(key);	//返回key在哈希表中的位置。  
umap.backet_count();	//返回哈希表的大小。  
umap.backet_size(backet_pos);	//返回在哈希表的某个位置上，存储了几个value   
umap.count(key);  //返回map中有几个相同的key，由于unordered\_map不支持同样的key，因此只会返回1或0   
umap.empty();	//返回该map是否为空   
umap.equal_range(key);	//返回与key相等的区间迭代器，由于unordered\_map中key是唯一的，所以只会返回最多包含一个元素的区间。如果没有找到，则返回起始和结束范围同为end的两个迭代器。   
umap.find(key);	//寻找key并返回迭代器，如果没有找到则返回end   
bool b = umap.key\_eq()(key1, key2);	//返回key1和key2在该map中是否判定为同一个key，比如9和9就是同一个，9和10就不是同一个……      
umap.max\_bucket\_count;	//返回当前环境下支持的最大哈希表   
umap.max_size();	//返回当前环境下该map支持的最大存储数量  
umap.reserve(n);	//使哈希表数设置成最适合保存n个key的数量。   
umap.size();	//返回当前存储的数据数量   
umap1.swap(umap2);	//交换2个unordered\_map   
### 迭代器的使用及遍历
迭代器是一种检查容器内元素并遍历元素的数据类型。C++更趋向于使用迭代器而不是下标操作，因为标准库为每一种标准容器定义了一种迭代器类型。   
```c
unordered_map<int, string>::iterator itrbegin = umap.begin();	//起始迭代器   
unordered_map<int, string>::iterator itrend = umap.end();	//结束迭代器   
unordered_map<int, string>::const_iterator cbeginitr = umap.cbegin();	//常量起始迭代器   
unordered_map<int, string>::const_iterator cenditr = umap.cend();	//常量结束迭代器   

//由于该容器为键值对，因此迭代器并非常用的解引用，而是调用first和second来获取key和value     
for (; itrBegin != m.end(); itrBegin++)    
{     
	cout << itrBegin->first << " " << itrBegin->second;   
}   
```
值得注意的是，unordered\_map并不具有反向迭代器。  
### 总结   
1 与map相似，key与value一一对应。   
2 底层使用了哈希表，具有比map更快的访问速度。  
3 key总是唯一的。   
4 没有排序意味着效率比map更高，当然空间占用上次于map。    