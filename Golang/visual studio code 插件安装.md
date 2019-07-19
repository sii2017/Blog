## visual studio code 插件安装
vscode开始配置起来很迅速，当真的开始写代码了以后发现经常会提示，某个command无效，需要安装某个插件，建议我install。  
当我们install以后会告诉我们failed，让人云里雾里……   
在我查阅了搜索引擎上大量的资料以后。终于搞懂了，但是其中错综复杂的关系，我想还是记录下来。   
### 这是些什么插件
这些插件是vscode使用的，其它编译器可能也是支持的（不确定）。   
这些插件的功能包括不限于，自动补全，自动补全未导入的包，当前文件中按符号搜索，重命名符号，查找所有引用组件等等等等。   
很多，就不一一详述了。   
这些插件属于一些辅助功能，可以帮助我们写代码的。每当vscode自己想用这些功能但是却没有找到相关的exe文件的时候，就会提示我们。   
### 为何总是install失败
timeout，由于网络的关系，即使是fq了，但是仍然会timeout。   
### 第一步
首先要先通过git clone的方式下载两个关键组件：tools和lint。   
实际上我也不确定这两个组件有什么用，但是根据目前有限的信息，之后要安装的一系列组件与他们都有着交错的关系，如果没有这俩组件，会影响到其它使用的组件的安装。   
于是  
```
git clone https://github.com/golang/tools.git   
git clone https://github.com/golang/lint.git   
```   
对了下载的位置也比较讲究，要在&GOPATH/src/golang.org目录下，分别建立（其实不用，下载下来就是）两个文件夹，tools和lint。   
克隆下来以后也不需要install或者build。   
个人判断之后安装的组件中有一部分会通过import引用到他们，因此他们俩本身是不需要编译的。   
### 第二步
tools和lint作为第一步的基础已经打好，可以分别或者一起安装其它的组件了。   
这些组件都存在于github上官方或者个人（sqs似乎是个人用户）的内容里。   
我们有两种方法。   
#### 失败率较高但是比较方便   
通过go get命令来获取。   
go get实际上是先download，然后go install的组合命令。   
比如安装gocode插件。   
```
go get -u -v github.com/nsf/gocode   
```   
这是代码自动补全插件。  
会开始进行下载，然后安装，自动安装，在bin中生成exe文件，那就安装成功了。  
但是经常会在download的过程中timeout。   
#### 手动下载并安装
通过git clone命令进行单独下载。   
```
git clone github.com/nsf/gocode   
```   
下载到$GOPATH/src/github.com目录下。   
下载完成以后使用go build命令进行编译。  
```
go build gocode   
```  
会在当前文件夹产生一个gocde.exe文件，然后把该文件移动到$GOPATH/bin下就可以了。   
### 解析原理
最后终于在搜索引擎上找到一篇文件。  
实际上vscode是调用bin中的插件exe文件，对代码进行一些优化和帮助的。  
所以我们做的没那么复杂，就是把内容下载下来并且使其变成二进制exe文件，放到bin下备用就行了。   
这就是最终的目的。   
关于各个组件的地址参考官网或者搜索引擎的博客吧，我就不抄一遍了。   