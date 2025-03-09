#include <systemc.h>
#include "car_monitor.h"
#include "traffic_light_server.h"
#include "traffic_light_monitor.h"

int sc_main(int argc, char **argv) {
    // The command-line arguments are as follows:
    // 1. the simulation time (in seconds)
    assert(argc >= 2);

    char *input_file = nullptr;
    char *output_file = nullptr;
    if (argc > 2) {
        input_file = argv[2];
    }
    if (argc > 3) {
        output_file = argv[3];
    }

    sc_time sim_time(atof(argv[1]), SC_SEC);

    sc_signal<int> NS_car_sig;
    sc_signal<int> SN_car_sig;
    sc_signal<int> WE_car_sig;
    sc_signal<int> EW_car_sig;

    sc_signal<bool> NS_light_sig;
    sc_signal<bool> SN_light_sig;
    sc_signal<bool> WE_light_sig;
    sc_signal<bool> EW_light_sig;

    sc_event car_comming_event;
    CarMonitor car_monitor("car_monitor_1", &car_comming_event, input_file);
    TrafficLightServer traffic_light_server("traffic_server_1", &car_comming_event);
    TrafficLightMonitor traffic_light_monitor("traffic_light_monitor_1", output_file);

    car_monitor(NS_car_sig, SN_car_sig, WE_car_sig, EW_car_sig);
    traffic_light_server(NS_car_sig, SN_car_sig, WE_car_sig, EW_car_sig, 
                        NS_light_sig, SN_light_sig, WE_light_sig, EW_light_sig);
    traffic_light_monitor(NS_light_sig, SN_light_sig, WE_light_sig, EW_light_sig);

    sc_start(sim_time);

    return 0;
}