add_subdirectory(linkedlist_demo)
add_subdirectory(vector_demo)
add_subdirectory(stack_demo)
add_subdirectory(queue_demo)

# 변수를 상위 스코프로 전달
set(PROJECT_DEMO_SOURCES    ${PROJECT_DEMO_SOURCES} PARENT_SCOPE)
set(PROJECT_DEMO_HEADERS    ${PROJECT_DEMO_HEADERS} PARENT_SCOPE)
set(PROJECT_DEMO_DIR        ${PROJECT_DEMO_DIR} PARENT_SCOPE)
