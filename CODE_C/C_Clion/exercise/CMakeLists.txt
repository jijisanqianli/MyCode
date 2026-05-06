cmake_minimum_required(VERSION 4.1)
project(exercise C)

# 配置C11标准
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
# 所有exe输出到bin目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# -------------------------- 1. 单文件题目（src/下）--------------------------
# 自动扫描src下所有.c文件，生成独立exe
file(GLOB SINGLE_FILES ${PROJECT_SOURCE_DIR}/src/*.c)
foreach(SRC ${SINGLE_FILES})
    get_filename_component(TARGET_NAME ${SRC} NAME_WE)
    add_executable(${TARGET_NAME} ${SRC})
    # 强制指定C语言（避免中文/解析问题）
    set_target_properties(${TARGET_NAME} PROPERTIES LINKER_LANGUAGE C)
endforeach()

# -------------------------- 2. 多文件模块（modules/下）--------------------------
#一：
# 顺序表模块：编译test_seqlist.exe
add_executable(test_seqlist
        modules/seqlist/test_seqlist.c
        modules/seqlist/seqlist.c
)
# 告诉编译器头文件路径（找到seqlist.h）
target_include_directories(test_seqlist PRIVATE modules/seqlist)
# 强制指定C语言
set_target_properties(test_seqlist PROPERTIES LINKER_LANGUAGE C)


#二：
add_executable(seqlist_exercise_test
        modules/seqlist_exercise/seqlist_exercise_test.c
        modules/seqlist_exercise/odd_even.c
        modules/seqlist_exercise/del_dupnum.c
        modules/seqlist_exercise/del_x2y.c
        modules/seqlist_exercise/set_seqlist.c
)
# 告诉编译器头文件路径（找到seqlist.h）
target_include_directories(seqlist_exercise_test PRIVATE modules/seqlist_exercise)
# 强制指定C语言
set_target_properties(seqlist_exercise_test PROPERTIES LINKER_LANGUAGE C)

#三：linked_list_exercise
add_executable(linked_list_exercise_test
        modules/linked_list_exercise/basic_linked_list_function.c
        modules/linked_list_exercise/linked_list_exercise_test.c
        modules/linked_list_exercise/lnk_merge.c
        modules/linked_list_exercise/lnk_del_x2y.c
)
# 告诉编译器头文件路径（找到seqlist.h）
target_include_directories(linked_list_exercise_test PRIVATE modules/linked_list_exercise)
# 强制指定C语言
set_target_properties(linked_list_exercise_test PROPERTIES LINKER_LANGUAGE C)

#四：linked_list_exercise
add_executable(queue_exercise_test
        modules/queue_exercise/queue_exercise_test.c
        modules/queue_exercise/circle_linked_list.c
        modules/queue_exercise/stack.c
        modules/queue_exercise/stack_compute.c
)
# 告诉编译器头文件路径（找到seqlist.h）
target_include_directories(queue_exercise_test PRIVATE modules/queue_exercise)
# 强制指定C语言
set_target_properties(queue_exercise_test PROPERTIES LINKER_LANGUAGE C)

add_executable(tree_exercise_test
        modules/tree_exercise/tree_exercise_test.c
        modules/tree_exercise/stack_example.c
        modules/tree_exercise/pre_order.c
        modules/tree_exercise/path.c
)
# 告诉编译器头文件路径（找到seqlist.h）
target_include_directories(tree_exercise_test PRIVATE modules/tree_exercise)
# 强制指定C语言
set_target_properties(tree_exercise_test PROPERTIES LINKER_LANGUAGE C)

# 后续加其他模块（比如链表），复制下面模板即可：
# add_executable(test_linklist
#     modules/linklist/test_linklist.c
#     modules/linklist/linklist.c
# )
# target_include_directories(test_linklist PRIVATE modules/linklist)
# set_target_properties(test_linklist PROPERTIES LINKER_LANGUAGE C)