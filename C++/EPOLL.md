## EPOLL
前几天刚刚学习了socket编程中的select函数。   
> 可以参考同目录下《socket编程 select函数》   
   
我们可以知道select函数作为简单的方法，有着缺点：   
1 每次调用select都需要将进程加入到所有监视socket的等待队列，每次唤醒都需要从每个队列中移除。这里涉及了两次遍历，而且每次都要将整个fds列表传递给内核，有一定的开销。正是因为遍历操作开销大，出于效率的考量，才会规定select的最大监视数量，默认只能监视1024个socket。   
2 进程被唤醒后，程序并不知道哪些socket收到数据，还需要遍历一次。   
而EPOLL技术，想办法减少了遍历的方法，提高了监控socket的效率。   
### EPOLL的设计思路
epoll是在select出现N多年后才被发明的，是select和poll的增强版本。   
epoll通过以下一些措施来改进效率：功能分离和就序列表。   
#### 功能分离
select低效的原因之一是将“维护等待队列”和“阻塞进程”两个步骤合二为一。   
如下图所示，每次调用select都需要这两步操作：将进程添加到每个需要监控的socket的等待队列中，然后在分别阻塞。然而大多数应用场景中，需要监视的socket相对固定，并不需要每次都修改。    
epoll将这两个操作分开，先用epoll_ctl维护等待队列，再调用epoll_wait阻塞进程。显而易见的，效率就能得到提升。   
![](https://github.com/sii2017/image/blob/master/epoll1.jpg)   
如下的代码中，先用epoll_create创建一个epoll对象epfd，再通过epoll_ctl将需要监视的socket添加到epfd中，最后调用epoll_wait等待数据。   
```c
int s = socket(AF_INET, SOCK_STREAM, 0);    
bind(s, ...)   
listen(s, ...)   

int epfd = epoll_create(...);   
epoll_ctl(epfd, ...); //将所有需要监听的socket添加到epfd中   

while(1)   
{    
    int n = epoll_wait(...)  
    for(接收到数据的socket)   
	{  
        //处理  
    }   
}   
```
#### 就序列表   
select低效的另一个原因在于程序不知道哪些socket收到数据，只能一个个遍历。如果内核维护一个“就绪列表”，引用收到数据的socket，就能避免遍历。    
如下图所示，计算机共有三个socket，收到数据的sock2和sock3被rdlist（就绪列表）所引用。当进程被唤醒后，只要获取rdlist的内容，就能够知道哪些socket收到数据。   
![](https://github.com/sii2017/image/blob/master/epoll2.jpg)   
### epoll的原理和流程
#### 创建epoll对象
当某个进程调用epoll_create方法时，内核会创建一个eventpoll对象（也就是程序中epfd所代表的对象）。   
eventpoll对象也是文件系统中的一员，和socket一样，**它也会有等待队列**。   
![](https://github.com/sii2017/image/blob/master/epoll3.jpg)   
创建一个代表该epoll的eventpoll对象是必须的，因为内核要维护“就绪列表”等数据，“就绪列表”是eventpoll的成员。   
#### 维护监视列表
创建epoll对象后，可以用epoll_ctl添加或删除所要监听的socket。   
以添加socket为例，如下图，如果通过epoll_ctl添加sock1、sock2和sock3的监视，内核会将eventpoll添加到这三个socket的等待队列中。   
![](https://github.com/sii2017/image/blob/master/epoll4.jpg)   
> 值得注意的是，之前说过eventpoll对象也有等待队列。但是在这里，并不是把socket123添加到eventpoll的等待队列里，而是把eventpoll对象添加到socket123的等待队列里。   
   
当socket收到数据后，中断程序会操作eventpoll对象，**而不是直接操作进程**。   
#### 接收数据
当socket收到数据后，中断程序会给eventpoll的“就绪列表”添加收到数据的socket的引用。     
如下图展示的是sock2和sock3收到数据后，中断程序让rdlist引用这两个socket。   
![](https://github.com/sii2017/image/blob/master/epoll5.jpg)   
eventpoll对象相当于是socket和进程之间的中介，socket的数据接收并不直接影响进程，而是通过改变eventpoll的就绪列表来改变进程状态。   
当程序执行到epoll_wait时，如果rdlist已经引用了socket，那么epoll_wait直接返回，如果rdlist为空，阻塞进程。   
#### 阻塞和唤醒进程
