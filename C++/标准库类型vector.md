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
**加入单个元素（只能加在末尾）**   
push\_back函数负责将一个值压进vector对象的尾端，作为它新的尾元素。   
```c
vector<int> vec1;  
vec1.push_back(10);   

vector<string> vec2;  
vec2.push_back("abc");  

vector<int> vec3;  
for(int i=0; i<10; i++)  
	vec3.push_back(i);   
```    
**加入批量元素（会删除原有的元素）**   
assign函数可以一次性为vector加入批量的元素。    
需要注意的是，原来的元素就被消除了，取而代之的是放入的新元素，与初始化相似。   
```c
vector<int> vec;   
for (int i = 0; i < 5; i++)   
	vec.push_back(i);			//此时vec为 0 1 2 3 4    

vector<int> vec1(3, 15);		//15 15 15    

//通过其它vector来进行赋值    
vec.assign(vec1.begin(),vec1.end());	//此时 vec为15 15 15     
//第一个参数代表数量，第二个参数代表元素，与初始化类似的赋值   
vec.assign(4, 18);	//vec为18 18 18     
```   
**加入批量或单个元素（保留原有的元素）**   
```c
vector<int> vec;  
for (int i = 0; i < 5; i++)   
	vec.push_back(i);			//0 1 2 3 4   

//第一种用法：在最开始的位置插入10。    
vec.insert(vec.begin(), 10);	// 10 0 1 2 3 4   
//第二种用法：在第二个位置插入3个25。    
vec.insert(vec.begin() + 1, 3, 25);	//10 25 25 25 0 1 2 3 4   

vector<int> vec2{ 10001,10002,10003,9999 };   
//第三种用法：在vec的第三个位置插入vec2从开始到最后的数据   
vec.insert(vec.begin() + 2, vec2.begin(), vec2.end());	//10 25 10001 10002 10003 9999 25 25 0 1 2 3 4   
```
> 注意：任何情况下，不能通过下标去给vector添加元素，会造成内存越界。在元素压入前，是不会分配内存的，因此访问不存在的下标，会报错。    
### 删除元素
**删除单个元素（只能删除尾元素）**   
与push_back相似，pop_back可以弹出（删除）vector的尾元素。   
```c
vector<int> vec;   
for (int i = 0; i < 5; i++)   
	vec.push_back(i);			//此时vec为 0 1 2 3 4        
str.pop_back();	//此时 0 1 2 3   
```   
**删除批量元素**   
vector的erase函数，可以根据提供的位置，删除一个或者多个连续的元素。   
```c
vector<int> vec;  
for (int i = 0; i < 5; i++)  
	vec.push_back(i);			//0 1 2 3 4    

vec.erase(vec.begin());		//1 2 3 4   
vec.erase(vec.begin(), vec.end() - 1);	//4    
```   
在使用erase的时候需要注意，如果正在使用迭代器的话，那么删除元素后迭代器有可能会失效。   
### 预分配空间
一般情况下来说，我们使用vector可以需要在需要插入数据的时候再插入，因为vector从末尾插入数据效率也比较高。但是如果我们要进一步提高vector添加数据的效率该怎么做呢？那就是预分配空间了。   
**带初始化的调整空间**  
resize函数，如字面意思，重新分配内存。   
该函数在保留原有数据的情况下，调整（包括增减和减少）vector的空间。多则删除，少则补上。   
补上的值，如果第二个参数进行设置了，则补上的值以此初始化，如果没有第二个参数，那么其值随机。   
```c
vector<int> vec;  
for (int i = 0; i < 5; i++)  
	vec.push_back(i);			//0 1 2 3 4    

//这里采用的是初始化值的方式    
vec.resize(10, 10);		//0 1 2 3 4 10 10 10 10 10   
vec.pop_back();			//0 1 2 3 4 10 10 10 10  
vec.pop_back();		//0 1 2 3 4 10 10 10  
	
cout << "当前vec内的数据为：";			//0 1 2 3 4 10 10 10  
for (auto i : vec)  
	cout << i << " ";  
cout << endl;     
cout << "当前可容纳的空间为：" << vec.capacity() << endl;			//10    
```  
可以看到，即使我们之后pop_back了两次尾元素，实际删除了最后的两个10。使用capacity返回的空间仍然为10，说明已经成功为vector预分配了内存。   
**不初始化的增加空间**   
reserve函数直接为vector扩充内存，里面的值不会被初始化，是完全空着的。  
如果reserve的参数小于当前实际vector的数量的话，什么也不会发生。   
```c
vector<int> vec;
for (int i = 0; i < 5; i++)
	vec.push_back(i);			//0 1 2 3 4 

vec.reserve(100);
	
cout << "当前vec内的数据为：";			//0 1 2 3 4
for (auto i : vec)
	cout << i << " ";
cout << endl;   
cout << "当前可容纳的空间为：" << vec.capacity() << endl;			//100
cout << endl;
```  
> 即使预分配了内存，当内存不够用时，系统还是会自动增加内存的。   
> 这种操作只有在需要给vector添加大量数据的时候才显得有意义，因为这将避免系统自动给内存多次容量扩充操作。（尽管系统自动给vector扩容效率挺高，但是多次扩容仍然会降低性能）。      
   
