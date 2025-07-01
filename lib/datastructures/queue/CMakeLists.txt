add_library(queue STATIC
	queue.c
	circular_queue.c
)

target_link_libraries(queue
	PUBLIC linkedlist
)

target_include_directories(queue
	PUBLIC 
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../linkedlist>
		$<INSTALL_INTERFACE:include>
)

target_compile_features(queue PUBLIC c_std_17)
