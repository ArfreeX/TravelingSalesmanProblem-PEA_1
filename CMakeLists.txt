cmake_minimum_required(VERSION 2.8)

project(PEA_P1)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set( project_sources
   main.cpp
   helpers/FileStream.cpp
   tsp/BranchAndBound.cpp
   tsp/BruteForce.cpp
   tsp/DynamicProgramming.cpp
   tsp/GenericTsp.cpp
)

add_executable(${PROJECT_NAME}
    ${project_sources}
)
