package main

func foo() {
	println("foo")
	return
}

func bar(x int32, y float32, g int32) int32 {
	var z int32 = x + int32(y)
	println(z)
	return z + 2
}

func main() {
	foo()
	foo()
	var x int32 = 88
	var result int32 = bar(x, 11.6, 8)
	println(result)
	foo()
	return
}