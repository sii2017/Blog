## GO TOUR methods
> GO指南中methods部分   
  
### 方法
Go 没有类。不过你可以为结构体类型定义方法。   
方法就是一类带特殊的**接收者**参数的函数。   
方法接收者在它自己的参数列表内，位于 func 关键字和方法名之间。   
在此例中，Abs 方法拥有一个名为 v，类型为 Vertex 的接收者。    
```
type Vertex struct {  
	X, Y float64  
}    

func (v Vertex) Abs() float64 {   
	return math.Sqrt(v.X*v.X + v.Y*v.Y)   
}   
  
func main() {   
	v := Vertex{3, 4}   
	fmt.Println(v.Abs())   
}    
```    
> 记住：方法只是个带接收者参数的函数。   
   
以下这个Abs的写法就是个正常的函数，然而功能并没有什么变化。   
```
type Vertex struct {  
	X, Y float64   
}   

func Abs(v Vertex) float64 {  
	return math.Sqrt(v.X*v.X + v.Y*v.Y)   
}  

func main() {  
	v := Vertex{3, 4}   
	fmt.Println(Abs(v))   
}   
```   
以上例子用的是结构体作为接收者。
**实际上我们可以为非结构体类型声明方法。**   
在此例中，我们看到了一个带 Abs 方法的数值类型 MyFloat。   
```
type MyFloat float64   

func (f MyFloat) Abs() float64 {   
	if f < 0 {  
		return float64(-f)   
	}  
	return float64(f)   
}   

func main() {   
	f := MyFloat(-math.Sqrt2)  
	fmt.Println(f.Abs())  
}   
```
你只能为在同一包内定义的类型的接收者声明方法，而不能为其它包内定义的类型（包括 int 之类的内建类型）的接收者声明方法。   
> 显然可以通过type，给基础类型取别名，来实现方法。   
   
### 指针接收者
你可以为指针接收者声明方法。  
这意味着对于某类型 T，接收者的类型可以用 \*T 的文法。（此外，T 不能是像 \*int 这样的指针。）  
例如，这里为 *Vertex 定义了 Scale 方法。   
```
func (v *Vertex) Scale(f float64) {   
	v.X = v.X * f  
	v.Y = v.Y * f  
}   
```   
指针接收者的方法可以修改接收者指向的值（就像 Scale 在这做的）。由于方法经常需要修改它的接收者，指针接收者比值接收者更常用。     
若使用值接收者，那么 Scale 方法会对原始 Vertex 值的副本进行操作。（对于函数的其它参数也是如此。）Scale 方法必须用指针接受者来更改 main 函数中声明的 Vertex 的值。   
### 方法与指针重定向
带指针参数的函数必须接受指针为实参，如果实参为普通变量则会产生编译错误。   
```
var v Vertex  
ScaleFunc(v, 5)  // 编译错误！   
ScaleFunc(&v, 5) // OK    
```   
而以指针为接收者的方法被调用时，接收者**既能为值又能为指针**：   
```
var v Vertex   
v.Scale(5)  // OK  
p := &v   
p.Scale(10) // OK  
```     
对于语句 v.Scale(5)，即便 v 是个值而非指针，带指针接收者的方法也能被直接调用。 也就是说，由于 Scale 方法有一个指针接收者，为方便起见，Go 会将语句 v.Scale(5) 解释为 (&v).Scale(5)。   
**同样的事情也发生在相反的方向。**   
接受一个值作为参数的函数必须接受一个指定类型的值，否则会发生编译错误。   
```
var v Vertex   
fmt.Println(AbsFunc(v))  // OK  
fmt.Println(AbsFunc(&v)) // 编译错误！  
```   
而以值为接收者的方法被调用时，接收者既能为值又能为指针：   
```
var v Vertex  
fmt.Println(v.Abs()) // OK  
p := &v   
fmt.Println(p.Abs()) // OK   
```  
这种情况下，方法调用 p.Abs() 会被解释为 (*p).Abs()。    
### 选择值或指针作为接收者
使用指针接收者的原因有二：   
首先，方法能够修改其接收者指向的值。  
其次，这样可以避免在每次调用方法时复制该值。若值的类型为大型结构体时，这样做会更加高效。   
> 这就和c的引用相似，提高效率。但是需要注意的是，要避免不小心改变原始值，如果在不需要改变的时候。   
   
