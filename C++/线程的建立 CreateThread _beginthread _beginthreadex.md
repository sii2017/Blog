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
（参考《windows程序设计》第5版珍藏版）
## \_beginthreadex与\_endthreadex