## Boost asio 常用函数
asio，意为异步输入/输出。  
该库可以让c++异步处理数据。异步任务的主要优点在于，在等待任务完成时不需要阻塞应用程序，可以去执行其它任务。   
异步任务的典型例子是网络应用。如果数据被发送出去，通常需要知道数据是否发送成功。如果没有一个类似asio这样的库，则必须等待函数的返回值来判断是否成功，需要等待一段时间。   
而使用boost asio，这个过程被分为两个单独的步骤：第一步是作为一个异步任务开始传输数据。一旦传输完成，不论成功失败，应用程序都会在第二步中得到相关的结果通知。而同时应用程序无需阻塞到传输完成，可以在这段时间里执行其它操作。   
### I/0服务和I/O对象
使用Boost Asio进行异步数据处理的应用程序基于两个概念：I/O服务和I/O对象。    
I/O服务抽象了操作系统的接口，允许第一时间进行异步数据处理，而 I/O 对象则用于初始化特定的操作。   
Boost.Asio只提供了一个名为boost::asio::io\_service的类作为I/O服务，它针对所支持的每一个操作系统都分别实现了优化的类。   
```c
boost::asio::io\_service io\_service;    //初始化  
```
另外库中还包含了针对不同 I/O 对象的几个类。其中，类boost::asio::ip::tcp::socket用于通过网络发送和接收数据，而类boost::asio::deadline\_timer则提供了一个计时器，用于测量某个固定时间点到来或是一段指定的时长过去了。   
### boost::asio::deadline\_timer类  
```c    
\#include <boost/asio.hpp>   
\#include <iostream>     
 
void handler(const boost::system::error_code &ec)    
{    
   std::cout << "5 s." << std::endl;   
}   
 
int main()   
{    
   boost::asio::io_service io_service;    
   boost::asio::deadline\_timer timer(io\_service, boost::posix_time::seconds(5));   //用io\_service初始化timer，同时定一个5秒的闹钟   
   timer.async\_wait(handler);   //被定义后立刻开始计时   
   io\_service.run();   
}    
```  
函数 main()首先定义了一个I/O服务io_service，用于初始化I/O对象timer。   
**所有I/O对象通常都需要一个I/O服务作为它们的构造函数的第一个参数。**   
由于timer的作用类似于一个闹钟，所以boost::asio::deadline_timer的构造函数可以传入第二个参数，用于表示在某个时间点或是在某段时长之后闹钟停止。    
该计时器在被定义后立刻开始计时，即async\_wait函数。   
```c
timer.async\_wait(handler);   //被定义后立刻开始计时   
```   
值得注意的是，这里我们只是传入了函数名，而该函数此刻并没有被调用，直到计时结束。   
async\_wait()的好处是，该函数调用会立即返回，而不是等待五秒钟。一旦闹钟时间到，作为参数所提供的函数就会被相应调用。因此，应用程序可以在调用了async\_wait()之后执行其它操作，而不是阻塞在这里。   