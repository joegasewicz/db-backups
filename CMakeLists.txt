cmake_minimum_required(VERSION 4.2)
project(db_backups C)

set(CMAKE_C_STANDARD 11)

add_executable(db_backups main.c
        conf.c
        conf.h)
