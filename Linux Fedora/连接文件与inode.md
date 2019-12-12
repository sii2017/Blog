## 连接文件
Linux下的连接文件有两种，一种是hard link，一种是symbol link。   
其中symbol link与windows下的快捷方式类似，就是生成一个新的文件，指向源文件。   
而hard link则是linux独有的，它并不只是快捷方式的那种指向，而是实际是源文件本身。   
以下分开讲。   
### 命令ln
通过命令ln来生成连接文件。   
ln [-sf] 源文件 目标文件   
默认不带参数为hard link。   
如果带参乎上ln -s则是symbol link   
f参数是，如果目标文件存在，就将该目标文件删除后再创建。   
### hard link
hard link一开始可能比较难理解，如果会c++的话，我们可以理解为它与c++的引用类似，但是不完全一样。   
当我们操作hard link的时候，实际上在操作源文件吗，这与c++的引用相似。     
然而当我们删除hard link的时候，我们却并不会删除源文件。   
这是为什么？   
这里我们要说到inode了。   
#### inode
> 众所周知，在linux系统里，每个文件都对应一个inode号，而inode中则记录着指向文件实际内容的位置。   
> 当我们访问一个文件，那么就是通过对应的inode，来找到对应的存储内容。  
> 当我们删除一个文件，那么就没有文件对应这个inode了，也就没法再访问到这个文件的内容了。    
    
而hard link则是多个文件，对应着同一个inode号，并且对应着同一个文件内容。   
即使删除源文件，只要有一个hard link存在，那么就能通过hard link找到inode，来访问到文件内容。   
所以某种意义上来说，hard link可以使我们的文件更安全，即使误删除了某个关联文件，但是也可以通过其他hard link来访问。   
> 可以理解为，当我们访问源文件的时候，系统如此操作：   
> 从源文件找到inode，从inode找到文件实际位置，访问成功。   
> 当我们访问hard link的时候，系统如此：   
> 从hard link文件找到inode，从inode找到文件实际位置，访问成功。     
   
尽管他们的访问点不同，但是从inode开始，则都是相同的。   
#### ls
通过ls命令，我们可以清晰的看到hard link的性质。  
当我们使用ls -i的时候能看到文件对应的inode号以及该文件关联的inode数量。   
我们就可以看到源文件和所有相关的hard link文件的inode都是一致的，他们都关联同一个inode。   
同时，他们所有的详细信息都是一模一样的，除了文件名。   
以及，他们对应的inode数不再像普通文件一样是1，而是复数。   
![](https://github.com/sii2017/image/blob/master/hard%20link.jpg)   
### symbol link
symbol link就好理解多了，毕竟windows用了这么多年，就是一个快捷方式的概念。   
当我们使用ln命令加上-s命令后，就可以生成symbol link。   
与hard link不同，symbol link有着自己的inode，inode中记录着指向自己文件实际内容的位置，自己文件实际内容则记录着指向源文件的inode，再从源文件的inode访问到源文件的实际文件内容。   
> 换言之，当我们访问symbol link的时候，系统是这样操作的：  
> 先访问symbol link的inode，得到symbol link实际文件的位置，然后通过实际文件内的记录，找到源文件的inode号，再访问源文件的inode号，找到源文件实际存储的位置，最后访问到想要访问的内容。  
   
 
与hard link不同，它并不直接指向源文件的inode，只是间接访问。因此删掉symbol link不会对源文件造成任何影响。以及我们创建symbol，源文件inode关联数也不会增加。   
![](https://github.com/sii2017/image/blob/master/symbol%20link.jpg)   
当源文件被删除，则symbol link会失效，显示无法找到源文件，与windows的快捷方式一致。   