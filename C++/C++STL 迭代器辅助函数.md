## C++ STL迭代器辅助函数
```c
advance(itr);   
distance(itr1,itr2);   
iter_swap(itr1,itr2);   
```   
### advance
advance函数可以使迭代器前进或者后退。   
advance共2个参数，第一个参数为迭代器，第二个参数为整型，意味着移动的步数和方向。   
第二个参数如果为正数则为++移动，负数则为--移动。   
advance()并不检查迭代器是否超过序列的边界，即begin之前或end之后，因此这是使用的时候需要注意的。    
```c
vector<int> vec;   
for (int i = 0; i < 5; i++)   
	vec.push_back(i);  
vector<int>::iterator itr = vec.begin();  
cout << *itr << endl;	//0    
//advance(itr, -1);	//error advance不会检测迭代器是否超过了边界，因此会报错   
advance(itr, 1);	//前进一步   
cout << *itr << endl;	//1  
advance(itr, -1);	//倒退一步  
cout << *itr << endl;	//0   
advance(itr, 4);	//前进四步   
cout << *itr << endl;	//4   
advance(itr, 1);   
if (itr == vec.end())   
cout << "itr==vec.end()" << endl;   
//advance(itr, 1);		//error advance函数不会检测迭代器是否超过了尾迭代器，因此会报错   
```   
### distance
distance函数可以返回迭代器之间的距离。   
distance函数有两个参数，分别是迭代器1和迭代器2，返回迭代器2减去迭代器1的距离。   
两个迭代器必须指向同一个容器。   
```c
vector<int> vec;   
for (int i = 0; i < 5; i++)  
	vec.push_back(i);   
vector<int>::iterator itrbegin = vec.begin();   
vector<int>::iterator itrend = vec.end();  
cout << distance(itrbegin, itrend) << endl;	//5   
cout << distance(itrend, itrbegin) << endl;	//-5   
```  
### iter_swap
itr_swap函数可以交换迭代器itr1和itr2所指的值。   
itr_swap函数的参数同样是2个，分别为itr1和itr2。   
两个迭代器的类型并不需要完全相同，但是所指向的值必须可以相互赋值。  
```c
vector<int> vec;  
list<int> li;   
vec.emplace_back(1);  
li.emplace_back(10);   
iter_swap(vec.begin(), li.begin());   
cout << *vec.begin() << endl;  	//10
cout << *li.begin() << endl;      //1
```   
可以看到即使是不同的容器vec和list之间也可以进行顺利的值交换。    