cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(LaboOpdracht1)

add_executable(LaboOpdracht1 main.c)

target_link_libraries(LaboOpdracht1 PJ_RPI)
target_link_libraries(LaboOpdracht1 mariadb)

install (TARGETS LaboOpdracht1 DESTINATION lib)