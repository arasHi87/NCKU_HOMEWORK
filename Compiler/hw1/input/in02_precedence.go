package main

func main() {
	println(3 - 4 * (+5 + -8) - 10 / 7)
	println(3 - 4 * (+5 + -8) - 10 / 7 > -4 % 3 || !true && !!false)
	println(3.0 - 4.0 * (+5.0 + -8.0) - 10.0 / 7.0)
	print(3.0 - 4.0 * (+5.0 + -8.0) - 10.0 / 7.0 > -4.0 || !true && !!false)
}