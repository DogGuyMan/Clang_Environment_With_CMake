# ─── LinkedList 라이브러리 생성 ──────────────────────────
add_library(linkedlist STATIC
    linkedlist.c
)

# ─── 헤더 파일 경로 설정 ──────────────────────────
target_include_directories(linkedlist
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
)

# ─── C 표준 설정 ──────────────────────────
target_compile_features(linkedlist PUBLIC c_std_17)
