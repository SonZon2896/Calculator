cmake_minimum_required(VERSION 3.2.0)
project(Calculator VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_executable(Calculator calculator_use.cpp
                         cpp/Token.cpp
                         cpp/Calculator.cpp
                         headers/Token.h
                         headers/Calculator.h
                         )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)