add_subdirectory(datatype)
add_subdirectory(linkedlist)
add_subdirectory(vector)
add_subdirectory(stack)
add_subdirectory(queue)
add_subdirectory(hashtable)
add_subdirectory(tree)

# ─── 통합 데이터구조 라이브러리 생성 ──────────────────────────
add_library(datastructures STATIC
    # 각 서브 라이브러리들을 하나로 통합
    # 인터페이스는 추가할 필요는 없나보다.. $<TARGET_OBJECTS:datatype> ❌
    $<TARGET_OBJECTS:linkedlist>
    $<TARGET_OBJECTS:vector>
    $<TARGET_OBJECTS:stack>
    $<TARGET_OBJECTS:queue>
    $<TARGET_OBJECTS:hashtable>
    $<TARGET_OBJECTS:tree>
)

# ─── 의존성 전파 ──────────────────────────
target_link_libraries(datastructures
	# datatype이 INTERFACE header only lib라고 해서 다른 라이브러리와 혼용할때 INTERFACE datatype 하지 말자! ❌
	PUBLIC datatype linkedlist vector stack queue tree
)

# ─── 헤더 파일 경로 설정 ──────────────────────────
target_include_directories(datastructures
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/datatype>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/linkedlist>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/vector>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/stack>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/queue>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/hashtable>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/tree>
        $<INSTALL_INTERFACE:include>
)

# ─── 설치 설정 ──────────────────────────
if(LIBRARIES_ONLY)
    install(TARGETS datastructures datatype linkedlist vector stack queue hashtable tree
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBRARY_PATH} # CMAKE_INSTALL_PREFIX (${sourceDir}/build_libraries/install)을 의미한다.
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBRARY_PATH} # CMAKE_INSTALL_PREFIX (${sourceDir}/build_libraries/install)을 의미한다.
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINARY_PATH} # CMAKE_INSTALL_PREFIX (${sourceDir}/build_libraries/install)을 의미한다.
    )

    install(FILES
        datatype/sjhdatatype.h
        linkedlist/linkedlist.h
        vector/vector.h
        stack/stack.h
	    queue/queue.h
	    queue/circular_queue.h
	    queue/priority_queue.h
	    hashtable/hashtable.h
	    hashtable/string_hashtable.h
	    tree/tree.h
        DESTINATION include
    )
endif()
