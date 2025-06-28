add_library(linkedlist STATIC
    linkedlist.h
    linkedlist.c
)

if(LIBRARIES_ONLY)
    # ─── 라이브러리 전용 빌드 시 설치 설정 ──────────────────────────
    install(TARGETS linkedlist
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBRARY_PATH} # CMAKE_INSTALL_PREFIX (${sourceDir}/build_libraries/install)을 의미한다.
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBRARY_PATH} # CMAKE_INSTALL_PREFIX (${sourceDir}/build_libraries/install)을 의미한다.
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINARY_PATH} # CMAKE_INSTALL_PREFIX (${sourceDir}/build_libraries/install)을 의미한다.
    )

    # 헤더 파일 설치
    install(FILES
        linkedlist.h
        DESTINATION include
    )

    return()  # 라이브러리만 빌드하고 종료
endif()

message(STATUS "=== Libraries Configuration Complete ===")
