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
### select函数工作原理   
服务端需要管理多个客户端连接，而recv只能监视单个socket，这种矛盾下，人们开始寻找监视多个socket的方法。   
假如能够预先传入一个socket列表，如果列表中的socket都没有数据，挂起进程；   
直到有一个socket收到数据，唤醒进程。这种方法很直接，也是select的设计思想。  
在如下的代码中，先准备一个数组（下面代码中的fds），让fds存放着所有需要监视的socket。然后调用select，如果fds中的所有socket都没有数据，select会在while内无限循环，直到有一个socket接收到数据，select返回值，并唤醒进程。用户可以遍历fds，通过FD_ISSET判断具体哪个socket收到数据，然后做出处理。 

### select函数工作实例