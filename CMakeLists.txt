cmake_minimum_required(VERSION 3.20)
project(AllIn_c C)

set(CMAKE_C_STANDARD 17)

add_executable(AllIn_c main.c)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SODIUM REQUIRED IMPORTED_TARGET libsodium)
target_link_libraries(AllIn_c PRIVATE PkgConfig::SODIUM)


