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
boost::asio::io_service io_service;    //初始化  
```
另外库中还包含了针对不同 I/O 对象的几个类。其中，类boost::asio::ip::tcp::socket用于通过网络发送和接收数据，而类boost::asio::deadline\_timer则提供了一个计时器，用于测量某个固定时间点到来或是一段指定的时长过去了。   
### boost::asio::deadline\_timer类  
```c    
#include <boost/asio.hpp>   
#include <iostream>     
 
void handler(const boost::system::error_code &ec)    
{    
   std::cout << "5 s." << std::endl;   
}   
 
int main()   
{    
   boost::asio::io_service io_service;    
   boost::asio::deadline_timer timer(io_service, boost::posix_time::seconds(5));   //用io_service初始化timer，同时定一个5秒的闹钟   
   timer.async_wait(handler);   //被定义后立刻开始计时   
   io_service.run();   
}    
```  
函数 main()首先定义了一个I/O服务io_service，用于初始化I/O对象timer。   
**所有I/O对象通常都需要一个I/O服务作为它们的构造函数的第一个参数。**   
由于timer的作用类似于一个闹钟，所以boost::asio::deadline_timer的构造函数可以传入第二个参数，用于表示在某个时间点或是在某段时长之后闹钟停止。    
该计时器在被定义后立刻开始计时，即async\_wait函数。   
```c
timer.async_wait(handler);   //被定义后立刻开始计时   
```   
值得注意的是，这里我们只是传入了函数名，而该函数此刻并没有被调用，直到计时结束。   
async\_wait()的好处是，该函数调用会立即返回，而不是等待五秒钟。一旦闹钟时间到，作为参数所提供的函数就会被相应调用。因此，应用程序可以在调用了async\_wait()之后执行其它操作，而不是阻塞在这里。   
象async\_wait()这样的方法被称为是非阻塞式的。I/O对象通常还提供了阻塞式的方法，可以让执行流在特定操作完成之前保持阻塞。 例如，可以调用阻塞式的wait()方法，取代boost::asio::deadline\_timer的调用。由于它会阻塞调用，所以它不需要传入一个函数名，而是在指定时间点或指定时长之后返回。   
在async\_wait以后又调用了run函数。   
### run函数
```c
io_service.run();   
```  
这是必须的，因为控制权必须被操作系统接管，才能在五秒之后调用 handler() 函数。  
尽管async\_wait()会启动一个异步操作并立即返回，而run()则是阻塞的。因此调用run()后程序执行会停止。    
另外在上面的代码中，如果不用run将函数阻塞的话，就会自然的执行到main的最后从而返回，整个程序就结束了，定时器也会失效。   
因此，上述的程序“应该”被阻塞。   
那么有没有不该被阻塞的程序呢？   
如果应用程序不应被阻塞，那么就应该在一个**新的线程**内部调用 run()，它自然就会仅仅阻塞那个线程。   
### 多线程
如果在某个boost::asio::io\_service类型的对象之上调用run()方法，则相关联的句柄也会在同一个线程内被执行。通过使用多线程，应用程序可以同时调用多个run()方法。一旦某个异步操作结束，相应的I/O服务就将在这些线程中的某一个之中执行句柄。如果第二个操作在第一个操作之后很快也结束了，则I/O服务可以在另一个线程中执行句柄，而无需等待第一个句柄终止。  
```c
#include <boost/asio.hpp>   
#include <boost/thread.hpp>   
#include <iostream>    

void handler1(const boost::system::error_code &ec)  
{  
	std::cout << "5 s." << std::endl;  
}   

void handler2(const boost::system::error_code &ec)  
{   
	std::cout << "5 s." << std::endl;   
}   

boost::asio::io_service io_service;   

void run()  
{   
	io_service.run();  
}   

int main()   
{   
	boost::asio::deadline_timer timer1(io_service, boost::posix_time::seconds(5));   
	timer1.async_wait(handler1);   
	boost::asio::deadline_timer timer2(io_service, boost::posix_time::seconds(5));   
	timer2.async_wait(handler2);  
	boost::thread thread1(run);   
	boost::thread thread2(run);   
	thread1.join();  
	thread2.join();   
}   
```   
我们在 main() 中创建了两个线程。 这两个线程均针对同一个 I/O 服务调用了 run() 方法。 这样当异步操作完成时，这个 I/O 服务就可以使用两个线程去执行句柄函数。    
这个例子中的两个计时数均被设为在五秒后触发。 由于有两个线程，所以 handler1() 和 handler2() 可以同时执行。   
**如果第二个计时器触发时第一个仍在执行，则第二个句柄就会在第二个线程中执行。 如果第一个计时器的句柄已经终止，则 I/O 服务可以自由选择任一线程。**   
线程可以提高应用程序的性能。 因为线程是在处理器内核上执行的，所以创建比内核数更多的线程是没有意义的。 这样可以确保每个线程在其自己的内核上执行，而没有同一内核上的其它线程与之竞争。    
要注意，使用线程并不总是值得的。 以上例子的运行会导致不同信息在标准输出流上混合输出，因为这两个句柄可能会并行运行，访问同一个共享资源：标准输出流 std::cout。 这种访问必须被同步，以保证每一条信息在另一个线程可以向标准输出流写出另一条信息之前被完全写出。 在这种情形下使用线程并不能提供多少好处，如果各个独立句柄不能独立地并行运行。   
多次调用同一个I/O服务的run()方法，是为基于Boost.Asio的应用程序增加可扩展性的推荐方法。另外还有一个不同的方法：不要绑定多个线程到单个I/O服务，**而是创建多个 I/O 服务**。然后每一个I/O服务使用一个线程。如果I/O服务的数量与系统的处理器内核数量相匹配，则异步操作都可以在各自的内核上执行。   
```c
#include <boost/asio.hpp>    
#include <boost/thread.hpp>    
#include <iostream>    

