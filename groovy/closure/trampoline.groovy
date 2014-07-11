def fact
fact = { n, total ->
    n == 0 ? total : fact.trampoline(n - 1, n * total)
}.trampoline()

def factorial = { n -> fact(n, 1G)}
assert factorial(20) == 2432902008176640000
