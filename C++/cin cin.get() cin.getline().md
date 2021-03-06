# cin输入相关函数 
在遍历c++ primer plus这本书的过程中，第五第六章出现率很高的cin.get()，cin.getline()引起里了我的注意，甚至还有点搞不清楚。   
这种通过命令框的输入，在目前工作中的实际模块里并不常见，因此也不太熟悉，趁此了解一下，并且经由博客记录下来，以便以后需要用到时可以迅速上手。   
相关函数分别有以下好几种：  
```c
cin >> ch; 	//通过重载操作符>>来操作cin   
cin.get();	//通过get函数   
cin.getline();	//通过getline函数   
getline();	//与cin的getline相似，确实别人家的getline函数   
```   
## cin重载操作符>>的使用   
### 1 cin >> 可以输入一个字符或一个数字。   
```c
int i;   
cin >> i;  

char ch;   
cin >> ch;   
```  
如果输入多个字符，比如abc，而只有一个   
```c
cin >> ch;  
```  
那么只会读取第一个a，但是bc还在流里，因此再次获取流的话，会依次得到b和c。  
### 2 cin >> 可以输入一串字符串。   
```c
char ch[10];     
cin >> ch;   
```    
输入：abc；输出：abc。   
输入：abc cba；输出abc。   
**这个用法遇到空格，tab，回车会停止，并从流中移除这些符号。**     
如果超出了ch的长度怎么办？   
输入：abcdefghijklmnopq；输出：abcdefghijklmnopq。   
可以看到这个用法并不会知道ch的长度，只会根据是否遇到空格，tab或回车来看是否停止。   
注意：大于10个字符后的字符，其实是存储在后面的野生内存里的，只不过由于ch的最后没有'\0'停止符，在输出的时候cout不知道停止了，因此一直输出下去直到最后。这是比较危险的。   
## cin.get()   
### 1 接收单个字符   
```c
//1   
char ch;   
ch= cin.get();    

//2 
cin.get(ch);      
```   
输入：a；输出：a。   
输入：ab；输出：a；下一次再输出：b。  
与之前的“cin>>”相似，每次只能输入一个字符，但是如果有多个字符，那么会存在流中依次被输入。   
> 如果不把get到的字符赋值，那么可以用作舍弃这个特定的字符来使用。  
> 比如有个空格，那么读掉但是不赋值，再进行下一次读取了。  
   
### 2 接收字符串   
这里使用了这个函数的重载模式，存在两个参数，第一个参数为目标字符数组，第二个参数为最大从流中读取的数量。   
```c
char ch[10];   
cin.get(a,10);   
```   
这个函数与之前的“cin>>”相比，更安全，会自动根据字符长度截断，然后在最后预留一个位置加入'\0'字符。  
输入：abcdefghij；输出：abcdefghi。  
由于j是第十个字符，因此被阶段，第十个字符加入了'\0'。    
**另外这个函数并不会由于空格和tab截断，会保留空格和tab，仅仅遇到回车停止，并且不移除回车符。**        
## cin.getline()
### 1 获取一行字符（双参数用法）       
这个函数是用来接收一行字符串的，接收空格，tab等符号，直到遇到回车键结束，**并移除回车符。**     
用法与带参数的get函数相似。   
```c
char ch[10];  
cin.getline(ch, 10);   
```   
同样会在最后一个字符的位置加入'\0'，同样遇到'\0'结束，同样会根据长度来截断。   
### 2 获取一行字符（三参数用法）   
这个函数有重载的另外一个版本。前两个参数相同，第三个参数为停止符。  
双参数版本默认为遇到'\0'结束，但是第三个参数可以设置我们想要的结束的字符。  
```c
char ch[10];   
cin.getline(ch, 10, 'a');   
```   
输入：cbaddd；输出：cb。   
## 总结  
就单个字符，可以使用cin.get()。   
就字符串，使用cin.getline()会比较简单，使用cin.get()会更精确一些。   
值得注意的是，使用cin.get(ch, n)来获取字符串，**不会移除最后的回车符**，因此如果后面还有多次输入操作，由于函数会读取到最后未被移除的回车符，会认为已经到句尾，则语句结束。这种时候，可以通过无参数的cin.get()来读取（移除）这个回车符。   
cin.getline()不会有这样的困扰。   