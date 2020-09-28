cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(hry-sic VERSION 2.0.0)

file(GLOB_RECURSE hry-sic-src src/*.cpp src/*.hpp)
add_library(hry-sic SHARED ${hry-sic-src})

add_subdirectory(vendor)

target_compile_options(hry-sic PRIVATE ${STATIC_FLAG})

# replace it with find_package or sth, link already compiled hry-core
target_link_libraries(hry-sic PRIVATE hry-core)

target_include_directories(hry-sic PRIVATE src)