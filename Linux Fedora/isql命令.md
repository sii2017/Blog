## isql命令
isql可以与odbc进行交互式输入执行sql语句，并获取显示结果。     
> interactive sql  
  
### 用法
isql登陆数据库的用法只要由三个参数。  
isql [DSN] [username] [password] [options]       
通常输入上面的指令就可以登陆数据库了。   
随后可以使用sql中的各种命令，进行操作数据库。   
### 参数
常用的参数如下：   
-v 进verbose模式，如果出现错误会进行详细的描述，很适合debug的时候用。   
-k 使用SQLDriverConnect进行连接，可想而知如果不设置则默认为SQLConnect进行连接。   
-e 使用SQLExecDirect替代默认的Prepare。  
### 其他
更详细的引用可以使用man或者参考以下官方说明：   
https://www.mankier.com/1/isql