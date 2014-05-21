class Console {
    def leftShift(str) {
        println "<< $str"
    }
    def rightShift(str) {
        println ">> $str"
    }
}

def console = new Console()
console << "a"
console >> "b"
