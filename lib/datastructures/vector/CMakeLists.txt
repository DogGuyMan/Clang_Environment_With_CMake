add_library(vector STATIC
	vector.c
	vector_primitive.c
)

target_link_libraries(vector
	PUBLIC datatype
)

# ─── 헤더 파일 경로 설정 ──────────────────────────
target_include_directories(vector
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../datatype>
        $<INSTALL_INTERFACE:include>
)

# ─── C 표준 설정 ──────────────────────────
target_compile_features(vector PUBLIC c_std_17)

message(STATUS "=== Libraries Configuration Complete ===")
