## 标准库类型vector
标准库类型vector表示对象的集合，其中所有对象的类型都相同。且集合中每隔对象都有一个与之对应的索引用于访问对象。   
因为vector容纳着其它对象，所以它也常被称为“容器”。   
要想使用vector需要包含头文件vector，并且使用std名字空间。   
> vector是模板而非类型，由vector生成的类型必须包含vector中的元素类型，例如vector<int>。   
> 由于vector中存放的是对象，因此它不能存放引用，因为引用并不是对象。    
### 初始化
vector有着多种初始化的方法，以下：  
vector<T> v1;	//v1是一个空的vector，但是只能存放T类型。   
vector<T> v2(v1);	//v2以v1的元素进行了初始化，包含v1元素的副本。    
vector<T> v2=v1;	//将v1赋值给v2。   
vector<T> v3(n, val);	//v3包含了n个重复的val对象。  
vector<T> v4(n);	//v4包含了n个重复并执行了值初始化的对象。   
vector<T> v5{a,b,c...};	//v5以大括号中的值以及顺序进行初始化。   
vector<T> v5={a,b,c...};;	//等价于上面。   
注意：圆括号则是用数量来统一初始化对象，用花括号则是c++11的列表初始化。  
### 添加元素
对于vector对象来说，直接初始化的方式适用于三种情况：  
1 初始值已知且数量比较少。   
2 用另一个vector对象为其初始化。  
3 所有元素的初始值一样且知道确切数量。   
然而更常见的是，我们在创建vector对象的时候并不知道元素数量，值也无法确定。这时候我们就要先创建，后插入了。   
push_back函数负责将一个值压进vector对象的尾端，作为它新的尾元素。   
```c
vector<int> vec1;  
vec1.push_back(10);   

vector<string> vec2;  
vec2.push_back("abc");  

vector<int> vec3;  
for(int i=0; i<10; i++)  
	vec3.push_back(i);   
```    
注意：不能通过下标去给vector添加元素，会造成内存越界。在元素压入前，是不会分配内存的，因此访问不存在的下标，会报错。    
### 删除元素
### 功能函数
以下是一些常用的功能函数：   
vec.empty();	//如果不含任何元素则返回真；反之假。   
vec.size();	//返回元素的个数。   
vec.clear();	//清空vec中的元素。  
vec.front();	//返回vec中第一个元素。   
vec.back();		//返回vec中最后一个元素。   
vec.pop_back();	//弹出（删除）vec中的最后一个元素。   
vec.assign(v.begin(), v.begin()+3);	//v为向量，将v的0~2个元素赋值给vec。   
vec.assign(n,val);	//将n个val赋值给vec。   
vec.erase(vec.begin()+1,vec.begin()+3);	//删除区间的元素。这里的参数可以由begin()和end()函数返回的位置，也可以是迭代器。  
vec.erase(vec.begin());	//删除单个位置的元素，参数要求与上相同。    
v[n];	//支持下标，可以像数组一样访问每个位置上的数字。   
v1=v2;	//将v2赋值给v1替换v1之前的元素。   
v1={a,b,c...};	//用列表中的值赋值给v1并替换v1中原有的元素。   
== != < >等符号正常支持。    