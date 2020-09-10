# Event loop
A simple implementation of a signal handler with the help of sd_event_loop.
This is a snippet from the following blog post: hilmerssonkod.se/blog/who_handled_my_signal.html

For this to complile you need to have [spdlog](https://github.com/gabime/spdlog) installed.

### Compile and run
To compile into a build directory using CMake run:

`cmake -S . -B build`

`cmake --build build`

if all went well you can then run the application

`./build/event_loop`

### Without spdlog
If you want you can strip out the spdlog stuff and compile it with the following:

`g++ -std=c++14 -o event_loop.o event_loop.cc -lsystemd`
