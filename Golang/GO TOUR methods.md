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
