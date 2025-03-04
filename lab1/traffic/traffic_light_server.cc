#include "traffic_light.h"

TrafficLight::TrafficLight(sc_module_name name)
  : sc_module(name),
    now_largest_direction(0),
    traffic_light_status(false)
{
    own_car_amount.initialize(0);
    own_traffic_light.initialize(false);

    SC_THREAD(traffic_light_thread);
}

void TraffcLight::traffic_light_thread() {
    for (;;) {
        wait(1, SC_SEC);
        local_car_amount += incoming_car;
        
        if (local_car_amount >)
    }
};