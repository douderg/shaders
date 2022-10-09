cmake_minimum_required (VERSION 3.15)
project (shaders VERSION 0.1.0)

add_subdirectory(prepare_shader)

file(GLOB SHADERS src/*)

foreach (SHADER ${SHADERS})
    cmake_path(GET SHADER FILENAME SHADER_NAME)
    string(REPLACE . _ TARGET_NAME ${SHADER_NAME})
    add_shader(${TARGET_NAME} ${SHADER})
    install (TARGETS ${TARGET_NAME} EXPORT ${PROJECT_NAME}-targets
        RUNTIME DESTINATION "lib/${PROJECT_NAME}-${PROJECT_VERSION}"
        ARCHIVE DESTINATION "lib/${PROJECT_NAME}-${PROJECT_VERSION}" 
    )
endforeach()

configure_file (config.cmake.in ${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config.cmake @ONLY)
configure_file (config-version.cmake.in ${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake @ONLY)

install (FILES
	${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config.cmake
	${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake
	DESTINATION "lib/${PROJECT_NAME}-${PROJECT_VERSION}"
)

install (EXPORT ${PROJECT_NAME}-targets
	DESTINATION "lib/${PROJECT_NAME}-${PROJECT_VERSION}" 
)
