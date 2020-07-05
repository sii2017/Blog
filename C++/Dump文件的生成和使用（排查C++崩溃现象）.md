## Dump文件的生成和使用
c++程序本地崩溃，不值一提，可以很方便的重现和调试。   
但是当程序被客户使用，或者在云上崩溃，则比较麻烦。因为并不是所有地方都有log点，以及是否能复现，也是一个问题。   
因此会运用Dump就显得格外重要。   
### Dump文件的生成
Dump文件是进程的内存镜像，可以把程序的执行状态通过调试器保存到dump文件中。Dump文件是用来给驱动程序编写人员调试驱动程序用的，这种文件必须用专用工具软件打开，比如使用WinDbg、VisualStudio打开。       
当我们的程序发布出去之后，在客户机上是无法跟踪自己代码的BUG的，所以 Dump 文件对于我们来说特别有用。我们可以通过.dmp文件把出现BUG的情况再现，然后再现客户环境（包括堆栈调用等情况），设置源码调试路径，可以找到出现BUG的语句。     
#### 设置Dump的代码
> 本段落参考博文https://blog.csdn.net/tojohnonly/article/details/72845022   
   
想要程序在崩溃的时候出现dump文件，需要使用DbgHelp模块的MINIDUMP编程生成。   
首先需要包含头文件。  
```c
#include <DbgHelp.h>   
```    
代码如下：   
```c
int GenerateMiniDump(PEXCEPTION_POINTERS pExceptionPointers)
{
    // 定义函数指针
    typedef BOOL(WINAPI* MiniDumpWriteDumpT)(
        HANDLE,
        DWORD,
        HANDLE,
        MINIDUMP_TYPE,
        PMINIDUMP_EXCEPTION_INFORMATION,
        PMINIDUMP_USER_STREAM_INFORMATION,
        PMINIDUMP_CALLBACK_INFORMATION
        );
    // 从 "DbgHelp.dll" 库中获取 "MiniDumpWriteDump" 函数
    MiniDumpWriteDumpT pfnMiniDumpWriteDump = NULL;
    HMODULE hDbgHelp = LoadLibrary(_T("DbgHelp.dll"));
    if (NULL == hDbgHelp)
    {
        return EXCEPTION_CONTINUE_EXECUTION;
    }
    pfnMiniDumpWriteDump = (MiniDumpWriteDumpT)GetProcAddress(hDbgHelp, "MiniDumpWriteDump");

    if (NULL == pfnMiniDumpWriteDump)
    {
        FreeLibrary(hDbgHelp);
        return EXCEPTION_CONTINUE_EXECUTION;
    }
    // 创建 dmp 文件件
    TCHAR szFileName[MAX_PATH] = { 0 };
    const TCHAR* szVersion = _T("DumpDemo_v1.0");
    //TCHAR* szVersion = TEXT("DumpDemo_v1.0");
    SYSTEMTIME stLocalTime;
    GetLocalTime(&stLocalTime);
    wsprintf(szFileName, L"%s-%04d%02d%02d-%02d%02d%02d.dmp",
        szVersion, stLocalTime.wYear, stLocalTime.wMonth, stLocalTime.wDay,
        stLocalTime.wHour, stLocalTime.wMinute, stLocalTime.wSecond);
    HANDLE hDumpFile = CreateFile(szFileName, GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_WRITE | FILE_SHARE_READ, 0, CREATE_ALWAYS, 0, 0);
    if (INVALID_HANDLE_VALUE == hDumpFile)
    {
        FreeLibrary(hDbgHelp);
        return EXCEPTION_CONTINUE_EXECUTION;
    }
    // 写入 dmp 文件
    MINIDUMP_EXCEPTION_INFORMATION expParam;
    expParam.ThreadId = GetCurrentThreadId();
    expParam.ExceptionPointers = pExceptionPointers;
    expParam.ClientPointers = FALSE;
    pfnMiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(),
        hDumpFile, MiniDumpWithDataSegs, (pExceptionPointers ? &expParam : NULL), NULL, NULL);
    // 释放文件
    CloseHandle(hDumpFile);
    FreeLibrary(hDbgHelp);
    return EXCEPTION_EXECUTE_HANDLER;
}

LONG WINAPI ExceptionFilter(LPEXCEPTION_POINTERS lpExceptionInfo)
{
    // 这里做一些异常的过滤或提示
    if (IsDebuggerPresent())
    {
        return EXCEPTION_CONTINUE_SEARCH;
    }
    return GenerateMiniDump(lpExceptionInfo);
}
```    
当上面的代码准备好，在执行代码的地方加入
```c
SetUnhandledExceptionFilter(ExceptionFilter);   
```   
当该程序运行崩溃的时候就会在exe所在同目录生成一个dump文件。   
### Dump文件的使用
> 本段落参考博文 https://blog.csdn.net/tojohnonly/article/details/72864694   
   
当我们双击exe文件并且崩溃后，就会产生dump文件。   
如果崩溃呢，这比较简单……   
```c
int* p = nullptr;   
*p = 1;   
```   
双击大打开Dump文件，用vs打开。    
#### 确保路径相同
一定要确保进程名称对应的程序**路径**在本地存在，同时确保最初生成程序的对应.pdb符号文件也在当前目录。   
有时从客户那里反馈回来的Dump文件程序路径和本地的不一致，需要将程序拷贝到Dump信息里面的路径中去。   
#### 设置symbols路径
调试文件需要对应的符号文件，我们需要设置符号文件对应的路径：   
在Dump信息摘要右上角，点击设置符号路径，一般选Mircrosoft符号服务器就行，再设置个本地缓存符号的目录。   
#### 设置源码路径
在左侧的解决方案处（边边上）右键点击 属性->调试源文件，将源代码的路径添加进来，注意一定是解决方案所在的路径。    
#### 调试Dump文件
准备工作已就绪，现在在Dump文件摘要右上角点击使用仅限本机进行调试。    
> 如果提示无法找到调试信息、或者调试信息不匹配，无法查找或打开 PDB 文件。说明没有将最初生成程序的对应 .pdb 符号文件放在调试程序所在的目录，或者 .pdb 符号文件与当前的程序版本不匹配。   
   
顺利的话，就会重现当时发生的问题。   
#### 追加
实际使用中发现，直接把dum文件放到本机pdb符号文件同目录就可以了。   
不需要重新建目录……