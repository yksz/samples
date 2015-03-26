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

;;; Modification
(define s (string-copy "abc"))
(string-set! s 1 #\Z) ; s => "aZc"
(define s (make-string 3))
(string-fill! s #\Z) ; s => "ZZZ"

;;; Comparison
(string=  "abc" "abc") ; => #t
(string<> "abc" "def") ; => #t
(string<  "abc" "abd") ; => #t
(string>  "abc" "abb") ; => #t
(string<= "abc" "abc") ; => #t
(string>= "abc" "abc") ; => #t
(string-ci=  "ABC" "abc") ; => #t
(string-ci<> "ABC" "def") ; => #t
(string-ci<  "ABC" "abd") ; => #t
(string-ci>  "ABC" "abb") ; => #t
(string-ci<= "ABC" "abc") ; => #t
(string-ci>= "ABC" "abc") ; => #t

;;; Searching
(string-index "abcde" #\b) ; => 1
(string-index "abcde" #\b 3) ; => #f
(string-index-right "abcde" #\b) ; => 1
(string-index-right "abcde" #\f) ; => #f
(string-skip "  abcde" #\space) ; => 2
(string-skip-right "abcde  " #\space) ; => 4
(string-count "fizzbuzz" #\z) ; => 4
(string-contains "fizzbuzz" "zz") ; => 2
(string-contains-ci "FIZZBUZZ" "zz") ; => 2

;;; Prefixes & suffixes
(string-prefix-length "foo" "foobar") ; => 3
(string-prefix-length "bar" "foobar") ; => 0
(string-suffix-length "foo" "foobar") ; => 0
(string-suffix-length "bar" "foobar") ; => 3
(string-prefix-length-ci "foo" "FOOBAR") ; => 3
(string-prefix-length-ci "bar" "FOOBAR") ; => 0
(string-suffix-length-ci "foo" "FOOBAR") ; => 0
(string-suffix-length-ci "bar" "FOOBAR") ; => 3
(string-prefix? "foo" "foobar") ; => #t
(string-suffix? "bar" "foobar") ; => #t
(string-prefix-ci? "foo" "FOOBAR") ; => #t
(string-suffix-ci? "bar" "FOOBAR") ; => #t

;;; Alphabetic case mapping
(string-titlecase "abc") ; => "Abc"
(string-titlecase "123") ; => "123"
(string-upcase "abc") ; => "ABC"
(string-downcase "ABC") ; => "abc"

;;; Reverse & append
(string-reverse "abc") ; => "cba"
