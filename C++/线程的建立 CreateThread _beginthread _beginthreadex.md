# 线程建立的三种方式
程序代码的执行，是执行线程的工作。当一个进程建立起来，主线程也会产生。每一个windows程序一开始就会有一个执行线程。如果有需要我们可以调用函数来产生额外的执行线程。   
在之前的学习过程中，一共了解了三种建立线程的方式。分别为Createthread，\_beginthread，\_beginthreadex。   
三种函数，各有区别。**其中建议使用\_beginthreadex函数**，而其中原因将一一进行分析。
## CreateThread
CreateThread函数实际上是操作系统层面调用的函数，与之对应的结束线程为ExitThread。   
```c
CreateThread(LPSECURITY_ATTRIBUTES lpThreadAttributes,   
DWORD dwStackSize,   
LPTHREAD_START_ROUTINE lpStartAddress,    
LPVOID lpParameter,  
DWORD dwCreationFlags,   
LPDWORD lpThreadId   
);      
```   
第一个参数表示安全属性的设定以及继承。  
第二个参数设定堆栈的大小。   
第三个参数设定「执行线程函数」名称，而该函数的参数则在这里的第四个参数设定。    
第五个参数如果是0表示让执行线程立刻开始执行，如果是CREATE_SUSPENDED，则是要求执行线程暂停执行（调用
ResumeThread令其重新开始）。    
最后一个参数是个指向DWORD的指针，系统会把执行线程的ID 放在这里。   
**由于该函数应该为操作系统所调用，所以不建议程序员使用。**   
（参考侯捷的《深入浅出MFC》）  
## \_beginthread与\_endthread
与CreateThread相比，\_beginthread更值得去使用。   
### 语法  
```c
uintptr_t _beginthread(   
void( *start_address )( void * ),   
unsigned stack_size,   
void *arglist   
);   
```   
假如成功，函数将会返回一个新线程的句柄，并可以存储在变量中：   
```
HANDLE hStdOut = _beginthread( CheckKey, 0, NULL);    
```   
如果失败_beginthread将返回-1。   
第一个参数start_address为新线程的起始地址 ，指向新线程调用的函数的起始地址。    
第二个参数stack_size为新线程的堆栈大小，可以为0。    
第三个参数arglist为传递给线程的参数列表，无参数时为NULL。   
该函数使用需要头文件process.h作为支持。  
（参考《windows程序设计》第5版珍藏版）  
### 与CreateThread的区别
很多开发者不清楚这两者之间的关系，随意选一个函数来用，发现也没有什么大问题。等到有一天忽然发现一个程序运行时间很长的时候会有细微的内存泄露，开发者绝对不会想到是因为这两套函数用混的结果。   
根据Windows API和MSVC CRT的关系，可以看出来\_beginthread是对CreateThread的封装，它最终还是调用CreateThread来创建线程。   
那么在\_beginthread调用CreateThread()之前做了什么呢？我们可以看一下\_beginthread的源代码，它位于 CRT源代码中的thread.c。我们发现它在调用CreateThread之前申请了一个叫\_tiddata的结构，然后将这个结构用\_initptd函数初始化之后传递给\_beginthread自己的线程入口函数\_threadstart。\_threadstart首先把由\_beginthread传过来的\_tiddata结构指针保存到线程的显式TLS数组，然后它调用用户的线程入口真正开始线程。在用户线程结束之后，\_threadstart函数调用\_endthread结束线程。并且\_threadstart还用\_try/\_except将用户线程入口函数包起来，用于捕获所有未处理的信号，并且将这些信号交给CRT处理。   
所以除了信号之外，很明显CRT包装Windows API线程接口的最主要目的就是为了\_tiddata结构。这个线程私有的结构里面保存的是什么呢？我们从mtdll.h中找到它的定义，它里面保存的是诸如线程ID、线程句柄、erron、strtok()的前一次调用位置、rand()函数的种子、异常处理等与CRT有关的而且是线程私有的信息。可见 MSVC CRT并没有使用我们前面所说的\_\_declspec(thread)这种方式来定义线程私有变量，从而防止库函数在多线程下失效，而是采用在堆上申请一个\_tiddata结构，把线程私有变量放在结构内部，由显式TLS保存\_tiddata的指针。    
了解了这些信息以后，我们应该会想到一个问题，那就是如果我们用CreateThread创建一个线程然后调用CRT的strtok()函数，按理说应该会出错，因为strtok()所需要的\_tiddata并不存在，可是我们好像从来没碰到过这样的问题。查看strtok()函数就会发现，当一开始调用\_getptd()去得到线程的\_tiddata结构时，这个函数如果发现线程没有申请\_tiddata结构，它就会申请这个结构并且负责初始化。于是无论我们调用哪个函数创建线程，都可以安全调用所有需要\_tiddata的函数，因为一旦这个结构不存在，它就会被创建出来。    
那么\_tiddata在什么时候会被释放呢？ExitThread()肯定不会，因为它根本不知道有\_tiddata这样一个结构存在，那么很明显是_endthread()释放的，这也正是CRT的做法。    
不过我们很多时候会发现，即使使用CreateThread()和ExitThread() （不调用ExitThread()直接退出线程函数的效果相同），也不会发现任何内存泄露，这又是为什么呢？经过仔细检查之后，我们发现原来密码在CRT DLL的入口函数DllMain中。我们知道，当一个进程/线程开始或退出的时候，每个DLL的DllMain都会被调用一次，于是动态链接版的CRT就有机会在DllMain中释放线程的\_tiddata。**可是DllMain只有当CRT是动态链接版的时候才起作用，静态链接CRT是没有DllMain的！这就是造成使用CreateThread会导致内存泄露的一种情况。**在这种情况下，\_tiddata在线程结束时无法释放，造成了泄露。    
（转自某博客）   
> 概括：\_beginthread函数会额外申请内存空间来存储相关的数据。但是仅仅在静态链接CRT的情况下，该内存空间无法被正常释放，会引起内存泄漏。     
> 总结，如果能使用\_beginthraed则不要使用CreateThread函数。   
### 例子   
```c
//线程1每秒输出一次，线程2每3秒输出一次。线程1在5次循环后自己结束。持续30秒后，线程2随着主线程一起结束。   
#include <iostream>    
#include <process.h>    
#include <windows.h>     
  
using namespace std;     
  
void ThreadFun1(PVOID param){     
    for(int i=0; i<5; i++)   
	{      
        Sleep(1000);      
        cout << "this is ThreadFun1" << endl;      
    }      
	_endthread();	//自己结束线程，并且handle会被该函数关闭
}      
  
void  ThreadFun2(PVOID param){   
	//无限循环，但是会随着主线程的结束而结束     
    while (1)    
	{    
        Sleep(3000);      
        cout << "this is ThreadFun2" << endl;     
    }    
}      
  
int main(){    
    int i = 0;      
  
    _beginthread(ThreadFun1, 0, NULL);      
    _beginthread(ThreadFun2, 0, NULL);    
    Sleep(30000);    
    cout << "end" << endl;      
    return 0;     
}       
```     
## \_beginthreadex与\_endthreadex
当前\_beginthreadex比\_beginthread更值得去使用。  
### 语法
```c
uintptr_t _beginthreadex( // NATIVE CODE    
   void *security,     
   unsigned stack_size,      
   unsigned ( __stdcall *start_address )( void * ),      
   void *arglist,    
   unsigned initflag,    
   unsigned *thrdaddr       
);    
```  
**以下三个参数与\_beginthread一致：**   
参数start\_address是启动开始执行新线程的例程的地址。    
参数stack\_size为新线程的堆栈大小或 0。   
参数arglist是要传递到新线程的参数列表或 NULL。   
**以下三个参数为\_beginthreadex独有：**  
参数Security是指向SECURITY\_ATTRIBUTES结构的指针，此结构确定返回的句柄是否由子进程继承。 如果Security为NULL，则不能继承句柄。    
参数initflag是控制新线程的初始状态的标志。 将initflag设置为0以立即运行，或设置为CREATE\_SUSPENDED以在挂起（暂停）状态下创建线程(使用ResumeThread来启动该线程)。 将initflag设置为 STACK\_SIZE\_PARAM\_IS\_A\_RESERVATION标志以将stack\_size用作堆栈的初始保留大小（以字节计）；如果未指定此标志，stack\_size将指定提交大小。   
参数thrdaddr是指向接收线程标识符的32位变量，用于记录线程地址。如果此变量为 NULL，则不可用。    
### 与\_beginthread的区别
对两者进行比较，我们可以得知：  
1 \_beginthreadex较\_beginthreadex拥有额外的三个参数：initflag,security和threadaddr。因此\_beginthreadex可以使我们（在安全线，状态，及识别上）更好的掌控新线程。  
2 \_beginthreadex在失败时返回0，而\_beginthread返回-1L。   
3 \_beginthread使用\_endthread终止，\_beginthreadex使用\_endthreadex终止。当线程的回调函数返回时，系统会自动调用\_beginthread和\_begintheadex来结束线程并且释放相关的资源。   
4 当我们使用\_beginthead来创建新线程，而这个线程如果很快就结束了，那么返回的句柄**可能**是无效的，或者是指向其它地方的。而如果我们使用\_beginthreadex来创建线程，那么返回的句柄总是有效的。显然后者更安全。       
> 需要注意的是，\_beginthread返回的句柄在调用\_endthread时会被系统释放。但是\_beginthreadex返回的句柄不会被系统释放，它只能被使用者手动始放。因此当我们使用\_beginthreadex来创建线程，无论我们将回调函数返回，或者是使用\_endthreadex结束线程，都需要再通过函数CloseHandle这个API函数手动的始放句柄。   