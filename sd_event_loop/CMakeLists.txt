project(EventLoopExample)
cmake_minimum_required(VERSION 3.17)
find_package(spdlog REQUIRED)
# ---------------------------------------------------------------------------------------
# Example of using pre-compiled library
# ---------------------------------------------------------------------------------------
add_executable(event_loop event_loop.cc)
target_link_libraries(event_loop PRIVATE spdlog::spdlog)
target_link_libraries(event_loop PRIVATE -lsystemd)
