add_library(tree STATIC
    tree
)

target_link_libraries(tree
    PUBLIC vector stack queue
)

target_include_directories(tree
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../vector>
        $<INSTALL_INTERFACE:include>
)

target_compile_features(tree PUBLIC c_std_17)
