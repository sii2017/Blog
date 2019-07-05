## socket编程 connect函数
connect函数通常用于客户端建立tcp连接。  
与bind函数的参数相同。但是bind是将套接字与ip和端口进行绑定，而connect是将套接字与ip和端口进行连接。     
```c
int connect (int sockfd,struct sockaddr * serv_addr,int addrlen);   
```   
**参数：**    
sockfd：用来通信的套接字。   
serv_addr：套接字想要连接的主机地址和端口号。   
addrlen：serv\_addr的长度。    
**返回值：**   
如果成功则返回0；失败返回-1。错误原因将存于errno中。   
**错误代码：**    
EBADF 参数sockfd 非合法socket处理代码  
EFAULT 参数serv\_addr指针指向无法存取的内存空间  
ENOTSOCK 参数sockfd为一文件描述词，非socket。   
EISCONN 参数sockfd的socket已是连线状态  
ECONNREFUSED 连线要求被server端拒绝。  
ETIMEDOUT 企图连线的操作超过限定时间仍未有响应。  
ENETUNREACH 无法传送数据包至指定的主机。  
EAFNOSUPPORT sockaddr结构的sa\_family不正确。   
EALREADY socket为不可阻塞且先前的连线操作还未完成。  
### TCP和UDP中connect的区别
connect是套接字连接操作，connect操作之后代表对应的套接字已连接，UDP协议在创建套接字之后，可以同多个服务器端建立连接通信，而TCP协议只能与一个服务器端建立通信，TCP不允许目的地址是广播或多播地址，UDP允许。当然UDP协议也可以像TCP协议一样，通过connect来指定对方的ip地址、端口。   
UDP协议经过connect之后，在通过sendto来发送数据报时不需要指定目的地址、端口，如果指定了目的地址、端口，那么会返回错误。通过UDP协议可以给同一个套接字指定多次connect操作，而TCP协议不可以，TCP只能指定一次connect操作。UDP协议指定第二次connect操作之后会先断口第一次的连接，然后建立第二次的连接。    
### 阻塞
建立socket后默认connect()函数为阻塞连接状态，在大多数实现中，connect的超时时间在75s至几分钟之间，想要缩短超时时间，可以将socket句柄设置为非阻塞状态。     
同时，处理使用非阻塞socket的connect函数的步骤有所不同。   
1 创建socket,返回套接口描述符;   
2 调用fcntl把套接口描述符设置成非阻塞;(LINUX环境）   
3 调用connect开始建立连接;   
4 判断连接是否成功建立;    
5.1 如果connect返回0,表示连接简称成功(服务器可客户端在同一台机器上时就有可能发生这种情况);    
5.2 如果connect没有返回0，之后调用select来等待连接建立成功完成;    
6.1 如果select返回0,则表示建立连接超时;我们返回超时错误给用户,同时关闭连接,以防止三路握手操作继续进行下去;    
6.2 如果select返回大于0的值,则需要检查套接口描述符是否可读或可写;如果套接口描述符可读或可写,则我们可以通过调用getsockopt来得到套接口上待处理的错误(SO_ERROR),如果连接建立成功,这个错误值将是0,如果建立连接时遇到错误,则这个值是连接错误所对应的errno值(比如:ECONNREFUSED,ETIMEDOUT等)。   
**非阻塞模式有3种用途**    
1.三次握手同时做其他的处理。connect要花一个往返时间完成，从几毫秒的局域网到几百毫秒或几秒的广域网。这段时间可能有一些其他的处理要执行，比如数据准备，预处理等。    
2.用这种技术建立多个连接。这在web浏览器中很普遍。    
3.由于程序用select等待连接完成，可以设置一个select等待时间限制，从而缩短connect超时时间。   
多数实现中，connect的超时时间在75秒到几分钟之间。有时程序希望在等待一定时间内结束，使用非阻塞connect可以防止阻塞75秒，在多线程网络编程中，尤其必要。   