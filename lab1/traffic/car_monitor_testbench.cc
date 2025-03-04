#include <systemc.h>
#include "car_monitor.h"

int sc_main(int argc, char **argv) {
    // The command-line arguments are as follows:
  // 1. the simulation time (in seconds)
    assert(argc >= 2);

    char *input_file = nullptr;
    if (argc > 2) {
        input_file = argv[2];
    };

    sc_time sim_time(atof(argv[1]), SC_SEC);

    sc_signal<int> NS_sig;
    sc_signal<int> SN_sig;
    sc_signal<int> WE_sig;
    sc_signal<int> EW_sig;

    CarMonitor car_monitor("car_monitor_1", input_file);

    car_monitor(NS_sig, SN_sig, WE_sig, EW_sig);

    sc_start(sim_time);

    return 0;
}