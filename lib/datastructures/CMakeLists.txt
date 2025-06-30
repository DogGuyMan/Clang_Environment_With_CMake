add_subdirectory(linkedlist)
add_subdirectory(vector)
add_subdirectory(stack)

# ─── 통합 데이터구조 라이브러리 생성 ──────────────────────────
add_library(datastructures STATIC
    # 각 서브 라이브러리들을 하나로 통합
    $<TARGET_OBJECTS:linkedlist>
    $<TARGET_OBJECTS:vector>
    $<TARGET_OBJECTS:stack>
)

# ─── 의존성 전파 ──────────────────────────
target_link_libraries(datastructures
    PUBLIC linkedlist vector stack
)


# ─── 헤더 파일 경로 설정 ──────────────────────────
target_include_directories(datastructures
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/linkedlist>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/vector>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/stack>
        $<INSTALL_INTERFACE:include>
)

# ─── 설치 설정 ──────────────────────────
if(LIBRARIES_ONLY)
    install(TARGETS datastructures linkedlist vector stack
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBRARY_PATH} # CMAKE_INSTALL_PREFIX (${sourceDir}/build_libraries/install)을 의미한다.
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBRARY_PATH} # CMAKE_INSTALL_PREFIX (${sourceDir}/build_libraries/install)을 의미한다.
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINARY_PATH} # CMAKE_INSTALL_PREFIX (${sourceDir}/build_libraries/install)을 의미한다.
    )

    install(FILES
        linkedlist/linkedlist.h
        vector/vector.h
        stack/stack.h
        DESTINATION include
    )
endif()
