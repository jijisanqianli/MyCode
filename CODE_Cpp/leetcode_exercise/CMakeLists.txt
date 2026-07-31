cmake_minimum_required(VERSION 4.2)
project(leetcode_exercise)

set(CMAKE_CXX_STANDARD 17)

# 核心代码：强制 GCC / MinGW 在编译时将字符串以 UTF-8 编码写入 exe
add_compile_options(-finput-charset=UTF-8)
add_compile_options(-fexec-charset=UTF-8)
