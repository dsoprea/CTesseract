project(ctesseract)
#set(CMAKE_BUILD_TYPE Release)
set(CMAKE_BUILD_TYPE Debug)

# Required cmake version
cmake_minimum_required(VERSION 2.6.0)

#add_definitions(-g -Wall -Werror)
add_definitions(-Wall -Werror)
include_directories("include")

add_library(
    ctesseract SHARED

    ctess_main.cpp
    ctess_page_iterator.cpp ctess_mr_iterator.cpp ctess_string.cpp
)

target_link_libraries (ctesseract tesseract lept)

SET_TARGET_PROPERTIES(
    ctesseract
    PROPERTIES
        VERSION 1.0.1
        SOVERSION 1.0.0
)

install(TARGETS ctesseract
        LIBRARY DESTINATION lib)

