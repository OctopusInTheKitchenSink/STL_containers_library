cmake_minimum_required(VERSION 3.11)
set(PROJECT_NAME s21_containers)
project($(PROJECT_NAME))

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DSOME_IMPORTANT_DEFINITION)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -Wall")

enable_testing()

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

add_library(s21_containers_lib
    Container_Adaptor/queue/s21_queue.cpp
    Container_Adaptor/stack/s21_stack.cpp
    Sorted_Container/Set_Conteiner/s21_set.cpp
    Sorted_Container/Set_Conteiner/s21_multiset.cpp
)

add_executable(TEST_QUEUE tests/s21_test_queue.cpp)
target_link_libraries(TEST_QUEUE
    s21_containers_lib
    GTest::gtest
    GTest::gmock
    GTest::Main
    test_coverage_flags
    Threads::Threads)
add_test(NAME TEST_QUEUE COMMAND TEST_QUEUE)

add_executable(TEST_STACK tests/s21_test_stack.cpp)
target_link_libraries(TEST_STACK
    s21_containers_lib
    GTest::gtest
    GTest::gmock
    GTest::Main
    Threads::Threads)
add_test(NAME TEST_STACK COMMAND TEST_STACK)

add_executable(TEST_SET tests/s21_test_set.cpp)
target_link_libraries(TEST_SET
    s21_containers_lib
    GTest::gtest
    GTest::gmock
    GTest::Main
    Threads::Threads)
add_test(NAME TEST_SET COMMAND TEST_SET)

add_executable(TEST_MULTISET tests/s21_test_multiset.cpp)
target_link_libraries(TEST_MULTISET
    s21_containers_lib
    GTest::gtest
    GTest::gmock
    GTest::Main
    Threads::Threads)
add_test(NAME TEST_MULTISET COMMAND TEST_MULTISET)
