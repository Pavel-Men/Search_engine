cmake_minimum_required(VERSION 3.16)

project(search_engine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(search_engine main.cpp)

include(FetchContent)

#nlohmann_json lib

# set(JSON_BuildTests OFF CACHE INTERNAL "")

# add_subdirectory(nlohmann_json)

# target_link_libraries(search_engine PUBLIC nlohmann_json::nlohmann_json)

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
