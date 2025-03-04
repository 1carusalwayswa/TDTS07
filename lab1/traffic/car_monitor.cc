#include "car_monitor.h"

CarMonitor::CarMonitor(sc_module_name name, char *datafile)
  : sc_module(name),
    gen(std::random_device{}()),
    distrib(0, 3)
{
    NS.initialize(0);
    SN.initialize(0);
    WE.initialize(0);
    EW.initialize(0);

    SC_THREAD(car_monitor_thread);

    use_random = (datafile != nullptr) ? (in = new ifstream(datafile), false)
                                     : true;
};

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
        if (use_random) {
            cur_num = get_random_num();
        } else {
            *in >> cur_num;
        }

        if (cur_num == 0) {
            NS = 1;
            std::cout << "Now direction: " << "NS" << std::endl;
            SN = WE = EW = 0;
        } else if (cur_num == 1) {
            SN = 1;
            std::cout << "Now direction: " << "SN" << std::endl;
            NS = WE = EW = 0;
        } else if (cur_num == 2) {
            WE = 1;
            std::cout << "Now direction: " << "WE" << std::endl;
            NS = SN = EW = 0;
        } else if (cur_num == 3) {
            EW = 1;
            std::cout << "Now direction: " << "EW" << std::endl;
            NS = SN = WE = 0;
        }
    }
}