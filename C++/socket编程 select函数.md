## socket编程 select函数
在socket编程中，select是个重要的函数，需要熟练了解。  
> 尽管现在已经有更好的替代，效率更高的EPOLL了。   
  
前日正在学习EPOLL，看到相关的介绍中，select是EPOLL的前身，为了更好的学习EPOLL，因此这里先学习了select的相关内容。   
在之前的博客里记录的socket系列函数中，在服务器端都是针对单个socket的情况，即同一时间服务器只能处理单个socket。   
即这个简单的流程是，创建监听套接字，绑定IP和端口，开始监听，等待连接，建立连接后返回一个新的通讯套接字，开始接受客户端的数据。   
复习下相关代码：   
```c
int main()  
{   
	WORD sockVersion = MAKEWORD(2, 2);   
	WSADATA wsaData;   
	if (WSAStartup(sockVersion, &wsaData) != 0)  
		return 0;   

	//创建监听套接字   
	//AF_INET表示IPv4,SOCK_STREAM表示流数据传输模式，IPPROTO_TCP是传输协议   
	SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);   
	if (listenSocket == INVALID_SOCKET)   
	{  
		printf("套接字创建失败");   
		WSACleanup();   
		return 0;  
	}   

	//绑定IP和端口   
	sockaddr_in addrListen;   
	addrListen.sin_family = AF_INET;	//指定IP格式   
	addrListen.sin_port = htons(8888);	//绑定端口号   
	addrListen.sin_addr.S_un.S_addr = INADDR_ANY;	//表示任何IP   
	if (bind(listenSocket, (SOCKADDR*)&addrListen, sizeof(addrListen)) == SOCKET_ERROR)  
	{   
		printf("binding falied");  
		closesocket(listenSocket);  
		return 0;   
	}  


	//开始监听  
	if (listen(listenSocket, 5) == SOCKET_ERROR)  
	{  
		printf("监听出错");   
		closesocket(listenSocket);  
		return 0;  
	}   
	
	//等待连接，连接后建立一个新的通讯套接字  
	SOCKET revSocket;  
	sockaddr_in remoteAddr;   
	int remoteAddrLen = sizeof(remoteAddr);  
	printf("等待连接...\n");  

	//等待客户端请求，服务器接受请求   
	revSocket = accept(listenSocket, (SOCKADDR*)&remoteAddr, &remoteAddrLen);  
	if (revSocket == INVALID_SOCKET)  
	{     
		printf("客户端发出请求，服务器端接受失败: %d \n", WSAGetLastError());  
		closesocket(listenSocket);   
		WSACleanup();  
		return 0;  
	}  
	else   
		printf("连接成功:%s \n", inet_ntoa(remoteAddr.sin_addr));  

	int res;  
	do  
	{  
		//接收客户端数据   
		char revData[255] = "";  
		char* sendData = new char[100];  
		//通过建立的连接通信   
		res = recv(revSocket, revData, 255, 0);  
		if (res > 0)    
		{  
			printf("Bytes received: %d\n", res);  
			printf("客户端发送的数据为:%s\n", revData);   
			if (strcmp(revData, "try to connect")==0)  
			{  
				char sendBuf[] = "connect successful";   
				send(revSocket, sendBuf, (int)strlen(sendBuf), 0);   
			}  
		}  
		else if (res == 0)  
			printf("Connection closed\n");   
		else   
			printf("recv failed: %d\n", WSAGetLastError());   
		delete sendData;  
	} while (res > 0);   

	closesocket(revSocket);  
	WSACleanup();  
}  
```  
而select函数，使服务器可以**同时监听并处理多个socket的连接**。    
> 也可以说学到这里，select，服务器端的认识又更前进了一步。   
   
### select函数
select函数在linux和windows并不相同，有微小的差异。   
由于目前我处在windows环境下，就以windows环境下的select来说。   
```c
int select(int nfds, // 忽略,为了与linux兼容  
fd_set FAR* readfds, // 1  
fd_set FAR* writefds, // 2  
fd_set FAR* exceptfds, // 3  
const struct timeval FAR* timeout); // 4  
```  
> 以下是一段对于linux平台下select函数的描述，与windows的select函数大同小异，为了便于理解，记录在这里。   
   
