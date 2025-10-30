cmake_minimum_required(VERSION 4.0)

project(search_engine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(search_engine main.cpp)

file(COPY ${CMAKE_SOURCE_DIR}/resources/json/
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/resources/txt/
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/resources/)


include(FetchContent)

#googleTese lib

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
set(gtest_disable_pthreads on)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()
target_link_libraries(search_engine PRIVATE gtest_main)
include(GoogleTest)

#nlohmann_json lib

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz)
FetchContent_MakeAvailable(json)

include(GNUInstallDirs)
install(TARGETS search_engine
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

add_library(Lib lib/converter_json.cpp
                lib/converter_json.h
                lib/inverted_index.h
                lib/inverted_index.cpp
                lib/search_server.h
                lib/search_server.cpp
                lib/structs.h)

target_link_libraries(search_engine PUBLIC Lib nlohmann_json::nlohmann_json)
target_link_libraries(Lib PUBLIC nlohmann_json::nlohmann_json)
add_subdirectory(tests)
