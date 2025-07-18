add_library(queue STATIC
	queue.c
	circular_queue.c
	circular_queue_primitive.c
	# priority_queue.c
)

target_link_libraries(queue
	PUBLIC linkedlist tree datatype
)

target_include_directories(queue
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../datatype>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../linkedlist>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../tree>
		$<INSTALL_INTERFACE:include>
)

target_compile_features(queue PUBLIC c_std_17)
