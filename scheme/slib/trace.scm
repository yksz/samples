(require 'trace)

(define fib
  (lambda (n)
    (if (<= n 2)
        1
        (+ (fib (- n 1)) (fib (- n 2))))))

(trace fib)
(fib 5)
