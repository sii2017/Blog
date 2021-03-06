## TCP的拥塞控制
### 什么是拥塞？什么是拥塞控制？
在某段时间内，若对网络中某一资源的需求超过了该资源所能提供的可用部分，网络的性能就要变坏。这种情况就称为拥塞。   
简单的说拥塞产生的原因有两点：（1）接收方容量不够（2）网络内部有瓶颈。   
拥塞控制就是防止过多的数据注入到网络中，这样可以使网络中的路由器或链路不致过载。   
> 拥塞控制与流量控制的区别   
拥塞控制是防止过多的数据注入到网络中，可以使网络中的路由器或链路不致过载，是一个全局性的过程。  
流量控制是点对点通信量的控制，是一个端到端的问题，主要就是抑制发送端发送数据的速率，以便接收端来得及接收。   
### 检测网络拥塞的方法
检测网络拥塞的指标是：由于缺少缓存空间而被丢弃的分组的百分数、平均队列长度、超时重传的分组数、平均分组时延、分组时延的标准差等，这些指标的上升都标志着拥塞的增长。   
可以使用这种方法来检测，在路由转发的分组中保留一个比特或字段，用该比特或字段的值表示网络有没有拥塞或产生了拥塞。也可以由一些主机或路由器周期性的发出探测分组，以询问拥塞是否发生。   
### 网络拥塞的表现
**（1）收到重复的ACK。**  
发送的包可能有些丢失，但是接收方没有接收到，而发送方由于发送窗口还可以发送，还在继续发，而接收方由于没有收到丢失的那个包，只能不断请求发送那个包对应的序列号。    
**（2）出现了超时。**   
当网路发生拥塞的时，路由器就要丢弃分组。因此只要发送方没有按时收到应当到达的确认报文，也就是说，只要出现了超时，就可以猜想网络可能出现了拥塞。（现在通信线路的传输质量一般都很好，因传输出差错而丢弃分组的概率都很小，远小于1%）（这也是发送方如何知道网络发生了拥塞的方法）   
### 拥塞控制的机制
![](https://github.com/sii2017/image/blob/master/%E6%8B%A5%E5%A1%9E01.png)
### TCP/IP协议的拥塞控制
TCP进行拥塞控制的四种算法：**慢开始、拥塞避免、快速重传、快速恢复。**   
拥塞窗口的大小取决于网络的拥塞程度，并且在动态的变化，发送方让自己的发送窗口等于拥塞窗口。发送方控制拥塞窗口的原则是：只要网络没有出现拥塞，拥塞窗口就可以再增大一些，以便把更多的分组发送出去，这样就可以提高网络的利用率，但只要网络出现拥塞或可能出现拥塞，就必须把窗口减小一些，以减少注入到网络中的分组数，以便缓解网络出现的拥塞。   
#### 慢开始算法思想（按指数增长）
当主机开始发送数据时，由于并不清楚网络的负荷情况，如果立即把大量数据字节注入到网络，那么就有可能引起网络发生拥塞，所以由小到大逐渐增大发送窗口，也就是由小到大逐渐增大拥塞窗口数值，试探一下网络的拥塞情况。  
![](https://github.com/sii2017/image/blob/master/%E6%8B%A5%E5%A1%9E02.png)  
慢开始规定，TCP最开始发送设置拥塞窗口的值cwnd=1，而每次收到确认报文就将拥塞窗口的值设为当前的两倍。（是的，如没有拥塞则以指数增长）   
为了防止拥塞窗口增长多大引起网络阻塞，为其设置了一个慢启动门限ssthresh，当到达门限时，就进入到拥塞避免阶段。  
> 当cnwd＜ssthresh，使用慢开始算法。  
当cnwd=ssthresh，既可使用慢开始算法，也可以使用拥塞避免算法。  
当cnwd＞ssthresh，使用拥塞避免算法。  
#### 拥塞避免算法的思路（按线性增长）
拥塞避免并非完全能够避免拥塞，是说在拥塞避免阶段将拥塞窗口控制为按线性规律增长，使网络比较**不容易**出现拥塞。   
因此这个阶段，不再以指数形式增长拥塞窗口，而是每经过一个往返时间RTT就将发送方的拥塞窗口+1，使其增长缓慢。  
按照线性方式增长，如果发生网络拥塞，比如丢包时，就将慢启动门限设为当前拥塞窗口值的一半，然后将拥塞窗口设置为1，重新开始执行慢启动算法。   
![](https://github.com/sii2017/image/blob/master/%E6%8B%A5%E5%A1%9E03.png)  
> 注意：  
> **无论是在慢开始阶段还是在拥塞避免阶段**，只要发送方判断网络出现拥塞（其根据就是没有收到确认，虽然没有收到确认可能是其他原因的分组丢失，但是因为无法判定，所以都当做拥塞来处理），就把慢开始门限设置为出现拥塞时的发送窗口大小的一半。然后把拥塞窗口设置为1，执行慢开始算法。    
#### 快速重传算法思想
快重传要求，  
**接收方**在收到一个失序的报文段后就立即发出重复确认（为的是使发送方及早知道有报文段没有到达对方）而不要等到自己发送数据时捎带确认。      
**发送方**只要一连接收到3个重复确认，就知道接收方确实没有收到该报文段，因而应当立即进行重传，而不必继续等待设置的重传计时器时间到期。这样就不会出现超时，发送方也就不会误认为出现了网络拥塞。   
![](https://github.com/sii2017/image/blob/master/%E6%8B%A5%E5%A1%9E04.png)  
使用快速重传可以使整个网络的吞吐量提高约20%。快速重传后进入快速恢复。    
> 快速重传与快速恢复是配合使用的算法，快速重传是接收方需要做的事情，而快速恢复则是发送方需要做的事情了。    
#### 快速恢复的思想
**采用快恢复算法时，慢开始只在TCP连接建立时和网络出现超时时才使用。**   
当**发送方**连续收到三个重复确认时，就执行“乘法减小”算法，把ssthresh门限减半。   
但是接下去并不执行慢开始算法。  
将慢启动门限值设置为原来的一半，然后将拥塞窗口设置为现在的慢启动的门限值，不再执行慢启动而是直接进入拥塞避免阶段。使发送窗口成线性方式增长。  