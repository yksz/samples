def fibonacci
fibonacci = { x ->
    x <= 1 ? x : fibonacci(x-1) + fibonacci(x-2)
}.memoize()

for (i in 0..20)
    print fibonacci(i) + " "
println ""
