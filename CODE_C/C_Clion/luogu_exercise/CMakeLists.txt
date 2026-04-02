cmake_minimum_required(VERSION 4.1)
project(exercise C CXX)  # 同时支持 C 和 C++

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# 自动扫描 C 和 C++ 文件
file(GLOB SINGLE_FILES
        ${PROJECT_SOURCE_DIR}/src/*.c
        ${PROJECT_SOURCE_DIR}/src/*.cpp
)

foreach(SRC ${SINGLE_FILES})
    get_filename_component(TARGET_NAME ${SRC} NAME_WE)

    # 核心修复：自动判断是 C 还是 C++
    if(SRC MATCHES "\\.cpp$")
        add_executable(${TARGET_NAME} ${SRC})
        set_target_properties(${TARGET_NAME} PROPERTIES LINKER_LANGUAGE CXX)
    else()
        add_executable(${TARGET_NAME} ${SRC})
        set_target_properties(${TARGET_NAME} PROPERTIES LINKER_LANGUAGE C)
    endif()
endforeach()