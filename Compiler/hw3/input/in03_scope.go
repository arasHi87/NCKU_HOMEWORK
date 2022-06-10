package main

func main() {
    var height int32 = 99
    {
        var width float32 = 3.14
        println(width)
        println(height)
    }
    var length float32
    {
        var length string = "hello world"
        {
            var length bool  = true
            println(length)
        }
        println(length)
    }
    println(length)
}