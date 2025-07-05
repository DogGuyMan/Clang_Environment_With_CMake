add_library(queue STATIC
	queue.c
	circular_queue.c
	priority_queue.c
)

target_link_libraries(queue
	PUBLIC linkedlist tree
)

target_include_directories(queue
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../linkedlist>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../tree>
		$<INSTALL_INTERFACE:include>
)

target_compile_features(queue PUBLIC c_std_17)
