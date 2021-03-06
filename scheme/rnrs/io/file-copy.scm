(define port-copy
  (lambda (iport oport)
    (define (iter c)
      (unless (eof-object? c)
        (write-char c oport)
        (iter (read-char iport))))
    (iter (read-char iport))))

(define file-copy
  (lambda (src dst)
    (let ((iport (open-input-file src))
          (oport (open-output-file dst)))
      (port-copy iport oport)
      (close-input-port iport)
      (close-output-port oport))))


(let ((args (command-line)))
  (when (<= (length args) 2)
    (display "usage: copy <src> <dst>")
    (newline)
    (exit 1))
  (let ((src (list-ref args 1))
        (dst (list-ref args 2)))
    (file-copy src dst)))
