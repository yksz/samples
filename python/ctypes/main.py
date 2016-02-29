#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import ctypes
import sys

if sys.platform.startswith('cygwin'):
    newmath = ctypes.CDLL("./newmath.dll")
elif sys.platform.startswith('darwin'):
    newmath = ctypes.CDLL("./libnewmath.dylib")
elif sys.platform.startswith('linux'):
    newmath = ctypes.CDLL("./libnewmath.so")
else:
    print("Could not load 'newmath' library")
    sys.exit(1)

print("(add 1 2) => {}".format(newmath.add(1, 2)))
