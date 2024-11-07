cmake_minimum_required(VERSION 3.20)

project(EpiKodi VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if (BUILD)
    add_subdirectory(app)
endif()

if (TEST)
    add_subdirectory(test)
endif()
