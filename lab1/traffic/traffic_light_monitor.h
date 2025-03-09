#ifndef TRAFFIC_LIGHT_MONITOR_H
#define TRAFFIC_LIGHT_MONITOR_H

#include <systemc.h>
#include <fstream>

SC_MODULE(TrafficLightMonitor) {
    sc_in<bool> NS_traffic_light;
    sc_in<bool> SN_traffic_light;
    sc_in<bool> WE_traffic_light;
    sc_in<bool> EW_traffic_light;

    SC_HAS_PROCESS(TrafficLightMonitor);
    TrafficLightMonitor(sc_module_name name, const char* outfile = nullptr);
    ~TrafficLightMonitor();

    void monitor_method();
    
    std::ofstream* out;
    bool use_file;
};

#endif // TRAFFIC_LIGHT_MONITOR_H