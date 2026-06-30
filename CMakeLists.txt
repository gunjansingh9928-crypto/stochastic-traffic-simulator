cmake_minimum_required(VERSION 3.15)
project(StochasticTrafficSimulator CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(traffic_sim
    src/main.cpp
    src/event_queue.cpp
    src/server.cpp
    src/request_generator.cpp
    src/logger.cpp
)
