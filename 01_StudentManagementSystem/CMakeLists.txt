cmake_minimum_required(VERSION 3.22.1)

project(StudentManagementSystem VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if("${FILE_PATH}" STREQUAL "")
    set(STUDENTS_DATA_PATH "${CMAKE_CURRENT_SOURCE_DIR}/data/students.dat")
endif()

# Library sources (excluding main.cpp)
set(LIB_SOURCES
    src/Student.cpp
    src/StudentManager.cpp
    src/FileManager.cpp
    src/CRUD.cpp
    src/DataHandler.cpp
)

add_definitions(-DFILE_PATH="${STUDENTS_DATA_PATH}")

# Create a library from the core sources
add_library(StudentManagementSystemLib ${LIB_SOURCES})

# Include directories for the library (accessible to dependents)
target_include_directories(StudentManagementSystemLib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

# Main executable
add_executable(StudentManagementSystem main.cpp)
target_link_libraries(StudentManagementSystem PRIVATE StudentManagementSystemLib)

add_subdirectory(tests)
