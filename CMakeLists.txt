cmake_minimum_required(VERSION 3.30)
project(calcCLI)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_UNITY_BUILD ON)
set(CMAKE_UNITY_BUILD_BATCH_SIZE 0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB SRCS src/*.cpp)

add_compile_options(-flto -fsanitize=address,leak -Wall -Werror)
add_link_options(-flto -fsanitize=address,leak)

add_executable(cacl ${SRCS})

