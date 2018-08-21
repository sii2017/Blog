## 基于范围的for循环
c++11新增了一种循环，即**基于范围的for循环**。   
### 语法
语法如下：     
```c
for(for-range-declaration: expression)  
	statement    
```  
语句statement会按照顺序执行语句expression中的每个元素。   
### 例子
```c
#include <iostream>  
#include <vector>  
#include <string>   
using namespace std;  

int main(int argc, char** argv)  
{  
	//数组   
	int i[] = { 1,2,3,4,5,6 };  
	for (int a: i)   
		cout << a << " ";		//1,2,3,4,5,6   
	cout << endl;  

	//字符串  
	string str = "for-range";   
	for (auto& c : str)    
		cout << c << " ";	//f o r - r a n g e   
	cout << endl;  

	//字符串数组  
	vector<string> vecStr;   
	vecStr.push_back("first");   
	vecStr.push_back("second");  
	vecStr.push_back("third");   
	vecStr.push_back("forth");   
	vecStr.push_back("fifth");    
	vecStr.push_back("sixth");  
	for (auto singlestr : vecStr)   
		cout << singlestr << " ";	   
	cout << endl;   

	getchar();    
	return 0;   
}  
```  
### 关于范围for循环的特性
1 自动识别数组。   
2 自动识别具有.begin()和.end()的容器。   
3 使用基于自变量（auto）的查找begin()和end()。   