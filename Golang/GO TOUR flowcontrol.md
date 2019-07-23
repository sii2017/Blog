## GO TOUR flowcontrol
> GO指南中flowcontrol部分   
   
主要内容为：   
> for   
switch   
defer   
### for
Go只有一种循环结构：for循环。   
基本的 for 循环由三部分组成，它们用分号隔开：   
初始化语句：在第一次迭代前执行   
条件表达式：在每次迭代前求值   
后置语句：在每次迭代的结尾执行   
初始化语句通常为一句短变量声明，该变量声明仅在 for 语句的作用域中可见。   
一旦条件表达式的布尔值为 false，循环迭代就会终止。   
注意：和 C、Java、JavaScript 之类的语言不同，Go 的 for 语句后面的三个构成部分外没有小括号， 大括号 { } 则是必须的。   
```
package main   
  
import (  
	"fmt"  
)   
   
func main() {   
	for i := 0; i < 10; i++ {  
		fmt.Printf("%d", i)   
	}  
}   
```    
与c相似的是，初始化语句和后置语句都是可选的。   
### for是Go中的while
当给for循环去掉分号，for就能在go中当作while来使用了。   
```
package main   
  
import (  
	"fmt"  
)   
  
func main() {   
	var i = 900  
	for i < 1000 {   
		fmt.Printf("%d\n", i)  
		i++  
	}   
}  
```   
### 无限循环
如果省略循环条件，该循环就不会结束。无限循环可以写的很紧凑。   
```
package main   
  
func main() {  
	for {  
	}  
}   
```   
### if
Go的if语句与for循环类似，表达式外无需小括号()，而大括号{}则是必须的。   
```
if x<10{  
	...   
}   
```
### if的简短语句
同for一样，if语句可以在条件表达式前执行一个简单的语句。   
该语句声明的变量作用域仅在 if 之内。    
```
if v := math.Pow(x, n); v < lim {   
	return v   
}  
```   
### if 和 else
在 if 的简短语句中声明的变量同样可以在任何对应的 else 块中使用。   
### switch
switch是编写一连串if - else语句的简便方法。它运行第一个值等于条件表达式的case语句。   
Go的switch语句类似于C、C++中的，不过Go只运行选定的case，而非之后所有的case。   
实际上，Go自动提供了在这些语言中每个case后面所需的break语句。    
除非以fallthrough语句结束，否则分支会自动终止。  
Go的另一点重要的不同在于switch的case无需为常量，且取值不必为整数。   
```
package main   
   
import (  
	"fmt"  
)   
 
func main() {   
	i := 3  
	for i >= 0 {   
		switch i {   
		case 3:   
			fmt.Printf("three\n")  
			i--   
		case 2:   
			fmt.Printf("two\n")    
			i--   
		case 1:    
			fmt.Printf("one\n")   
			i--   
		case 0:   
			fmt.Printf("zero\n")   
			i--  
		}   
	}  
}   
```  
switch 的 case 语句从上到下顺次执行，直到匹配成功时停止（即不再往下匹配）。    
### 没有条件的 switch
没有条件的 switch 同 switch true 一样。  
这种形式能将一长串 if-then-else 写得更加清晰。   
```
package main  
   
import (  
	"fmt"  
	"time"   
)   
   
func main() {   
	t := time.Now()   
	switch {   
	case t.Hour() < 12:   
		fmt.Println("Good morning!")  
	case t.Hour() < 17:    
		fmt.Println("Good afternoon.")   
	default:   
		fmt.Println("Good evening.")   
	}   
}   
```    
### defer
defer语句会将函数推迟到外层函数返回之后执行。    
推迟调用的函数其参数会立即求值，但直到外层函数返回前该函数都不会被调用。   
```
package main   
  
import (   
	"fmt"  
)    
   
func main() {  
	i := 3    
	for i >= 0 {    
		switch i {  
		case 3:    
			defer fmt.Printf("three\n")  
			i--   
		case 2:   
			fmt.Printf("two\n")   
			i--  
		case 1:    
			fmt.Printf("one\n")    
			i--   
		case 0:   
			fmt.Printf("zero\n")    
			i--  
		}   
	}   
	fmt.Printf("middle\n")  
}   
```   
注意，是推出到外层**函数**返回之后才执行，并不是循环或者大括号等。   
推迟的函数调用会被压入一个栈中。当外层函数返回时，被推迟的函数会按照**后进先出**的顺序调用。   