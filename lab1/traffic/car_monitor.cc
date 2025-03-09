#include "car_monitor.h"

CarMonitor::CarMonitor(sc_module_name name, sc_event* car_comming_event_ptr_, char *datafile)
  : sc_module(name),
    gen(std::random_device{}()),
    distrib(0, 3),
    car_comming_event_ptr(car_comming_event_ptr_)
{
    NS_car_comming.initialize(0);
    SN_car_comming.initialize(0);
    WE_car_comming.initialize(0);
    EW_car_comming.initialize(0);

    SC_THREAD(car_monitor_thread);

    use_random = (datafile != nullptr) ? (in = new ifstream(datafile), false)
                                     : true;
}

CarMonitor::~CarMonitor()
{
    if (in != nullptr) {
        delete in;
    }
}

int CarMonitor::get_random_num() {
    return distrib(gen);
}

void CarMonitor::car_monitor_thread() {
    for (;;) {
        wait(1, SC_SEC);
        int cur_num = -1;
        int ns_car_comming, sn_car_comming, we_car_comming, ew_car_comming;
        if (use_random) {
            ns_car_comming = get_random_num();
            sn_car_comming = get_random_num();
            we_car_comming = get_random_num();
            ew_car_comming = get_random_num();
        } else {
            *in >> ns_car_comming >> sn_car_comming >> we_car_comming >> ew_car_comming;
        }

        NS_car_comming -> write(ns_car_comming);
        SN_car_comming -> write(sn_car_comming);
        WE_car_comming -> write(we_car_comming);
        EW_car_comming -> write(ew_car_comming);
        std::cout << sc_time_stamp() << " car: " << ns_car_comming << " " << sn_car_comming 
                                     << " " << we_car_comming << " " << ew_car_comming << std::endl;

                                     car_comming_event_ptr->notify(SC_ZERO_TIME);  // Add a delta cycle delay
    }
}