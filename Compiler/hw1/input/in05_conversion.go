package main

func main() {
	var x int32 = 3
	var y float32 = 3.14
	var z1 int32
	var z2 float32
	z1 = x + int32(y)
	z2 = float32(x) + y
	println(z1)
	println(z2)
	z1 = x + int32(6.28)
	z2 = float32(6) + y
	println(z1)
	println(z2)
}