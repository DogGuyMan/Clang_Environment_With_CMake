# https://libds.sourceforge.net/ 에서 다운받자.

# ─── libds.a가 없으면 빌드 ──────────────────────────
set(LIBDS_LIB_FILE "${CMAKE_CURRENT_SOURCE_DIR}/libds.a")
set(LIBDS_HEADER_FILE "${CMAKE_CURRENT_SOURCE_DIR}/ds.h")

if(NOT EXISTS ${LIBDS_LIB_FILE})
    message(STATUS "Building libds...")
    execute_process(
        COMMAND make gcc
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        RESULT_VARIABLE LIBDS_BUILD_RESULT
    )
    if(NOT LIBDS_BUILD_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to build libds")
    endif()
endif()

# ─── IMPORTED 라이브러리 생성 ──────────────────────────
add_library(LibDS::libds STATIC IMPORTED)

set_target_properties(LibDS::libds PROPERTIES
    IMPORTED_LOCATION ${LIBDS_LIB_FILE}
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}"
)

# ─── 설치 설정 ──────────────────────────
if(LIBRARIES_ONLY)
    # IMPORTED 타겟은 install(TARGETS ...)로 설치할 수 없음
    # 대신 install(FILES ...)로 직접 파일 복사
    install(FILES
        ${LIBDS_LIB_FILE}
        DESTINATION ${CMAKE_INSTALL_LIBRARY_PATH}
    )

    install(FILES
        ds.h
        local.h  # local.h도 필요할 수 있음
        DESTINATION include
    )
endif()
