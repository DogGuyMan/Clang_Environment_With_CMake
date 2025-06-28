cmake_minimum_required(VERSION 3.14.0)

# ─── 빌드 모드 확인 ──────────────────────────
option(LIBRARIES_ONLY "Build libraries only" OFF)

if(LIBRARIES_ONLY)
    set(PROJECT_NAME clang-libraries)
    message(STATUS "=== Building Libraries Only ===")
else()
    set(PROJECT_NAME clang-project)
    message(STATUS "=== Building Full Project ===")
endif()

project(${PROJECT_NAME} VERSION 1.0.0 LANGUAGES C)

# ─── 의존성 라이브러리 설정 ───────────────────────

# CMakePresets에 CMAKE_MODULE_PATH를 설정하지 않으면 cmake/*.cmake 파일을 찾을 수 없음
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
set(CMAKE_INSTALL_LIBRARY_PATH lib)
set(CMAKE_INSTALL_BINARY_PATH bin)

include(ClangStandard)

# ─── 실행 파일 생성 및 설정 ──────────────────────────
# Executable에 사용하는 Source들과 Header 모음

set(PROJECT_SOURCES)
set(PROJECT_HEADERS)

set(DEMO_DIR)
set(DEMO_SOURCES)
set(DEMO_HEADERS)


# ─── 서브 디렉토리 추가 ────────────────────────
add_subdirectory(lib/datastructures)

# ─── 프로젝트 빌드 (라이브러리가 아닌 경우만) ──────────────────────────
if(NOT LIBRARIES_ONLY)
    add_subdirectory(src)

    set(LIBRARY_INSTALL_DIR "${CMAKE_SOURCE_DIR}/build_libraries/install")
    set(LIBRARY_DEPS)

    include_directories(${LIBRARY_INSTALL_DIR}/include)
    link_directories(${LIBRARY_INSTALL_DIR}/lib)

    if(NOT EXISTS "${LIBRARY_INSTALL_DIR}/lib/liblinkedlist.a")
        message(FATAL_ERROR "라이브러리가 빌드되지 않았습니다. 먼저 ./shell/CMakeBuildLibraries.sh를 실행하세요.")
    else()
        set(LIBRARY_DEPS ${LIBRARY_DEPS} linkedlist)
    endif()

endif()

if(NOT LIBRARIES_ONLY)
    # 디버그 출력으로 변수 확인
    message(STATUS "PROJECT_SOURCES: ${PROJECT_SOURCES}")
    message(STATUS "PROJECT_HEADERS: ${PROJECT_HEADERS}")
    message(STATUS "DEMO_DIR: ${DEMO_DIR}")

    # Executable에 사용하는 Source들과 Header 모음
    add_executable(${PROJECT_NAME}
        app/main.c
        ${PROJECT_SOURCES}
    )

    target_include_directories(${PROJECT_NAME}
        PRIVATE ${PROJECT_DEMO_DIR}
    )

    target_link_libraries(${PROJECT_NAME}
        ${LIBRARY_DEPS}
    )

    message(STATUS "=== Project Configuration Complete ===")
endif()
