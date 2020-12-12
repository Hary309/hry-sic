cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(vendor)

use_static_linking()

project(hry-sic VERSION 2.0.0)

file(GLOB_RECURSE hry-sic-src src/*.cpp src/*.hpp)
add_library(hry-sic SHARED ${hry-sic-src})

target_link_hry_core(hry-sic)
