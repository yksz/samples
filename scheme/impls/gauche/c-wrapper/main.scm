(use c-wrapper)

(c-load "stdio.h")
(c-load "newmath.h"
        :libs "-L. -lnewmath")

(printf "(add 1 2) => %d\n" (add 1 2))
