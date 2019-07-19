## 三种常用命令
在学习golang的过程中，遇见三种功能类似的常用命令。   
go build   
go install  
go get   
记录下来相关的内容以供参考。   
### go build   
**仅得到exe执行文件；仅产生在执行命令的当前文件夹**   
通过go build加上要编译的go源文件名，既可以在当前文件夹得到一个可执行文件，默认情况下该文件名为源文件名去掉go后缀，变成了exe。    
go build hello.go   
也可以通过-o选项来指定其它的名字    
go build -o mygo hello.go    
这种情况下生成的exe文件就是mygo.exe了   
我们可以不指定go源文件名字，直接在目录下直接执行go build命令，那么我们将在当前目录下得到一个与目录名同名的可执行文件。    
go build   
如果目录名字为hello，那么可执行文件就是hello.exe。   
### go install  
**生成exe执行文件在bin目录，以及生成静态链接库.a文件在pkg目录下。**    
**package main将不会生成静态库.a文件。**    
与build命令相比，install命令在编译源码后会将可执行文件或库文件安装到约定的目录下（bin）。   
go install不支持重命名-o，直接以其所在目录名命名   
go install将可执行文件安装到与src同级别的bin目录下，bin目录由go install自动创建。   
go install将可执行文件依赖的各种package编译后，以静态文件（.a）的方式放在与src同级别的pkg目录下   
### go get   
**先下载，然后调用go install**    
get命令通常用于下载并安装第三方插件。   
与install的区别在于，在install之前，先进行download。  
随后进行install的操作。   
get有三个附加参数。   
-v 显示操作流程的日志及信息，方便检查错误   
-u 下载丢失的包，但是不会更新已经存在的包   
-d 只下载不安装。    
-insecure 允许使用不安全的http方式进行下载操作   