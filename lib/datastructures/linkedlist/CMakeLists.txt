message(STATUS "Start CMake linkedlist")
project(linkedlist)

add_library(linkedlist STATIC
    include/linkedlist.h
    src/linkedlist.c
)

target_include_directories(linkedlist
PUBLIC
    include
)

set(PROJECT_LIBRARIES ${PROJECT_LIBRARIES} linkedlist PARENT_SCOPE)

message(STATUS "Finish CMake linkedlist")
