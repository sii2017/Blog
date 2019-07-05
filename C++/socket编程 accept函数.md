## socket编程 accept函数
accept()系统调用主要用在基于连接的套接字类型，比如SOCK_STREAM和SOCK_SEQPACKET。    
**它提取出所监听套接字的等待连接队列中第一个连接请求，创建一个新的套接字，并返回指向该套接字的文件描述符。**    
新建立的套接字不在监听状态，原来所监听的套接字也不受该系统调用的影响。   
```c
SOCKET accept(SOCKET sock, struct sockaddr *addr, int *addrlen);    
```   
返回值：为新的套接字，可以用这个套接字进行通信。   
参数sock，为监听套接字。调用函数后该套接字不受影响。   
参数addr，指向struct sockaddr的指针，该结构用通讯层服务器对等套接字的地址(一般为客户端地址)填写，返回地址addr的确切格式由套接字的地址类别(比如TCP或UDP)决定。   
参数addrlen，一个值结果参数，调用函数前必须初始化为包含addr所指向结构大小的数值。函数返回时包含对等地址(一般为服务器地址)的实际数值；   
```c
SOCKET revSocket;   //用来接收返回的通信用的socket   
sockaddr_in remoteAddr;	//初始化，但是内容是由函数来接收的，也就是由客户端填写    
int remoteAddrLen = sizeof(remoteAddr);  //仅如初始化   

revSocket = accept(listenSocket, (SOCKADDR*)&remoteAddr, &remoteAddrLen);   
```   
### 阻塞
一般来说，**实现时accept()为阻塞函数**，当监听socket调用accept()时，它先到自己的receive\_buf中查看是否有连接数据包。    
若有，把数据拷贝出来，删掉接收到的数据包，创建新的socket与客户发来的地址建立连接；若没有，就阻塞等待。    
如果队列中没有等待的连接，套接字也没有被标记为Non-blocking，accept()会阻塞调用函数直到连接出现；    
如果套接字被标记为Non-blocking，队列中也没有等待的连接，accept()返回错误EAGAIN或EWOULDBLOCK。   