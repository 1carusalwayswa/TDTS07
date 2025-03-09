#include "traffic_light_monitor.h"

TrafficLightMonitor::TrafficLightMonitor(sc_module_name name, const char* outfile)
    : sc_module(name), use_file(outfile != nullptr)
{
    if (use_file) {
        out = new std::ofstream(outfile);
    } else {
        out = nullptr;
    }

    SC_METHOD(monitor_method);
    sensitive << NS_traffic_light << SN_traffic_light << WE_traffic_light << EW_traffic_light;
}

TrafficLightMonitor::~TrafficLightMonitor()
{
    if (out != nullptr) {
        delete out;
    }
}

void TrafficLightMonitor::monitor_method()
{
    bool ns = NS_traffic_light->read();
    bool sn = SN_traffic_light->read();
    bool we = WE_traffic_light->read();
    bool ew = EW_traffic_light->read();
    
    std::string ns_str = ns ? "GREEN" : "RED";
    std::string sn_str = sn ? "GREEN" : "RED";
    std::string we_str = we ? "GREEN" : "RED";
    std::string ew_str = ew ? "GREEN" : "RED";
    
    std::string output = sc_time_stamp().to_string() + " Traffic Lights: "
                        + "NS: " + ns_str + ", "
                        + "SN: " + sn_str + ", "
                        + "WE: " + we_str + ", "
                        + "EW: " + ew_str;
    
    if (use_file) {
        *out << output << std::endl;
    }
    
    std::cout << output << std::endl;
}