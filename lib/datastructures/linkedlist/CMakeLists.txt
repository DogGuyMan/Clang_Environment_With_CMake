# ─── LinkedList 라이브러리 생성 ──────────────────────────
add_library(linkedlist STATIC
    linkedlist.c
    linkedlist_primitive.c
)

# ─── LinkedList 라이브러리에 대한 의존성 명시 ──────────────────────────
target_link_libraries(linkedlist
    PUBLIC datatype  # LinkedList은 datatype에 의존함
)


# ─── 헤더 파일 경로 설정 ──────────────────────────
target_include_directories(linkedlist
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../datatype>
        $<INSTALL_INTERFACE:include>
)

# ─── C 표준 설정 ──────────────────────────
target_compile_features(linkedlist PUBLIC c_std_17)
