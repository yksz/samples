import static groovyx.gpars.actor.Actors.actor

def console = actor {
    loop {
        react { message ->
            switch (message) {
                case "stop":
                    stop()
                    break
                default:
                    println message
            }
        }
    }
}

console.send "msg1"
console << "msg2"
console "stop"
console.join()
