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
insert函数，可以添加单个、多个元素。   
```c
std::set<int> s;	//空值初始化   
std::set<int>::iterator itr;   
std::pair<std::set<int>::iterator, bool> pair_itr;   
pair_itr = s.insert(10);	//这个insert的重载版本会返回一个pair，first是set的迭代器，总是指向新加入的元素，或者是已经存在的相等的元素。而second则是加入失败还是成功。   
if (pair_itr.second == true)   
cout << "insert successfully" << endl;    
itr = pair_itr.first;	//无论是否添加成功，first总是指向该元素。    

//insert的另一种重载，拥有另一个参数position。   
//如果插入的元素紧挨着position指向的元素，那么效率会被优化到最大，并且会返回一个指向插入元素的迭代器（亦或者已经存在的相等的元素的迭代器）   
itr = s.insert(itr, 100);	//与10之间没有其它元素，最高效率   
itr = s.insert(itr, 101);	//与100之间没有其他元素，最高效率   
itr = s.insert(itr, 99);	//与101之间隔着一个100，并非最高效率   

int arr[] = { 1,2,3,4,5 };   
s.insert(arr, arr + 5);	//插入数组，没有返回值    
```  
emplace函数的用法相对简单。   
```c
std::set<int> s;	//空值初始化   
std::set<int>::iterator itr;   
std::pair<std::set<int>::iterator, bool> pair_itr;   
pair_itr = s.emplace(10);	//与Insert相似，返回pair，键对应插入元素的迭代器，值队应成功与否的布尔值   

itr = pair_itr.first;   
itr = s.emplace_hint(itr, 12);	//与insert类似，不过他没有做成重载函数。   
```   
### 删除元素
```c
auto ret_itr= s.erase(itr);	//根据itr指向的位置删除元素，返回后面的第一个元素    

int amount= s.erase(1);	//根据值来删除，返回删除的值的数量。本来就只能删除一个值，一开始不知道这个有什么用，但是考虑到有可能删除失败会返回0，大概就是这个用处。   

auto itr= s.erase(s.begin(), s.end());	//根据range来删除元素，返回删除后的第一个元素。这里全删完了，返回的便是s.end()了     
```   
以及几乎所有标准库模板都会有的clear函数，全部清空。   
### 功能函数
以下是set的常用功能函数：   
set<int> s;   
int i= s.count(val);	//统计val的数量，一般只有0或者1   
bool b= s.empty();	//set是否为空  
pair<set<int>::const_iterator, set<int>::const_iterator> ret= s.equal_range(val);	//返回寻找的这个值的区间。由于set中值是唯一的，所以只会返回包含一个元素的区间。其中first指向该元素本身，而second指向该元素后一个元素     
auto it= s.find(val);	//返回寻找的val元素的迭代器   
auto it= s.lower_bound(val);	//返回指向val的迭代器   
auto it= s.upper_bound(val);	//返回指向val下一个元素的迭代器   
int i= s.max_size();	//返回当前环境能存储的最大元素数量   
int i= s.size();	//返回当前set中的元素数量   

set<int> first{1,2,3,4};   
set<int> second{1,2,3};	
first.swap(second);	//交换两个set的值   
### 遍历及迭代器
迭代器是一种检查容器内元素并遍历元素的数据类型。C++更趋向于使用迭代器而不是下标操作，因为标准库为每一种标准容器定义了一种迭代器类型。   
**获取迭代器的函数**   
```c
set<int> s;  
set<int>::iterator itrBegin= s.begin();  //获取第一个元素的迭代器   
set<int>::iterator itrEnd= s.end();   //获取最后一个元素再后一个的迭代器   
set<int>::const_iterator itrCBegin= s.cbegin();  //获取begin的const属性的迭代器   
set<int>::const_iterator itrCEnd= s.cend();   //获取end的const属性的迭代器   
set<int>::reverse_iterator itrRBegin= s.rbegin();	//获取反向begin迭代器   
set<int>::reverse_iterator itrREnd= s.rend();	//获取反向end迭代器    
```   
**使用迭代器进行遍历**   
```c
vector<int> vec;   
for (int i = 0; i < 5; i++)  
	vec.push_back(i);	 	 	
	
vector<int>::iterator itr;   
for (itr = vec.begin(); itr != vec.end(); itr++)  
	cout << *itr << " ";   
```  
需要注意的是，不要对vec.end()进行解引用操作，因为它已经在容器之外了，解引用将会是未定义的操作。  