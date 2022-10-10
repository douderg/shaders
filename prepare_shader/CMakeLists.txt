cmake_minimum_required (VERSION 3.15)
project (prepare_shader VERSION 0.0.1)

find_program(SPIRV_COMPILER glslc REQUIRED)

add_executable (${PROJECT_NAME} main.cpp)
set_target_properties (${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)

function (add_shader TARGET_NAME SOURCE)
    add_custom_command(
        OUTPUT
            ${CMAKE_BINARY_DIR}/${TARGET_NAME}/${TARGET_NAME}.spv
        DEPENDS
            ${SOURCE}
        COMMAND
            ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/${TARGET_NAME}
        COMMAND
            ${SPIRV_COMPILER} --target-env=vulkan1.0 -o ${CMAKE_BINARY_DIR}/${TARGET_NAME}/${TARGET_NAME}.spv ${SOURCE}
    )

    add_custom_command(
        OUTPUT
            ${CMAKE_BINARY_DIR}/${TARGET_NAME}/${TARGET_NAME}.cpp
            ${CMAKE_BINARY_DIR}/${TARGET_NAME}/${TARGET_NAME}.hpp
        DEPENDS
            ${CMAKE_BINARY_DIR}/${TARGET_NAME}/${TARGET_NAME}.spv
            prepare_shader
        COMMAND $<TARGET_FILE:prepare_shader> ${TARGET_NAME} ${CMAKE_BINARY_DIR}/${TARGET_NAME}/${TARGET_NAME}.spv
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/${TARGET_NAME}
    )
    
    add_library(${TARGET_NAME} ${CMAKE_BINARY_DIR}/${TARGET_NAME}/${TARGET_NAME}.cpp)
    target_include_directories (${TARGET_NAME} 
        INTERFACE 
            $<INSTALL_INTERFACE:include> 
        PRIVATE 
            ${CMAKE_BINARY_DIR}/${TARGET_NAME}
    )

    install (FILES ${CMAKE_BINARY_DIR}/${TARGET_NAME}/${TARGET_NAME}.hpp TYPE INCLUDE)
endfunction()