#!/bin/sh

g++ -shared -Wl,-soname,ctesseract.so.1 -fPIC -g -o ctesseract.so.1.0 \
    ctess_main.cpp \
    ctess_page_iterator.cpp ctess_mr_iterator.cpp ctess_string.cpp \
\
    -ltesseract -llept \

