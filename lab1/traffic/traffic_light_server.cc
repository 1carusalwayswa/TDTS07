#include "traffic_light_server.h"

const int TrafficLightServer::biggest_waiting_time;
const int TrafficLightServer::forced_passing_time;

TrafficLightServer::TrafficLightServer(sc_module_name name, sc_event* car_comming_event_ptr_)
  : sc_module(name),
    NS_car_amount(0),
    SN_car_amount(0),
    WE_car_amount(0),
    EW_car_amount(0),
    NS_waiting_time(0),
    SN_waiting_time(0),
    WE_waiting_time(0),
    EW_waiting_time(0),
    now_green_direction(false),
    keeping_time(0),
    car_comming_event_ptr(car_comming_event_ptr_)
{
    NS_traffic_light.initialize(false);
    SN_traffic_light.initialize(false);
    WE_traffic_light.initialize(false);
    EW_traffic_light.initialize(false);

    SC_THREAD(traffic_light_server_thread);
    sensitive << *car_comming_event_ptr;
    // sensitive << NS_car_comming << SN_car_comming << WE_car_comming << EW_car_comming;
}

void TrafficLightServer::traffic_light_server_thread() {
    for(;;) {
        wait(*car_comming_event_ptr);
        // update the car amount
        NS_car_amount += NS_car_comming -> read();
        SN_car_amount += SN_car_comming -> read();
        WE_car_amount += WE_car_comming -> read();
        EW_car_amount += EW_car_comming -> read();
        
        int NS_SN_total = NS_car_amount + SN_car_amount;
        int WE_EW_total = WE_car_amount + EW_car_amount;

        bool ns_traffic_light, sn_traffic_light, we_traffic_light, ew_traffic_light;

        if (keeping_time != 0) {
            keeping_time--;
        } else {
            if (NS_SN_total < WE_EW_total) {
                now_green_direction = true;
            }

            if (now_green_direction 
                            && (NS_waiting_time > biggest_waiting_time 
                            ||  SN_waiting_time > biggest_waiting_time)) {
                keeping_time = forced_passing_time;
                now_green_direction = false;
                NS_waiting_time = SN_waiting_time = 0;
            }

            if (!now_green_direction 
                            && (WE_waiting_time > biggest_waiting_time 
                            ||  EW_waiting_time > biggest_waiting_time)) {
                keeping_time = forced_passing_time;
                now_green_direction = true;
                WE_waiting_time = EW_waiting_time = 0;
            }
        }

        // generate traffic light status base on now car amount status
        if (now_green_direction) {
            // NS-SN direction wait
            NS_waiting_time += NS_car_amount > 0 ? 1 : 0;
            SN_waiting_time += SN_car_amount > 0 ? 1 : 0;

            ns_traffic_light = sn_traffic_light = false;
            // generate WE, EW traffic light status
            we_traffic_light = (WE_car_amount > 0);
            ew_traffic_light = (EW_car_amount > 0);
        } else {
            // WE-EW direction wait
            WE_waiting_time += WE_car_amount > 0 ? 1 : 0;
            EW_waiting_time += EW_car_amount > 0 ? 1 : 0;

            we_traffic_light = ew_traffic_light = false;
            // generate NS, SN traffic light status
            ns_traffic_light = (NS_car_amount > 0);
            sn_traffic_light = (SN_car_amount > 0);
        }

        // DEBUG code
        std::cout << sc_time_stamp() << " amount: "
                                        << NS_car_amount << " "
                                        << SN_car_amount << " "
                                        << WE_car_amount << " "
                                        << EW_car_amount << std::endl;

        if (ns_traffic_light) NS_car_amount--;
        if (sn_traffic_light) SN_car_amount--;
        if (we_traffic_light) WE_car_amount--;
        if (ew_traffic_light) EW_car_amount--;

        NS_traffic_light -> write(ns_traffic_light);
        SN_traffic_light -> write(sn_traffic_light);
        WE_traffic_light -> write(we_traffic_light);
        EW_traffic_light -> write(ew_traffic_light);
        // DEBUG code, should be commented when not debug
        std::cout << sc_time_stamp() << " light: "
                    << ns_traffic_light << " " << sn_traffic_light << " "
                    << we_traffic_light << " " << ew_traffic_light << std::endl;
        std::cout << std::endl;
    }
};