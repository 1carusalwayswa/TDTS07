#ifndef TRAFFIC_LIGHT_H
#define TRAFFIC_LIGHT_H

#include <systemc.h>

SC_MODULE(TrafficLightServer) {
    // represent different direction the num of comming cars.
    sc_in<int> NS_car_comming;
    sc_in<int> SN_car_comming;
    sc_in<int> WE_car_comming;
    sc_in<int> EW_car_comming;

    // status of traffic lightin different direction, false represents red, true represents green
    sc_out<bool> NS_traffic_light;
    sc_out<bool> SN_traffic_light;
    sc_out<bool> WE_traffic_light;
    sc_out<bool> EW_traffic_light;

    SC_HAS_PROCESS(TrafficLightServer);
    TrafficLightServer(sc_module_name name, sc_event* car_comming_event_ptr_);

    void traffic_light_server_thread();
    // store echo amuont of each direction
    int NS_car_amount;
    int SN_car_amount;
    int WE_car_amount;
    int EW_car_amount;

    int NS_waiting_time;
    int SN_waiting_time;
    int WE_waiting_time;
    int EW_waiting_time;

    // if waiting time bigger than this variable, force the corresponding traffic light become green
    const static int biggest_waiting_time = 5;
    const static int forced_passing_time = 3;

    // false means NS-SN is green, otherwise WE-EW is green.
    bool now_green_direction;
    int keeping_time;

    sc_event* car_comming_event_ptr;
};

#endif // TRAFFIC_LIGHT_H