### 接口
接口类型是由一组方法签名定义的集合。   
或者可以说，   
接口是一组仅包含方法名、参数、返回值的未具体实现的方法的集合。   
接口类型的变量可以保存任何实现了这些方法的（接口）值。   
```
package main  

import "fmt"   

//声明一个接口，其中包含一个方法call   
type Phone interface {   
    call()  
}   

//任意类型都可以实现接口，比如这个类型   
type NokiaPhone struct {   
}   

//任意类型都可以实现接口，只要这个类型的方法与接口类型的方法一致，即称为该类型实现了该接口   
func (nokiaPhone NokiaPhone) call() {   
    fmt.Println("I am Nokia, I can call you!")   
}  

//任意类型都可以实现接口   
type ApplePhone struct {   
}   

//同上，只要这个类型的方法与接口类型的方法一直，即称该类型实现了该接口  
func (iPhone ApplePhone) call() {  
    fmt.Println("I am Apple Phone, I can call you!")   
}   

func main() {   
    var phone Phone  //声明一个接口变量  
	//将实现了该接口的类型变量赋值给该接口   
    phone = new(NokiaPhone)   
	//该接口即可调用该类型的方法  
    phone.call()   

    phone = new(ApplePhone)  
    phone.call()   
}  
```     
### 接口与隐式实现
类型通过实现一个接口的所有方法来实现该接口。既然无需专门显式声明，也就没有“implements”关键字。   
隐式接口从接口的实现中解耦了定义，这样接口的实现可以出现在任何包中，无需提前准备。   
因此，也就无需在每一个实现上增加新的接口名称，这样同时也鼓励了明确的接口定义。   
### 接口值
接口也是值。它们可以像其它值一样传递。  
接口值可以用作函数的参数或返回值。  
在内部，接口值可以看做包含**值**和**具体类型**的元组：  
（value，type）   
接口值保存了一个具体底层类型的具体值。  
接口值调用方法时会执行其底层类型的同名方法。   
```
package main   
  
import (  
	"fmt"   
	"math"   
)  
   
//声明接口   
type I interface {   
	M()  
}   
   
type T struct {  
	S string   
}  
  
//类型通过定义方法来实现接口   
func (t *T) M() {   
	fmt.Println(t.S)   
}    

func main() {  
	var i I  

	i = &T{"Hello"}  
	describe(i)  
	i.M()   
}   

func describe(i I) {   
	fmt.Printf("(%v, %T)\n", i, i)  //输出为(&{Hello}, *main.T)    
}   
```  
> %v，按值的本来值输出。   
> %T，输出 Go 语言语法格式的类型和值。   
   
