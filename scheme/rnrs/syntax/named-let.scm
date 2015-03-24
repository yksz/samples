(define (iota n)
  (let loop ((i (- n 1)) (ls '()))
    (if (< i 0)
      ls
      (loop (- i 1) (cons i ls)))))

(display (iota 10))