select 函数的作用是检测一组 socket 中某个或某几个是否有“事件”就绪，这里的“事件”一般分为如下三类：   
**读事件就绪：**   
socket 内核中，接收缓冲区中的字节数大于等于低水位标记 SO\_RCVLOWAT，此时调用 recv 或 read 函数可以无阻塞的读该文件描述符， 并且返回值大于0；   
TCP 连接的对端关闭连接，此时调用 recv 或 read 函数对该 socket 读，则返回 0；   
侦听 socket 上有新的连接请求；   
socket 上有未处理的错误。   
**写事件就绪：**    
socket 内核中，发送缓冲区中的可用字节数(发送缓冲区的空闲位置大⼩) 大于等于低水位标记 SO_SNDLOWAT，此时可以无阻塞的写, 并且返回值大于0；   
socket 的写操作被关闭(调用了 close 或者 shutdown 函数)（ 对一个写操作被关闭的 socket 进行写操作, 会触发 SIGPIPE 信号）；   
socket 使⽤非阻塞 connect 连接成功或失败之后；    
**异常事件就绪：**   
socket 上收到带外数据。   
**参数说明：**   
参数 nfds，为了与linux兼容，windows下该参数可以设为0。   
参数 readfds，需要监听可读事件的 fd 集合。   
参数 writefds，需要监听可写事件的 fd 集合。  
参数 exceptfds，需要监听异常事件 fd 集合。   
**返回值：**   
负值：select错误；   
正值：某些文件可读写或出错；   
0：等待超时，没有可读写或错误的文件。   
### select函数工作原理   
服务端需要管理多个客户端连接，而recv只能监视单个socket，这种矛盾下，人们开始寻找监视多个socket的方法。   
假如能够预先传入一个socket列表；  
如果列表中的socket都没有数据，挂起进程；   
直到有任何一个socket收到数据，唤醒进程。   
这种方法很直接，也是select的设计思想。  
在如下的代码中，先准备一个数组（下面代码中的fds），让fds存放着所有需要监视的socket。然后调用select，如果fds中的所有socket都没有数据，select会在while内无限循环，直到有任何一个socket接收到数据，select返回值，并唤醒进程。用户可以遍历fds，通过FD_ISSET判断具体哪个socket收到数据，然后做出处理。    
```
int s = socket(AF_INET, SOCK_STREAM, 0);    
bind(s, ...)  
listen(s, ...)   

int fds[] =  存放需要监听的socket   

while(1){   
    int n = select(..., fds, ...)  
    for(int i=0; i < fds.count; i++){   
        if(FD_ISSET(fds[i], ...)){ 
            //fds[i]的数据处理   
        }  
    }   
}  
```   
### 图解select流程
select的实现思路很直接。假如程序同时监视如下图的sock1、sock2和sock3三个socket，那么在调用select之后，操作系统把进程A分别加入这三个socket的等待队列中。   
![](https://github.com/sii2017/image/blob/master/select1.jpg)   
这个时候进程A是挂起的。内核将会运行其它进程B和C，而进程A就是我们运行select的用来监控的进程。   
当任何一个socket收到数据后，中断程序将唤起进程A。   
![](https://github.com/sii2017/image/blob/master/select2.jpg)   
如上图打个比方是socket2唤醒的进程A。   
所谓的唤醒进程，就是将进程从所有的等待队列中移除，加入到正常的工作队列中与进程B和C一起。   
![](https://github.com/sii2017/image/blob/master/select3.jpg)    
经由这些步骤，当进程A被唤醒后，它（进程A自己）知道至少有一个socket接收了数据。程序只需遍历一遍socket列表，就可以找到（事件）就绪的socket了。   
### select函数工作实例  
先上代码。   
```c
#include "pch.h"  
#include <stdio.h>   
#include <string.h>    
#include <WINSOCK2.H>  

#pragma comment(lib,"ws2_32.lib")   

#define INT_SERVER_PORT 5000   
#define STR_SERVER_IP "127.0.0.1"   
#define INT_DATABUFFER_SIZE 100   

int main(void)  
{  
	WORD dwVersion = MAKEWORD(2, 2);  
	WSAData wsaData;   
	WSAStartup(WINSOCK_VERSION, &wsaData);  

	SOCKET sockServer = socket(AF_INET, SOCK_STREAM, 0);   
	if (INVALID_SOCKET == sockServer)  
	{   
		printf("Failed to create socket!\n");  
		WSACleanup();  
		return;  
	}  

	sockaddr_in addrServer;	//监听socket  
	memset(&addrServer, 0, sizeof(sockaddr_in));  
	addrServer.sin_family = AF_INET;   
	addrServer.sin_port = htons(INT_SERVER_PORT);  
	addrServer.sin_addr.S_un.S_addr = htonl(INADDR_ANY);    

	int iResult;   

	bool bReuseAddr = true;    
	iResult = setsockopt(sockServer, SOL_SOCKET, SO_REUSEADDR, (char *)&bReuseAddr, sizeof(bReuseAddr));		//设置套接字选项  
	if (SOCKET_ERROR == iResult)   
	{  
		printf("Failed to set resueaddr socket!\n");   
		WSACleanup();   
		return;  
	}    

	iResult = bind(sockServer, (sockaddr *)&addrServer, sizeof(addrServer));	//绑定端口   
	if (SOCKET_ERROR == iResult)  
	{   
		printf("Failed to bind address!\n");  
		WSACleanup();  
		return;   
	}   

	if (0 != listen(sockServer, 5))	//启用监听   
	{  
		printf("Failed to listen client!\n");   
		WSACleanup();  
		return;  
	}   

	UINT i = 0;  
	SOCKET sockAccept;  
	sockaddr_in addrAccept;  
	int iAcceptLen = sizeof(addrAccept);  
	char szDataBuff[INT_DATABUFFER_SIZE];  
	int iRecvSize;  

	sockaddr_in addrTemp;   
	int iTempLen;  

	fd_set fd; 
	FD_ZERO(&fd);   
	FD_SET(sockServer, &fd);	//fd中加入监听socket   

	printf("Start server...\n");  
	while (1)   
	{  
		fd_set fdOld = fd;  
		iResult = select(0, &fdOld, NULL, NULL,/*&tm*/NULL);   
		if (0 <= iResult)  
		{  
			for (i = 0; i < fd.fd_count; i++)   
			{   
				if (FD_ISSET(fd.fd_array[i], &fdOld))  
				{  
					//如果socket是服务器，则接收连接    
					if (fd.fd_array[i] == sockServer)  
					{  
						memset(&addrAccept, 0, sizeof(addrTemp));  
						sockAccept = accept(sockServer, (sockaddr *)&addrAccept, &iAcceptLen);   
						if (INVALID_SOCKET != sockAccept)  
						{   
							FD_SET(sockAccept, &fd);  
							printf("%s:%d has connected server!\n", inet_ntoa(addrAccept.sin_addr),
								ntohs(addrAccept.sin_port));   
						}    
					}  
					else //非服务器,接收数据(因为fd是读数据集)     
					{  
						memset(szDataBuff, 0, INT_DATABUFFER_SIZE);    
						iRecvSize = recv(fd.fd_array[i], szDataBuff, INT_DATABUFFER_SIZE, 0);
						memset(&addrTemp, 0, sizeof(addrTemp));    
						iTempLen = sizeof(addrTemp);
						getpeername(fd.fd_array[i], (sockaddr *)&addrTemp, &iTempLen);    

						if (SOCKET_ERROR == iRecvSize)   
						{   
							closesocket(fd.fd_array[i]);  
							FD_CLR(fd.fd_array[i], &fd);   
							i--;  
							printf("Failed to recv data ,%s:%d errorcode:%d.\n",
								inet_ntoa(addrTemp.sin_addr), ntohs(addrTemp.sin_port), WSAGetLastError());   
							continue;  
						}   

						if (0 == iRecvSize)  
						{   
							//客户socket关闭    
							printf("%s:%d has closed!\n", inet_ntoa(addrTemp.sin_addr),
								ntohs(addrTemp.sin_port));   

							closesocket(fd.fd_array[i]);   
							FD_CLR(fd.fd_array[i], &fd);  
							i--;   
						}  

						if (0 < iRecvSize)  
						{   
							//打印接收的数据     
							printf("recv %s:%d data:%s\n", inet_ntoa(addrTemp.sin_addr),
								ntohs(addrTemp.sin_port), szDataBuff);   
						}  
					}   
				}  
			}  
		}     
		else if (SOCKET_ERROR == iResult)    
		{     
		//  printf("Faild to select sockt in server!\n");      
			Sleep(100);    
		}    
	}    
	WSACleanup();    
}    
```    
与维护的fd数组有关的有几个宏，需要了解一下。   
```c
FD_ZERO(&fd);   
```   
FD\_ZERO用来清空fd，在每次使用fd之前作为初始化使用。   
```c
FD_SET(sockServer, &fd);   
```  
FD\_SET即在fd中加入需要监控的socket。   
我们在代码中可以看到我们先加入了监听socket，来监控这个监听socket，如果监听socket有响应，那么说明有新的连接申请接入服务器。   
这个情况下我们调用accept函数来得到一个新的通讯socket进行通讯，不过我们并不用recv这个阻塞函数等待数据，而是把新的通讯socket加入到fd中，继续用select进行监控。   
这样整个监控有序，且进程不会被阻塞。  
其实看到这里，select的功能一览无遗。   
```c
if (FD_ISSET(fd.fd_array[i], &fdOld)){}    
```   
FD\_ISSET宏本质上就是检测对应的位置上是否置 1。  
通过select函数后，作为第二个参数的fd会被标记是否有事件发生。因此我们复制了一个oldfd，来进行select，然后通过FD\_ISSET宏遍历比较，找到那个发生事件的socket。  
```c
FD_CLR(fd.fd_array[i], &fd);   
```  
FD\_CLR宏用于在文件描述符集合中删除一个文件描述符。   
以上的代码可以用下图完美的阐述代码的思路。  
![](https://github.com/sii2017/image/blob/master/select4.jpg)   
### 注意   
1 select 函数调用前后会**修改** readfds、writefds 和 exceptfds 这三个集合中的内容（如果有的话），所以如果您想下次调用 select 复用这个变量，记得在下次调用前再次调用 select 前先使用 FD_ZERO 将集合清零，然后调用 FD_SET 将需要检测事件的 fd **再次添加**进去。  
我们在上面代码中使用的方法是，把fd赋值给一个新的oldfd，然后用oldfd作为参数进行select，这样就不会影响原本的fd了。   
2 select函数作为监控的功能，既可以用在监听socket身上，也可以用在通讯socket身上。由于它可以时刻监听，因此就可以代替recv这个将会阻塞的函数了。   
当然，当有socket有数据传输来的时候仍然是用recv进行接收数据，但是并不用因此而长时间阻塞了。   
3 不仅服务器端能用，客户端也能用。   
### select的缺点   
简单的方法往往有缺点，现在EPOLL的效率更高，在学习select的过程中应该知道他的缺点在哪里。   
其一，每次调用select都需要将进程加入到所有监视socket的等待队列，每次唤醒都需要从每个队列中移除。这里涉及了两次遍历，而且每次都要将整个fds列表传递给内核，有一定的开销。正是因为遍历操作开销大，出于效率的考量，才会规定select的最大监视数量，默认只能监视1024个socket。   
其二，进程被唤醒后，程序并不知道哪些socket收到数据，还需要遍历一次。    
解决的方法便是EPOLL了，详情可以参考同一目录下的《EPOLL》。