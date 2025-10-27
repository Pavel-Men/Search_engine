cmake_minimum_required(VERSION 3.16)

project(test_InvertedIndex LANGUAGES CXX)

add_executable(${PROJECT_NAME} test_InvertedIndex.cpp)

set(CMAKE_CXX_STANDARD 20)

target_link_libraries(${PROJECT_NAME} PUBLIC
			Lib
			nlohmann_json::nlohmann_json
			gtest
			gtest_main)