**减少空间到到满足元素所占存储空间的大小**   
看了之前的扩大内存，shrink\_to\_fit函数可以帮助我们减去不需要的预分配内存，到满足当前元素所占存储空间的大小为止。   
需要注意的是，在使用vector的过程中，无论是系统自动申请还是由我们来分配，当删除元素的时候系统不会自动始放这个内存，因此当我们删除了大量元素的时候，这个函数可以让vector进行瘦身，来减少内存的占用。      
```c
vector<int> vec;  
for (int i = 0; i < 5; i++)   
	vec.push_back(i);			//0 1 2 3 4   

vec.reserve(100);		//内存增加到100   
cout << "当前可容纳的空间为：" << vec.capacity() << endl;			//100   
vec.shrink_to_fit();	//内存减小到5，正好可以存储当前的数量   
cout << "当前可容纳的空间为：" << vec.capacity() << endl;			//5   
```
> vector并不会自动释放不用的内存空间。      
### 功能函数
以下是一些常用的功能函数：   
vec.empty();	//如果不含任何元素则返回真；反之假。   
vec.size();	//返回元素的个数。   
vec.clear();	//清空vec中的元素。  
vec.front();	//返回vec中第一个元素。   
vec.back();		//返回vec中最后一个元素。     
vec.capacity();  //返回vec在内存中总共可以容纳的元素个数（如果预分配了空间）   
vecA.swap(vecB);	//将vecA和vecB的数据进行整体性的交换。   
v[n];	//支持下标，可以像数组一样访问每个位置上的数字，但不会检查是否越界。    
vec.at(n);    //at方法访问，与下标相同，区别就是at会检查是否越界，是则抛出out of range异常。   
int* p= vec.data(); 	//返回一个指针。可行的原因在于vector在内存中就是一个连续存储的数组，所以可以返回一个指针指向这个数组。这是是C++11的特性。   
v1=v2;	//将v2赋值给v1替换v1之前的元素。   
v1={a,b,c...};	//用列表中的值赋值给v1并替换v1中原有的元素。   
== != < >等符号正常支持。    
### 常用算法支持
使用算法需要包含头文件algorithm。  
```c
vector<int> vec;  
vec.push_back(1);  
vec.push_back(5);   
vec.push_back(3);   
vec.push_back(4);  
vec.push_back(2);   
	
sort(vec.begin(), vec.end());	//1 排序vec   
reverse(vec.begin(), vec.end());	//2 翻转vec   

//3 将前两个参数的范围内的元素复制到第三个参数的vector中，从第三个参数的位置开始。   
//注意，vec1中必须要足够的空间可以容纳传进去的数值，不然会报错。
vector<int> vec1(10, 22);   
copy(vec.begin(), vec.end(), vec1.begin() + 2);	   	
for (int i : vec1)   
	cout << i << " ";   
 
//4 寻找元素的位置，返回迭代器。如果没找到则返回vec.end()。    
vector<int>::iterator itr;   
itr = find(vec.begin(), vec.end(), 2);  
if(itr!=vec.end())   
	//这就是找到的第一个元素为2的位置的迭代器   
```
### 迭代器的使用及遍历
迭代器是一种检查容器内元素并遍历元素的数据类型。C++更趋向于使用迭代器而不是下标操作，因为标准库为每一种标准容器定义了一种迭代器类型。   
```c
vector<int> vec;   
for (int i = 0; i < 5; i++)  
	vec.push_back(i);	 	 	
	
vector<int>::iterator itr;   
for (itr = vec.begin(); itr != vec.end(); itr++)  
	cout << *itr << " ";   
```
### 使用场景
当我们不知道该使用什么容器的时候，就可以选择使用vector。   