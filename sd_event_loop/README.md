# Event loop
A simple implementation of a signal handler with the help of sd_event_loop.

Compile: `g++ -std=c++14 -o event_loop.o event_loop.cc -lsystemd`
or just run `make`.

Run: `./event_loop.o`