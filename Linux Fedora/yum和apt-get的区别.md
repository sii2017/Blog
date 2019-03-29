## yum和apt-get的区别
rpm包和deb包是两种Linux系统下最常见的安装包格式。   
rpm包主要应用在RedHat系列包括：Fedora等发行版的Linux系统上。    
deb包主要应用于Debian系列包括现在比较流行的Ubuntu等发行版上。    
通常我们如果要安装现成的这两种包的话，安装rpm包的命令是“rpm -参数”，安装deb包的命令是“dpkg -参数”。而Linux系统很方便和人性化的一点就是很多软件或服务根本就不用我们去下载，直接使用相应的命令就可以管理了。   
**yum可以用于运作rpm包，例如在Fedora系统上对某个软件的管理：**   
安装：yum install &lt;packag\_name&gt;   
卸载：yum remove &lt;package\_name&gt;   
更新：yum update &lt;package\_name&gt;  
**apt-get可以用于运作deb包，例如在Ubuntu系统上对某个软件的管理：**   
安装：apt-get install &lt;package\_name&gt;  
卸载：apt-get remove &lt;package\_name&gt;   
更新：apt-get update &lt;package\_name&gt;   