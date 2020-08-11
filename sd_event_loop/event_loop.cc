#include <systemd/sd-daemon.h>
#include <systemd/sd-event.h>

#include "spdlog/async.h"
#include "spdlog/sinks/basic_file_sink.h"
#include <cstring>
#include <iostream>

int signal_handler(sd_event_source* es, const struct signalfd_siginfo* si, void* /*userdata*/) {
    std::cout << "Signal handler: Got " << strsignal(si->ssi_signo) << std::endl;
    sd_event_exit(sd_event_source_get_event(es), 0);
    return 0;
}

bool SetupSignalHandler(sd_event* event) {
    sigset_t ss;
    // Exclude all signals from defined signal set (ss)
    if (sigemptyset(&ss) < 0) {
        return false;
    }
    // Add SIGINT to signal sets
    if (sigaddset(&ss, SIGINT) < 0) {
        return false;
    }
    // Add signal mask to calling thread.
    // SIGINT is now blocked in this thread.
    if (sigprocmask(SIG_BLOCK, &ss, nullptr) < 0) {
        return false;
    }
    // Let the sd event loop handle SIGINT
    if (sd_event_add_signal(event, nullptr, SIGINT, signal_handler, nullptr) < 0) {
        return false;
    }
    return true;
}

int main() {
    sd_event* event = nullptr;
    auto async_file = spdlog::basic_logger_mt<spdlog::async_factory>("async_file_logger", "logs/async_log.txt");
    // Acquire default event loop object (for calling thread).
    int event_loop_aquired = sd_event_default(&event);
    if (event_loop_aquired < 0) {
        return EXIT_FAILURE;
    }

    if (!SetupSignalHandler(event)) {
       return EXIT_FAILURE;
    }

    std::cout << "Application started" << std::endl;
    int event_loop_exit_code = sd_event_loop(event);
    std::cout << "Application is shutting down" << std::endl;
    if (event_loop_exit_code < 0) {
        return EXIT_FAILURE;
    }

    if (event_loop_aquired >= 0) {
        sd_event_unref(event);
    }

    return EXIT_SUCCESS;
}
