cmake_minimum_required(VERSION 3.10)
project("MojBroj" LANGUAGES C)
file(GLOB SRC_FILES src/*.c)
add_executable(mojbroj ${SRC_FILES})
target_include_directories(mojbroj PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)