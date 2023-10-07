cmake_minimum_required(VERSION 3.0.0)
project(Calculator VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

target_sources(Calculator_H_
               Calculator_use.cpp
               )
target_sources(Token_H_
               PRIVATE Token
               PUBLIC headers/Token.h
               )

add_executable(Calculator calculator_use.cpp
                         Calculator_H_
                         #Token_H_
                         )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)