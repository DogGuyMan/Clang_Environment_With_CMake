cmake_minimum_required(VERSION 3.14.0)
set(PROJECT_NAME clang-project)
project(${PROJECT_NAME} VERSION 1.0.0 LANGUAGES C)

# ─── 의존성 라이브러리 설정 ───────────────────────

# CMakePresets에 CMAKE_MODULE_PATH를 설정하지 않으면 cmake/*.cmake 파일을 찾을 수 없음

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(ClangStandard)

# ─── 실행 파일 생성 및 설정 ──────────────────────────
# Executable에 사용하는 Source들과 Header 모음

set(PROJECT_SOURCES)
set(PROJECT_HEADERS)
set(PROJECT_LIBRARIES)

message(STATUS "Before Enter lib Subdirectory")
add_subdirectory(lib)
message(STATUS "After Enter lib Subdirectory")

# ─── 설정한 Define 전처리 디버깅 ──────────────────────────

add_executable(${PROJECT_NAME}
    src/main.c
    ${PROJECT_SOURCES} ${PROJECT_HEADERS}
)

message(STATUS "PROJECT_LIBRARIES ${PROJECT_LIBRARIES}")

target_link_libraries(${PROJECT_NAME}
    ${PROJECT_LIBRARIES}
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_custom_target(run_with_leaks
        DEPENDS ${PROJECT_NAME}
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )
endif()
