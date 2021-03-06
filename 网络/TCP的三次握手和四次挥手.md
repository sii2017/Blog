# TCP的三次握手和四次挥手
## TCP层面的位码
在TCP层面有个FLAGS字段，也可以成为位码和标识码。   
共有六种标识：   
SYN，（synchronous，建立主机）；   
ACK，（acknowledge，确认）；   
PSH，（push，传送）；  
FIN，（finish，结束）；   
RST，（reset，重置）；  
URG，（urgent，紧急）。   
这六种标识符默认情况下为1，当需要使用他们时，则设为1。    
其中，ACK是可能与SYN，FIN等同时使用的，比如SYN和ACK可能同时为1，它表示的就是建立连接之后的响应，如果只是单个的一个SYN，它表示的只是建立连接。   
但SYN与FIN是不会同时为1的，因为前者表示的是建立连接，而后者表示的是断开连接。   
RST一般是在FIN之后才会出现为1的情况，表示的是连接重置。   
一般地，当出现FIN包或RST包时，我们便认为客户端与服务器端断开了连接；而当出现SYN和SYN＋ACK包时，我们认为客户端与服务器建立了一个连接。    
TCP的连接建立和连接关闭，都是通过请求－响应的模式完成的。   
## 三次握手
TCP是主机对主机层的传输控制协议，提供可靠的连接服务，采用三次握手确认建立一个连接。   
**第一次握手**：   
主机A发送位码为SYN＝1，以及附带随机产生seq number=1234567（保存在包头的序列号字段里）的数据包到服务器B，主机A进入SYN\_SEND状态，等待服务器B确认。   
![](https://github.com/sii2017/image/blob/master/%E4%B8%89%E6%AC%A1%E6%8F%A1%E6%89%8B1.png)   
**第二次握手：**   
服务器B由SYN=1知道，A要求建立联机。   
服务器B发回确认包(ACK)应答。即SYN标志位和ACK标志位均为1同时，将确认序号(Acknowledgement Number)设置为主机A发来的seq+1，并附带随机产生自己的序列号seq=7654321，给主机A。   
服务器B进入SYN\_RECV状态。  
![](https://github.com/sii2017/image/blob/master/%E4%B8%89%E6%AC%A1%E6%8F%A1%E6%89%8B2.png)   
**第三次握手：**    
客户端A收到服务器B的SYN＋ACK确认包后，检查ack number是否正确，即第一次发送的seq number+1，以及位码ACK是否为1。若正确，向服务器B发送确认包，ACK位码设为1，ack number为服务器发来的seq+1，此包发送完毕，客户端A和服务器B进入ESTABLISHED状态，完成三次握手。   
![](https://github.com/sii2017/image/blob/master/%E4%B8%89%E6%AC%A1%E6%8F%A1%E6%89%8B3.png)   
## 四次挥手  
数据传输完毕后，双方都可释放连接。最开始的时候，客户端和服务器都是处于ESTABLISHED状态，然后客户端主动关闭，服务器被动关闭。   
**第一次挥手：**    
客户端A发出连接释放报文给服务器B，并且停止发送数据。   
释放数据报文首部，位码FIN=1，其序列号为seq=u（等于前面已经传送过来的数据的最后一个字节的序号加1）。此时，客户端进入FIN-WAIT-1（终止等待1）状态。   
**第二次挥手：**     
服务器B收到连接释放报文，发出确认报文，位码ACK=1，确认序列号ack=u+1，并且带上自己的序列号seq=v。此时，服务端就进入了CLOSE-WAIT（关闭等待）状态。   
TCP服务器通知高层的应用进程，客户端向服务器的方向就释放了，这时候处于半关闭状态，即客户端已经没有数据要发送了，但是服务器若发送数据，客户端依然要接受。这个状态还要持续一段时间，也就是整个CLOSE-WAIT状态持续的时间。    
**第三次挥手与第四次挥手之间：**   
客户端A收到服务器B的确认请求后，此时，客户端就进入FIN-WAIT-2（终止等待2）状态，等待服务器B发送连接释放报文（在这之前还需要接受服务器发送的最后的数据）。     
**第三次挥手：**   
服务器将最后的数据发送完毕后，就向客户端发送连接释放报文，位码FIN=1，确认序列号ack=u+1，由于在半关闭状态，服务器很可能又发送了一些数据，假定此时的序列号为seq=w，此时，服务器就进入了LAST-ACK（最后确认）状态，等待客户端的确认。      
**第四次挥手：**   
客户端收到服务器的连接释放报文后，发出确认报文，即位码ACK=1，ack number=w+1，而自己的序列号是seq number=u+1，此时，客户端就进入了TIME-WAIT（时间等待）状态。    
注意此时TCP连接还没有释放，必须经过2∗∗MSL（最长报文段寿命）的时间后，当客户端撤销相应的TCB后，才进入CLOSED状态。    
6 服务器只要收到了客户端发出的确认，立即进入CLOSED状态。同样，撤销TCB后，就结束了这次的TCP连接。可以看到，服务器结束TCP连接的时间要比客户端早一些。      
![](https://github.com/sii2017/image/blob/master/%E5%9B%9B%E6%AC%A1%E6%8C%A5%E6%89%8B.png)  