cmake_minimum_required(VERSION 3.22.1)

message(STATUS "STARTING CMakeLists.txt in tests/")
enable_testing()

message(STATUS "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include(AddGoogleTest)

# Test executables
add_executable(TestStudent test_Student.cpp)
add_executable(TestStudentManager test_StudentManager.cpp)
add_executable(TestFileManager test_FileManager.cpp)
add_executable(TestCRUD test_CRUD.cpp)
add_executable(TestDataHandler test_DataHandler.cpp)

# Link tests to the library and GTest
target_link_libraries(TestStudent PRIVATE 
    GTest::gtest_main 
    StudentManagementSystemLib
)
target_link_libraries(TestStudentManager PRIVATE 
    GTest::gtest_main 
    StudentManagementSystemLib
)
target_link_libraries(TestFileManager PRIVATE 
    GTest::gtest_main 
    StudentManagementSystemLib
)
target_link_libraries(TestCRUD PRIVATE 
    GTest::gtest_main 
    StudentManagementSystemLib
)
target_link_libraries(TestDataHandler PRIVATE 
    GTest::gtest_main 
    StudentManagementSystemLib
)

include(GoogleTest)
gtest_discover_tests(TestStudent)
gtest_discover_tests(TestStudentManager)
gtest_discover_tests(TestFileManager)
gtest_discover_tests(TestCRUD)
gtest_discover_tests(TestDataHandler)

add_custom_target(runStudentTests
    COMMAND ${CMAKE_BINARY_DIR}/tests/TestStudent
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Running Student tests"
)

add_custom_target(runStudentManagerTests
    COMMAND ${CMAKE_BINARY_DIR}/tests/TestStudentManager
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Running StudentManager tests"
)

add_custom_target(runFileManagerTests
    COMMAND ${CMAKE_BINARY_DIR}/tests/TestFileManager
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Running FileManager tests"
)

add_custom_target(runCRUDTests
    COMMAND ${CMAKE_BINARY_DIR}/tests/TestCRUD
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Running CRUD tests"
)

add_custom_target(runDataHandlerTests
    COMMAND ${CMAKE_BINARY_DIR}/tests/TestDataHandler
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Running DataHandler tests"
)

add_dependencies(runStudentTests TestStudent)
add_dependencies(runStudentManagerTests TestStudentManager)
add_dependencies(runFileManagerTests TestFileManager)
add_dependencies(runCRUDTests TestCRUD)
add_dependencies(runDataHandlerTests TestDataHandler)


message(STATUS "END CMakeLists.txt in tests/")