### 底层值为 nil 的接口值
即便接口内的具体值为 nil，方法仍然会被 nil 接收者调用。   
在一些语言中，这会触发一个空指针异常，但在 Go 中通常会写一些方法来优雅地处理它（如本例中的 M 方法）。   
```
package main  
  
import "fmt"  
  
type I interface {  
	M()  
}  
  
type T struct {   
	S string  
}  
  
func (t *T) M() {  
	//优雅的方法就是预先判断并返回   
	if t == nil {   
		fmt.Println("<nil>")  
		return   
	}  
	fmt.Println(t.S)   
}   
  
func main() {  
	var i I  

	var t *T  
	i = t  
	describe(i)   
	i.M()  
   
	i = &T{"hello"}  
	describe(i)   
	i.M()  
}  
   
func describe(i I) {   
	fmt.Printf("(%v, %T)\n", i, i)  
}  
```   
注意: 保存了 nil 具体值的接口其自身并不为 nil。   
### nil 接口值
nil 接口值既不保存值也不保存具体类型。   
为 nil 接口调用方法会产生运行时错误，因为接口的元组内并未包含能够指明该调用哪个 具体 方法的类型。   
```
package main  

import "fmt"  

type I interface {  
	M()  
}  

func main() {   
	var i I  
	describe(i)    //会跳运行错误  
	i.M()  
}   

func describe(i I) {  
	fmt.Printf("(%v, %T)\n", i, i)   
}  
```
### 空接口
指定了零个方法的接口值被称为空接口：   
```  
var i interface{}   
```
空接口可保存任何类型的值。（**因为每个类型都至少实现了零个方法。**）   
空接口被用来处理未知类型的值。例如，fmt.Print 可接受类型为 interface{} 的任意数量的参数。   
```
package main  
  
import "fmt"  
   
func main() {  
	var i interface{}   
	describe(i)  	//(<nil>, <nil>)   
   
	i = 42   
	describe(i)  	//(42, int)   
   
	i = "hello"  
	describe(i)   //(hello, string)   
}   
   
func describe(i interface{}) {  
	fmt.Printf("(%v, %T)\n", i, i)   
}  
```   
### 类型断言
类型断言 提供了访问接口值底层具体值的方式。   
```
t:= i.(T)   
```   
该语句断言接口值 i 保存了具体类型 T，并将其底层类型为 T 的值赋予变量 t。   
若 i 并未保存 T 类型的值，该语句就会触发一个恐慌（panic）。   
这显然不太好，万一哪里传值传错了，处罚恐慌影响整个程序运行了，所以，为了 判断 一个接口值是否保存了一个特定的类型，类型断言可返回两个值：其底层值以及一个报告断言是否成功的布尔值。    
```
t, ok := i.(T)  
```   
若 i 保存了一个 T，那么 t 将会是其底层值，而 ok 为 true。   
如果接口i没有保存T类型的值，ok 将为 false 而 t 将为 T 类型的零值，**程序并不会产生恐慌**。   
请注意这种语法和读取一个映射时的相同之处。   
```
package main  

import "fmt"   

func main() {  
	var i interface{} = "hello"   

	s := i.(string)  
	fmt.Println(s)  

	s, ok := i.(string)  
	fmt.Println(s, ok)  

	f, ok := i.(float64)  
	fmt.Println(f, ok)   

	f = i.(float64) // 报错(panic) 
	fmt.Println(f)    
}  
```  
### 类型选择
类型选择 是一种按顺序从几个类型断言中选择分支的结构。   
类型选择与一般的 switch 语句相似，不过类型选择中的 case 为类型（而非值）， 它们针对给定接口值所存储的值的类型进行比较。   
```
switch v := i.(type) {   
case T:   
    // v 的类型为 T  
case S:  
    // v 的类型为 S  
default:   
    // 没有匹配，v 与 i 的类型相同  
}  
```  
类型选择中的声明与类型断言 i.(T) 的语法相同，只是具体类型 T 被替换成了关键字 type。   
此选择语句判断接口值 i 保存的值类型是 T 还是 S。在 T 或 S 的情况下，变量 v 会分别按 T 或 S 类型保存 i 拥有的值。在默认（即没有匹配）的情况下，变量 v 与 i 的接口类型和值相同。  
```
package main  

import "fmt"  

func do(i interface{}) {  
	switch v := i.(type) {  
	case int:  
		fmt.Printf("Twice %v is %v\n", v, v*2)  
	case string:   
		fmt.Printf("%q is %v bytes long\n", v, len(v))  
	default:   
		fmt.Printf("I don't know about type %T!\n", v)   
	}  
}   

func main() {  
	do(21)  
	do("hello")  
	do(true)   
}  
```  
> 不过这个v是什么类型，倒是让人好奇。   
   
### Stringer
fmt 包中定义的 Stringer 是最普遍的接口之一。   
意味着任意类型只要实现了String这个方法，即可调用这个接口来输出内容。   
```
type Stringer interface {  
    String() string   
}  
```  
Stringer 是一个可以用字符串描述自己的类型。fmt 包（还有很多包）都通过此接口来打印值。   
### 错误（接口）
Go 程序使用 error 值来表示错误状态。  
与 fmt.Stringer 类似，error 类型是一个内建接口：   
```
type error interface {  
    Error() string   
}   
``` 
（与 fmt.Stringer 类似，fmt 包在打印值时也会满足 error。）   
通常函数会返回一个 error 值，调用的它的代码应当判断这个错误是否等于 nil 来进行错误处理。   
```
i, err := strconv.Atoi("42")  
if err != nil {   
    fmt.Printf("couldn't convert number: %v\n", err)    
    return  
}   
fmt.Println("Converted integer:", i)   
``` 
error 为 nil 时表示成功；非 nil 的 error 表示失败。    
```
package main   

import (  
	"fmt"  
	"time"  
)  

type MyError struct {  
	When time.Time  
	What string  
}   

//通过实现error接口里的函数Error，来实现error这个接口   
func (e *MyError) Error() string {   
	return fmt.Sprintf("at %v, %s",
		e.When, e.What)   
}    

//这里的error是接口，接口可以作为返回值   
func run() error {
	return &MyError{
		time.Now(),
		"it didn't work",
	}
}

func main() {
	if err := run(); err != nil {
		fmt.Println(err)
	}
}
```
### Reader
io 包指定了 io.Reader 接口，它表示从数据流的末尾进行读取。   
Go 标准库包含了该接口的许多实现，包括文件、网络连接、压缩和加密等等。   
io.Reader 接口有一个 Read 方法：   
```
func (T) Read(b []byte) (n int, err error)   
```
Read 用数据填充给定的字节切片并返回填充的字节数和错误值。在遇到数据流的结尾时，它会返回一个 io.EOF 错误。   
示例代码创建了一个 strings.Reader 并以每次 8 字节的速度读取它的输出。   