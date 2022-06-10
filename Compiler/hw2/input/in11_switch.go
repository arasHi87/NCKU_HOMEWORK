package main

func main() {
    var num int32 = 11

    switch num {
		case 0: {
			println("A")
		}
		case 1: {
			println("B")
		}
		case 2: {
			println("C")
		}
		case 3: {
			println("D")
		}
		default: {
			println(num)
		}
    }

    switch num {
		case 10: {
			println("A")
		}
		case 11: {
			println("B")
		}
		case 12: {
			println("C")
		}
		case 13: {
			println("D")
		}
		default: {
			println(num)
		}
    }
}