cmake_minimum_required (VERSION 3.15)

project (ex3_sameer_jbara)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)
if (MSVC)
    add_compile_options (/W4 /permissive- /Zc:externConstexpr /Zc:inline)
endif ()

add_executable (ex3_sameer_jbara)

add_subdirectory (include)
add_subdirectory (src)
add_subdirectory (Resources)