void handler1(const boost::system::error_code &ec)   
{   
	std::cout << "5 s." << std::endl;   
}   

void handler2(const boost::system::error_code &ec)   
{   
	std::cout << "5 s." << std::endl;   
}   

boost::asio::io_service io_service1;   
boost::asio::io_service io_service2;  

void run1()  
{    
	io_service1.run();   
}   

void run2()  
{   
	io_service2.run();  
}   

int main()   
{   
	boost::asio::deadline_timer timer1(io_service1, boost::posix_time::seconds(5));  
	timer1.async_wait(handler1);   
	boost::asio::deadline_timer timer2(io_service2, boost::posix_time::seconds(5));   
	timer2.async_wait(handler2);  
	boost::thread thread1(run1);  
	boost::thread thread2(run2);  
	thread1.join();   
	thread2.join();  
}    
```    
前面的那个使用两个计时器的例子被重写为使用两个 I/O 服务。 这个应用程序仍然基于两个线程；但是现在每个线程被绑定至不同的 I/O 服务。 此外，两个 I/O 对象 timer1 和 timer2 现在也被绑定至不同的 I/O 服务。   
这个应用程序的功能与前一个相同。 在一定条件下使用多个 I/O 服务是有好处的，每个 I/O 服务有自己的线程，最好是运行在各自的处理器内核上，这样每一个异步操作连同它们的句柄就可以局部化执行。 如果没有远端的数据或函数需要访问，那么每一个 I/O 服务就象一个小的自主应用。 这里的局部和远端是指象高速缓存、内存页这样的资源。 由于在确定优化策略之前需要对底层硬件、操作系统、编译器以及潜在的瓶颈有专门的了解，所以应该仅在清楚这些好处的情况下使用多个 I/O 服务。   
### 网络编程 客户端
Boost.Asio 提供了多个 I/O 对象以开发网络应用。   
以下例子使用了 boost::asio::ip::tcp::socket 类来建立与中另一台PC的连接，并下载 'Highscore' 主页；就象一个浏览器在指向 www.highscore.de 时所要做的。   
```c
#include <boost/asio.hpp>   
#include <boost/array.hpp>   
#include <iostream>    
#include <string>    

boost::asio::io_service io_service;   
boost::asio::ip::tcp::resolver resolver(io_service);   
boost::asio::ip::tcp::socket sock(io_service);   
boost::array<char, 4096> buffer;   

void read_handler(const boost::system::error_code &ec, std::size_t bytes_transferred)   
{   
	if (!ec)  
	{   
		std::cout << std::string(buffer.data(), bytes_transferred) << std::endl;   
		sock.async_read_some(boost::asio::buffer(buffer), read_handler);   
	}   
}   

void connect_handler(const boost::system::error_code &ec)   
{   
	if (!ec)   
	{   
		boost::asio::write(sock, boost::asio::buffer("GET / HTTP 1.1\r\nHost: highscore.de\r\n\r\n"));   
		sock.async_read_some(boost::asio::buffer(buffer), read_handler);   
	}   
}   

void resolve_handler(const boost::system::error_code &ec, boost::asio::ip::tcp::resolver::iterator it)   
{    
	if (!ec)   
	{    
		sock.async_connect(*it, connect_handler);    
	}   
}   

