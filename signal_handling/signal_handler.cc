#include <iostream>
#include <signal.h>
#include <string.h>

namespace {
void signal_handler(int signal, siginfo_t* sig_info, void* unused) {
    std::cout << "Signal handler: Got " << strsignal(signal) << std::endl;
    raise(signal);
}
}

int main() {
    std::cout << "Let's set up a signal handler" << std::endl;
    struct sigaction sa;

    sa.sa_flags = SA_RESETHAND;
    sa.sa_sigaction = signal_handler;
    sigaction(SIGINT, &sa, nullptr);
    
    while(true) {}
    return 0;
}
