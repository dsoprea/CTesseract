project(ctesseract_test)
#set(CMAKE_BUILD_TYPE Release)
set(CMAKE_BUILD_TYPE Debug)

# Required cmake version
cmake_minimum_required(VERSION 2.6.0)

#add_definitions(-g -Wall -Werror)
add_definitions(-Wall -Werror)
include_directories("../include")
link_directories("${CMAKE_CURRENT_SOURCE_DIR}/../build")

add_executable(ctesseract_test ctesseract_test.c)

target_link_libraries (ctesseract_test tesseract lept ctesseract)

