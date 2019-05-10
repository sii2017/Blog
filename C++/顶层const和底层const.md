## 顶层const和底层const
顶层const可以表示任意的对象是常量，也是我们最常见的const。   
```c
const int a= 10;  	//顶层const   
```  
### 关于指针
而对于指针，由于指针本身是一个对象，它又可以指向另外一个对象。因此指针本身是不是常量以及指针所指的是不是一个常量就是两个相互独立的问题。   
用**顶层const(top-level const)**表示指针本身是个常量。     
用**底层const(low-level const)**表示指针所指对象是一个常量。   
```c
const int* b= &a;	//对于指针，const在前，是底层const，代表指向的对象是const的。   
int* const c;	//对于指针，const在后，是顶层const，代表指针本身是const的。   
const int* const d= &a;	//靠左的是底层const，意味着a是const的，靠右的是顶层const，意味着指针d本身是const的。   
```   
### 关于引用
对于引用，也存在顶层const和底层const。但是由于引用本身就无法与绑定的值解绑，因此不需要顶层const。我们需要注意的是底层const。  
```c
const int i= 10;   
const int& a= i;	//正确。在左的是底层const意味着绑定的i是const的。  
int& b= i;	//错误，i是具有const属性的，但是b不具有底层const属性。    
```   
### MORE
```c
int i= 0;	
int* const p1= &i;	//顶层const，意味着p1本身是const的，不能重新指向其它的变量。   
const int ci= 42;	//对于普通变量，都是顶层const且靠左，意味着变量本身为const。   
const int* p2= &ci;	//正确，对于指针左边是底层const，意味着指向的对象是const的。  
const int* const p3= p2;	//正确，底层const加顶层const，指针本身是const，指向的对象也是const   
const int& r= ci;	//正确，底层const，绑定的ci是const的。  
i= ci;	//正确，const变量可以赋值给非const变量  
p2= p3;	//正确，p2和p3指向的都是const对象   
int* p= p3;	//不正确，p3指向的对象是带const属性的，p也必须带底层const属性，不然就可以通过解引用改变指向的const属性的值了   
p2= &i;	//正确，int*能转换成const int*   
int& r= ci;	//不正确，ci带const属性，r必须要底层const，不然就能改变ci的值了。   
const int& r2= i;	//正确，const int&引用可以绑定到一个普通int上   
```   
> tips：可以看的出来，带const底层属性的指针和引用，并不代表指向的变量就带常属性的。只是这个带const底层属性的指针和引用不能改变它的值，实际上指向的对象可能是不带常属性的。   