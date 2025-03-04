#ifndef TRAFFIC_LIGHT_H
#define TRAFFIC_LIGHT_H

#include <systemc.h>

SC_MODULE(TrafficLightServer) {
    // the amount of cars waiting in different direction
    sc_in<int> NS_car_amount;
    sc_in<int> SN_car_amount;
    sc_in<int> WE_car_amount;
    sc_in<int> EW_car_amount;

    // status of traffic lightin different direction, false represents red, true represents green
    sc_out<bool> NS_traffic_light;
    sc_out<bool> SN_traffic_light;
    sc_out<bool> WE_traffic_light;
    sc_out<bool> EW_traffic_light;

    SC_HAS_PROCESS(TrafficLightServer);
    TrafficLightServer(sc_module_name name);

    void traffic_light_server_thread();
    // store the direction which has the lagest amount of car
    int now_largest_direction;
    // from lower to higher, is NS, SN, WE, EW
    bool traffic_light_status;
};

#endif // TRAFFIC_LIGHT_H