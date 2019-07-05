## socket编程 bind函数
```c
int bind(int sockfd, const struct sockaddr *addr,socklen_t *addrlen);   
```   
当用socket()函数创建套接字以后，套接字在名称空间(网络地址族)中存在，但没有任何地址给它赋值。   
bind()把用addr指定的地址和端口号赋值给用文件描述符代表的套接字sockfd。addrlen指定了以addr所指向的地址结构体的字节长度。一般来说，该操作称为“给套接字命名”。     
调用bind()函数之后，为socket()函数创建的套接字关联一个相应地址，发送到这个地址的数据可以通过该套接字读取与使用。    
bind()函数并不是总是需要调用的，只有用户进程想与一个具体的地址或端口相关联的时候才需要调用这个函数。如果用户进程没有这个需要，那么程序可以依赖内核的自动的选址机制来完成自动地址选择，而不需要调用bind()函数，同时也避免不必要的复杂度。   
**在一般情况下，对于服务器进程问题需要调用bind()函数，对于客户进程则不需要调用bind()函数。**    
```c
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
```   
#### 为什么客户端不需要bind
无连接的socket的**客户端和服务端** 以及 面向连接socket的**服务端** 通过调用bind函数来配置本地信息。   
如果使用bind函数时，通过将my_addr.sin\_port置为0，函数会自动为你选择一个未占用的端口来使用。   
Bind()函数在成功被调用时返回0；出现错误时返回"-1"并将errno置为相应的错误号。   
需要注意的是，在调用bind函数时一般不要将端口号置为小于1024的值，因为1到1024是系统保留端口号，你可以选择大于1024中的任何一个没有被占用的端口号。    
面向连接连接的socket客户端通过调用Connect函数在socket数据结构中保存本地和远端信息，无须调用bind()，因为这种情况下只需知道目的机器的IP地址，而客户通过哪个端口与服务器建立连接并不需要关心。socket执行体为你的程序自动选择一个未被占用的端口，并通知你的程序数据什么时候打开端口。（当然也有特殊情况，linux系统中rlogin命令应当调用bind函数绑定一个未用的保留端口号，还有当客户端需要用指定的网络设备接口和端口号进行通信等等）     
**总之：**   
**1.需要在建连前就知道端口的话，需要bind。**   
**2.需要通过指定的端口来通讯的话，需要bind。**   
 
服务器和客户端都可以bind，bind并不是服务器的专利。     

**客户端进程bind，端口**：由进程选择一个端口去连服务器，（如果默认情况下，调用bind函数时，内核指定的端口是同一个，那么调用多个调用了bind（）的client程序，会出现端口被占用的错误）注意这里的端口是客户端的端口。如果不分配就表示交给内核去选择一个可用端口。
**客户端进程bind，IP地址**：相当于为发送出去的IP数据报分配了源IP地址，但交给进程分配IP地址的时候（就是这样写明了bind IP地址的时候）这个IP地址必须是主机的一个接口，不能分配一个不存在的IP。如果不分配就表示由内核根据所用的输出接口来选择源IP地址。   
一般情况下客户端是不用调用bind函数的，一切都交给内核搞定。   

**服务端进程bind，端口**：基本是必须要做的事情，比如一个服务器启动时（比如freebsd），它会一个一个的捆绑众所周知的端口来提供服务，同样，如果bind了一个端口就表示我这个服务器会在这个端口提供一些“特殊服务”。   
**服务端进程bind，IP地址**：目的是限制了服务端进程创建的socket只接受那些目的地为此IP地址的客户链接，一般一个服务器程序里都有   
```c
servaddr.sin_addr.s_addr = htonl(INADDR_ANY);    
```
这样一句话，意思就是：我不指定客户端的IP，随便连，来者不拒！   

总之只要你bind时候没有指定哪一项（置为0），内核会帮你选择。   
### 服务器端口绑定的例子
```c
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
```