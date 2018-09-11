## 标准库模板 array 数组
array与c数组相似的一种容器，在c++11推出。  
array是在连续的内存中进行存储的容器，与vector相似。   
array的特性在于，他的大小是固定的，是一开始就需要确定的，且不能增加或减少。因此它也不支持添加或删除元素。      
array也支持下标访问，并且效率很高。   
### 头文件支持  
```c
#inlcude <array>   
```   
### 初始化  
```c   
array<int, 10> ar = { 1,2,3,4,5,6,7,8,9,0 };	//通过初始化列表初始化   1,2,3,4,5,6,7,8,9,0   
array<int, 5> ar1 = { 1,2,3 };	//通过初始化列表初始化靠前的部分元素 1 2 3 0 0   
array<int, 0> ar2;	//0个元素的array是被允许的，但是不能被解引用    
array<int, 3> ar3;	//不初始化不会有默认初始化元素。 这里的元素是未定义的的。    
```   
由于大小是array类型的一部分，array不支持普通的容器构造函数。   
如果我们对array进行列表初始化，初始值的数目必须等于或小于array的大小。如果初始值数目小于array的大小，则它们被用来初始化array中靠前的元素，所有剩余元素都会进行值初始化。  
### 添加、删除元素
由于array的长度是固定的，因此无法添加及删除元素。   
### 赋值操作
```c
//c的内置数组无法整个赋值，但是array作为一个容器就可以做到。    
array<int, 3> ar1 = { 1,2,3 };  
array<int, 3> ar2 = { 3,2,1 };   
ar2 = ar1;  

//通过函数统一赋值   
array<int, 5> ar3;  
ar3.fill(100);	//100 100 100 100 100   

//通过下标直接赋值    
array<int, 4> ar4;   
for (int i = 0; i < ar4.size(); i++)   
{  
	ar4[i] = i;   
}   

array<int, 5> ar5;
ar5.assign(1);	//1 1 1 1 1 在c++reference中并没有出现assign，但是vs2017支持。  
```   
赋值操作如同数组一般，并且可以做到数组做不到的整个容器的赋值，这是比较方便的，但是注意需要两个容器有着相同的类型和大小。   
无法像vector一样进行段落的赋值，只支持个别元素赋值或整体统一赋值。  
### 调整空间  
空间固定是array的特性，因此无法以任何方式调整空间。  
### 功能函数
以下是array其它的一些功能函数：  
array<int, 10> arr;  
arr.size();	//返回大小  
arr.empty();	//返回是否为空  
arr.max_size();	//返回最大的大小，对于array来说与size相同  
arr.front();	//返回第一个元素  
arr.back();	//返回最后一个元素   
arr.data();	//返回指向array开始位置的指针  
arr1.swap(arr2);	//交换两个数组  
arr.at(pos);	//同下标访问元素，不过at函数会进行检查，如果越界会跳异常。   
以上就是array的功能函数，较少。  
> 需要注意的是，array的swap函数效率较低。   
> vector的swap函数效率高是由于，vector对象本身在栈上，而vector中存储的内容在堆上。因此vector调用swap函数的时候仅仅交换两个vector在堆上的指针，就可以高效的交换元素了。   
> 但是对于array来说，他是实实在在在栈上的元素，交换元素的话需要一个一个交换，改变栈的位置，所以效率较低。   
### 迭代器与遍历
迭代器是一种检查容器内元素并遍历元素的数据类型。C++更趋向于使用迭代器而不是下标操作，因为标准库为每一种标准容器定义了一种迭代器类型。    
```c
array<int, 10> arr = { 1,2,3,4,5,6,7,8,9,0 };   
//获取普通迭代器，分别对应容器的第一个元素和最后一个元素后一个位置。  
array<int, 10>::iterator itrBegin = arr.begin();  
array<int, 10>::iterator itrEnd = arr.end();   

//获取常属性的迭代器，分别对应容器的第一个元素和最后一个元素后一个位置。    
array<int, 10>::const_iterator citrBegin = arr.cbegin();   
array<int, 10>::const_iterator citrEnd = arr.cend();   

//获取反向迭代器，分别对应容器的最后一个元素，和开始第一个元素前的一个位置。  
array<int, 10>::reverse_iterator ritrBegin = arr.rbegin();  
array<int, 10>::reverse_iterator ritrEnd = arr.rend();  

//获取常属性的反向迭代器，分别对应容器的最后一个元素，和开始第一个元素前的一个位置。   
array<int, 10>::const_reverse_iterator critrBegin = arr.crbegin();   
array<int, 10>::const_reverse_iterator critrEnd = arr.crend();  
```  
迭代的话很简单，与其它容器相似。   
```c
for(array<int, 10>::iterator itrBegin = arr.begin(); itrBegin!= arr.end(); itr++)  
{   
	cout << *itrBegin << endl;   
}  
```
以上通过迭代可以逐个访问元素。不过即使不迭代也没事，因为array支持高效的随机访问，只要用下标[]就可以了。   
### 总结  
1 array比c的传统数组更安全，且拥有容器的一些更方便的地方。  
2 array长度固定不变，无法删除增加，这是与vector的明显差异。  
3 array与vector的不明显差异在于：array是在栈上，实际占有栈的空间的，而vector对象在栈上，保存的元素在堆上。因此前者swap函数效率比后者的效率要低很多。   
4 什么时候使用array？当我们使用c的传统数组的时候，可以将其替代为array，使之更安全更高效。   