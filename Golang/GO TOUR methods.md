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
