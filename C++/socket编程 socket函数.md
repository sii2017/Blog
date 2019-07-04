## socket编程 socket函数
使用socketAPI前，要先将相关链接库（ws2_32.lib）加入链接，并使用WSAStartUp函数初始化。   
```c
#include "pch.h"   
#include <iostream>   
#include <WinSock2.h>   
#pragma comment(lib, "ws2_32.lib")	//将ws2_32.lib加入链接    
```    
```c
WORD sockVerson = MAKEWORD(2, 2);	//指定winsock版本     
WSADATA wsaData;   
if (WSAStartup(sockVerson, &wsaData) != 0)	//初始化  
	return 0;   
```   
每个socket函数都可能失败（返回-1），需要判断结果。   
socket分成两种：  
一种用来监听新链接，这种socket叫master socket，一般只存在于服务器。   
一种用来收发数据，这种socket叫connected socket，客户端服务区端都会使用。   
```c
SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);    
if (clientSocket == INVALID_SOCKET)    
{    
	printf("套接字创建失败");  
	WSACleanup();   
	return 0;   
}     
```   
AF_INET表示IPv4，SOCK_STREAM表示流传输方式，IPPROTO_TCP表示传输协议。   