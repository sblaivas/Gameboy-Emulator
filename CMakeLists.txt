#minimum CMake version this file needs
cmake_minimum_required(VERSION 3.16)

#Project name and language
project(gbemu LANGUAGES C)

#Use C11 and require it
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

#build the emulator core as a library
add_library(gbcore
    core/src/gb.c
)

#Mmake gb.h available to the core and anything that links it
target_include_directories(gbcore PUBLIC core/include)

#turn on warnings for the core
target_compile_options(gbcore PRIVATE -Wall -Wextra -Wpedantic)

#build the headless program from its main.c
add_executable(gbemu-headless
    frontends/headless/main.c
)

#link the headless program to the core
target_link_libraries(gbemu-headless PRIVATE gbcore)

#Turn on warnings for the headless program
target_compile_options(gbemu-headless PRIVATE -Wall -Wextra -Wpedantic)