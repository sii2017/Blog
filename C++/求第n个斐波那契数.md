## 第n个斐波那契数
斐波那契数列详情参考数学目录下《斐波那契数列》   
简单的来说，斐波那契数列为固定的一个数列：1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233，377，610，987，1597，2584，4181，6765，10946，17711，28657，46368........     
这个数列从第3项开始，每一项都等于前两项之和。   
### 题目
根据参数n来获取，第n个斐波那契数。   
### 思路
通过递归的思想，我们可以知道，低n个斐波那契数字，等于第n-1+低n-2，因此可以用递归的思路来做。  
由于递归的效率仍然是低于循环的，所以最后我们再从数字中找到规律，以动态规划的方式进行优化，最终得到循环的版本。   
### 代码（递归）
```c
int Fibonacci(int num)  
{  
	if (num == 1 || num == 2)   
		return 1;  
	return Fibonacci(num - 1) + Fibonacci(num - 2);  
}  
```  
### 代码（循环）   
```c
int Fibonacci(int num)  
{   
	if (num == 1 || num == 2)   
		return 1;   
	int* Fibonacci = new int[num];  
	Fibonacci[0] = Fibonacci[1] = 1;   

	for (int i = 2; i < num; i++)   
	{   
		Fibonacci[i] = Fibonacci[i - 1] + Fibonacci[i - 2];   
	}   
	return Fibonacci[num - 1];  
}   
```   
由于斐波那契数列是比较有特色的数列，并且在算法题中经常遇到，因此记录下来。   