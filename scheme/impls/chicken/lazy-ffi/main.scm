#!/usr/bin/env csi -script

(require-extension lazy-ffi)

#~"libc.so.6"
#~"./libnewmath.so"

(#~printf "(add 1 2) => %d\n" (#~add 1 2 return: int:))
