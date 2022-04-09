package main

func main() {
	var x int32
	println(x)
	x = 10
	println(x)
	x += 2
	println(x)
	x -= 3
	println(x)
	x *= 4
	println(x)
	x /= 5
	println(x)
	x %= 6
	println(x)

	var yy float32 = 3.14
	println(yy)
	yy = 10.4
	println(yy)
	yy += 2.0
	println(yy)
	yy -= 3.0
	println(yy)
	yy *= 4.0
	println(yy)
	yy /= 5.0
	println(yy)

	var s string
	println(s)
	s = "Hello"
	println(s)

	var bbb bool = false
	println(bbb)
	bbb = true
	println(bbb)
}