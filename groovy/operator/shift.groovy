class Hoge {
    def leftShift(str) {
        println "leftShift: $str"
    }
    def rightShift(str) {
        println "rightShift: $str"
    }
}

def hoge = new Hoge()
hoge << "a"
hoge >> "b"
