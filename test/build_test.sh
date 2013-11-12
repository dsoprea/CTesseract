#!/bin/sh

g++ -g -o test \
    ctess_main.cpp \
    ctess_page_iterator.cpp ctess_mr_iterator.cpp ctess_string.cpp \
    test.cpp \
\
    -ltesseract -llept \

