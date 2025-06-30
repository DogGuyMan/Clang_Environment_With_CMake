add_library(vector STATIC
	vector.c
)

# ─── 헤더 파일 경로 설정 ──────────────────────────
target_include_directories(vector
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
)

# ─── C 표준 설정 ──────────────────────────
target_compile_features(vector PUBLIC c_std_17)

message(STATUS "=== Libraries Configuration Complete ===")
