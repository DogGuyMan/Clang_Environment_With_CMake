add_library(hashtable STATIC
	hashtable.c
)

target_include_directories(hashtable
	PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
	$<INSTALL_INTERFACE:include>
)

target_compile_features(hashtable PUBLIC c_std_17)
