add_library(vector STATIC
	vector.h
	vector.c
)

if(LIBRARIES_ONLY)
	install(TARGETS vector
		LIBRARY DESTINATION ${CMAKE_INSTALL_LIBRARY_PATH}
		ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBRARY_PATH}
		RUNTIME DESTINATION ${CMAKE_INSTALL_BINARY_PATH}
	)

	install(FILES
		vector.h
		DESTINATION include
	)
	return()
endif()

message(STATUS "=== Libraries Configuration Complete ===")
