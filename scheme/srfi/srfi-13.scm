(use srfi-13)


;;; Predicates
(string? "") ; => #t
(string? 0)  ; => #f
(string-null? "")  ; => #t
(string-null? "a") ; => #f
(string-every #\a "aaa") ; => #t
(string-any #\a "abc") ; => #t


;;; Constructors
(make-string 3 #\a) ; => "aaa"
(string #\a #\b #\c) ; => "abc"
(string-tabulate (lambda (x) (integer->char (+ 97 x))) 3) ; => "abc"


;;; List & string conversion
(string->list "abc") ; => '(a b c)
(list->string '(#\a #\b #\c)) ; => "abc"
(reverse-list->string '(#\a #\b #\c)) ; => "cba"
(string-join '("foo" "bar" "baz") ":") ; => "foo:bar:baz"
(string-length "abc") ; => 3
(string-ref "abc" 1) ; => #\b
(string-copy "abc") ; => "abc"
(substring/shared "abcde" 2) ; ⇒> "cde"
(define s (string-copy "abcde"))
(string-copy! s 2 "ZZ") ; s => "abZZe"
(string-take "abcde" 2) ; => "ab"
(string-drop "abcde" 2) ; ⇒> "cde"
(string-take-right "abcde" 2) ; ⇒> "de"
(string-drop-right "abcde" 2) ; ⇒> "abc"
(string-pad     "325" 5) ; => "  325"
(string-pad   "71325" 5) ; => "71325"
(string-pad "8871325" 5) ; => "71325"
(string-pad-right "325"     5) ; => "325  "
(string-pad-right "71325"   5) ; => "71325"
(string-pad-right "8871325" 5) ; => "88713"
(string-trim       "   abc  ") ; ⇒> "abc  "
(string-trim-right "   abc  ") ; ⇒> "   abc"
(string-trim-both  "   abc  ") ; ⇒> "abc"
