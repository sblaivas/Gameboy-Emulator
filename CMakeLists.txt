#minimum CMake version this file needs
cmake_minimum_required(VERSION 3.16)

#Project name and language
project(gbemu LANGUAGES C)

#Use C11 and require it
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#build the emulator core as a library
add_library(gbcore core/src/gb.c)

#Mmake gb.h available to the core and anything that links it
target_include_directories(gbcore PUBLIC core/include)

#turn on warnings for the core
target_compile_options(gbcore PRIVATE -Wall -Wextra -Wpedantic)

#build the headless program from its main.c
add_executable(gbemu-headless frontends/headless/main.c)

#link the headless program to the core
target_link_libraries(gbemu-headless PRIVATE gbcore)

#Turn on warnings for the headless program
target_compile_options(gbemu-headless PRIVATE -Wall -Wextra -Wpedantic)

#Find SDL2 on this machine and stop if it's missing
find_package(SDL2 REQUIRED)

# Build the SDL program from its main.c.
add_executable(gbemu frontends/sdl/main.c)

#link the SDL program to the core and to SDL2
target_link_libraries(gbemu PRIVATE gbcore SDL2::SDL2)

#turn on warnings for the SDL program
target_compile_options(gbemu PRIVATE -Wall -Wextra -Wpedantic)