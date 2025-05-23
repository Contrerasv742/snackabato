# The following variables contains the files used by the different stages of the build process.
set(Snackoboto_default_default_XC32_FILE_TYPE_assemble)
set_source_files_properties(${Snackoboto_default_default_XC32_FILE_TYPE_assemble} PROPERTIES LANGUAGE ASM)
set(Snackoboto_default_default_XC32_FILE_TYPE_assembleWithPreprocess)
set_source_files_properties(${Snackoboto_default_default_XC32_FILE_TYPE_assembleWithPreprocess} PROPERTIES LANGUAGE ASM)
set(Snackoboto_default_default_XC32_FILE_TYPE_compile
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../AD.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../BOARD.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../LED.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../RC_Servo.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../part1.c")
set_source_files_properties(${Snackoboto_default_default_XC32_FILE_TYPE_compile} PROPERTIES LANGUAGE C)
set(Snackoboto_default_default_XC32_FILE_TYPE_compile_cpp)
set_source_files_properties(${Snackoboto_default_default_XC32_FILE_TYPE_compile_cpp} PROPERTIES LANGUAGE CXX)
set(Snackoboto_default_default_XC32_FILE_TYPE_link)

# The (internal) path to the resulting build image.
set(Snackoboto_default_internal_image_name "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/Snackoboto/default/default.elf")

# The name of the resulting image, including namespace for configuration.
set(Snackoboto_default_image_name "Snackoboto_default_default.elf")

# The name of the image, excluding the namespace for configuration.
set(Snackoboto_default_original_image_name "default.elf")

# The output directory of the final image.
set(Snackoboto_default_output_dir "${CMAKE_CURRENT_SOURCE_DIR}/../../../out/Snackoboto")
