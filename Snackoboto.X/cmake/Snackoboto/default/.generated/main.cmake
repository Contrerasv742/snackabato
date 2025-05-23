include("${CMAKE_CURRENT_LIST_DIR}/rule.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/file.cmake")

set(Snackoboto_default_library_list )

# Handle files with suffix s, for group default-XC32
if(Snackoboto_default_default_XC32_FILE_TYPE_assemble)
add_library(Snackoboto_default_default_XC32_assemble OBJECT ${Snackoboto_default_default_XC32_FILE_TYPE_assemble})
    Snackoboto_default_default_XC32_assemble_rule(Snackoboto_default_default_XC32_assemble)
    list(APPEND Snackoboto_default_library_list "$<TARGET_OBJECTS:Snackoboto_default_default_XC32_assemble>")
endif()

# Handle files with suffix S, for group default-XC32
if(Snackoboto_default_default_XC32_FILE_TYPE_assembleWithPreprocess)
add_library(Snackoboto_default_default_XC32_assembleWithPreprocess OBJECT ${Snackoboto_default_default_XC32_FILE_TYPE_assembleWithPreprocess})
    Snackoboto_default_default_XC32_assembleWithPreprocess_rule(Snackoboto_default_default_XC32_assembleWithPreprocess)
    list(APPEND Snackoboto_default_library_list "$<TARGET_OBJECTS:Snackoboto_default_default_XC32_assembleWithPreprocess>")
endif()

# Handle files with suffix [cC], for group default-XC32
if(Snackoboto_default_default_XC32_FILE_TYPE_compile)
add_library(Snackoboto_default_default_XC32_compile OBJECT ${Snackoboto_default_default_XC32_FILE_TYPE_compile})
    Snackoboto_default_default_XC32_compile_rule(Snackoboto_default_default_XC32_compile)
    list(APPEND Snackoboto_default_library_list "$<TARGET_OBJECTS:Snackoboto_default_default_XC32_compile>")
endif()

# Handle files with suffix cpp, for group default-XC32
if(Snackoboto_default_default_XC32_FILE_TYPE_compile_cpp)
add_library(Snackoboto_default_default_XC32_compile_cpp OBJECT ${Snackoboto_default_default_XC32_FILE_TYPE_compile_cpp})
    Snackoboto_default_default_XC32_compile_cpp_rule(Snackoboto_default_default_XC32_compile_cpp)
    list(APPEND Snackoboto_default_library_list "$<TARGET_OBJECTS:Snackoboto_default_default_XC32_compile_cpp>")
endif()

add_executable(${Snackoboto_default_image_name} ${Snackoboto_default_library_list})

target_link_libraries(${Snackoboto_default_image_name} PRIVATE ${Snackoboto_default_default_XC32_FILE_TYPE_link})

# Add the link options from the rule file.
Snackoboto_default_link_rule(${Snackoboto_default_image_name})

# Add bin2hex target for converting built file to a .hex file.
add_custom_target(Snackoboto_default_Bin2Hex ALL
    ${MP_BIN2HEX} ${Snackoboto_default_image_name})
add_dependencies(Snackoboto_default_Bin2Hex ${Snackoboto_default_image_name})

# Post build target to copy built file to the output directory.
add_custom_command(TARGET ${Snackoboto_default_image_name} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E make_directory ${Snackoboto_default_output_dir}
                    COMMAND ${CMAKE_COMMAND} -E copy ${Snackoboto_default_image_name} ${Snackoboto_default_output_dir}/${Snackoboto_default_original_image_name}
                    BYPRODUCTS ${Snackoboto_default_output_dir}/${Snackoboto_default_original_image_name})
