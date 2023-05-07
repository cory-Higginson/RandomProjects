cmake_minimum_required(VERSION 3.25)
project(FactoryGame)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5.1 COMPONENTS
        system window graphics network audio)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_executable(FactoryGame main.cpp)

target_link_libraries(FactoryGame sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