int main()   
{   
	boost::asio::ip::tcp::resolver::query query("www.highscore.de", "80");   //参数1为网址，参数2为通用端口  
	resolver.async_resolve(query, resolve_handler);
	io_service.run();   
}   
```   
这个程序最明显的部分是三个句柄的使用：connect\_handler() 和 read\_handler() 函数会分别在连接被建立后以及接收到数据后被调用。 那么为什么需要 resolve\_handler() 函数呢？   
### resolver对象
互联网使用了所谓的IP地址来标识每台PC。 IP地址实际上只是一长串数字，难以记住。 而记住象 www.highscore.de 这样的名字就容易得多。 为了在互联网上使用类似的名字，需要通过一个叫作域名解析的过程将它们翻译成相应的IP地址。    
这个过程由所谓的域名解析器来完成，对应的 I/O 对象是：boost::asio::ip::tcp::resolver。   
由于域名解析不是发生在本地的，所以它也被实现为一个异步操作。 一旦域名解析成功或被某个错误中断，resolve_handler() 函数就会被调用。   
resolver对象需要io_service进行初始化。asio的所有对象都需要io_service进行初始化。   
```c
boost::asio::ip::tcp::resolver resolver(io_service);    
```  
开始执行后，该应用将创建一个类型为 boost::asio::ip::tcp::resolver::query 的对象 query，表示一个查询，其中含有名字 www.highscore.de 以及互联网常用的端口80。 这个查询被传递给 async\_resolve() 方法以解析该名字。   
在域名解析后，函数resolver对象的随即调用了之前传入名称的connect\_handler函数，然后在函数中调用socket对象的成员函数async\_connect进行连接。   
### socket对象及async\_connect函数
socket对象也需要参数io\_service进行初始化。   
```c
boost::asio::ip::tcp::socket sock(io_service);    
```  
async\_connect是socket的成员函数之一。   
在域名解析后，resolve_handler将解析的内容传入async\_connect函数的第一个参数，同时传入connect\_handler函数名，当连接成功或者失败后进行调用。   
### async\_read\_some
async\_read\_some也是socket对象的成员函数。   
当连接成功后，之前传入名称的函数connect_handler被调用，其中socket对象的async\_read\_some被相继调用来独去数据。  
同时我们能发现async\_read\_some函数的第一个参数是接收数据的缓冲区，而第二个参数为read\_handler函数名。   
```c
sock.async_read_some(boost::asio::buffer(buffer), read_handler);    
```   
而read\_handler函数中，调用的仍然是socket对象的async\_read\_some函数。   
```c
void read_handler(const boost::system::error_code &ec, std::size_t bytes_transferred)  
{  
	if (!ec)  
	{   
		std::cout << std::string(buffer.data(), bytes_transferred) << std::endl;   
		sock.async_read_some(boost::asio::buffer(buffer), read_handler);  
	}  
}  
```   
read\_handler()在将数据写出至std::cout之后，会再次调用 async\_read\_some()方法。这是必需的，因为无法保证仅在一次异步操作中就可以接收到整个网页。async\_read\_some()和read\_handler()的交替调用只有当连接被破坏时才中止，如当web服务器已经传送完整个网页时。这种情况下，在read\_handler()内部将报告一个错误，以防止进一步将数据输出至标准输出流，以及进一步对该socket调用async\_read()方法。这时该例程将停止，因为没有更多的异步操作了。   
### 服务器端
下面的例子则示范了一个简单的 web 服务器。 其主要差别在于，这个应用不会连接至其它PC，而是等待连接。  
```c
#include <boost/asio.hpp>   
#include <string>     

boost::asio::io_service io_service;   
boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), 80);    
boost::asio::ip::tcp::acceptor acceptor(io_service, endpoint);    
boost::asio::ip::tcp::socket sock(io_service);   
std::string data = "HTTP/1.1 200 OK\r\nContent-Length: 13\r\n\r\nHello, world!";   

void write_handler(const boost::system::error_code &ec, std::size_t bytes_transferred)   
{  
}  

void accept_handler(const boost::system::error_code &ec)   
{  
	if (!ec)   
	{    
		boost::asio::async_write(sock, boost::asio::buffer(data), write_handler);   
	}   
}   

int main()   
{   
	acceptor.listen();   
	acceptor.async_accept(sock, accept_handler);   
	io_service.run();   
}    
```   
### acceptor对象
类型为boost::asio::ip::tcp::acceptor的I/O对象acceptor-被初始化为指定的协议和端口号，用于等待从其它PC传入的连接。 初始化工作是通过 endpoint 对象完成的，该对象的类型为 boost::asio::ip::tcp::endpoint，将本例子中的接收器配置为使用端口80来等待 IP v4 的传入连接，这是 WWW 通常所使用的端口和协议。   
接收器初始化完成后，main() 首先调用 listen() 方法将接收器置于接收状态，然后再用 async\_accept() 方法等待初始连接。 用于发送和接收数据的 socket 被作为第一个参数传递。   
当一个PC试图建立一个连接时，accept\_handler() 被自动调用。 如果该连接请求成功，就执行自由函数 boost::asio::async\_write() 来通过 socket 发送保存在 data 中的信息。  
> boost::asio::ip::tcp::socket 还有一个名为 async\_write\_some() 的方法也可以发送数据；不过它会在发送了至少一个字节之后调用相关联的句柄。 该句柄需要计算还剩余多少字节，并反复调用 async\_write\_some() 直至所有字节发送完毕。  
   
而使用  boost::asio::async\_write() 可以避免这些，因为这个异步操作仅在缓冲区的所有字节都被发送后才结束。  
在这个例子中，当所有数据发送完毕，空函数 write\_handler() 将被调用。 由于所有异步操作都已完成，所以应用程序终止。 与其它PC的连接也被相应关闭。