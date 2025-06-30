# ─── Stack 라이브러리 생성 ──────────────────────────
add_library(stack STATIC
    stack.c
)

# ─── Vector 라이브러리에 대한 의존성 명시 ──────────────────────────
target_link_libraries(stack
    PUBLIC vector  # Stack은 Vector에 의존함
)

# ─── 헤더 파일 경로 설정 ──────────────────────────
target_include_directories(stack
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../vector>  # vector.h 접근
        $<INSTALL_INTERFACE:include>
)

# ─── C 표준 설정 ──────────────────────────
target_compile_features(stack PUBLIC c_std_17)
