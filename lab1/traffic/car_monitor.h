#ifndef CAR_MONITOR_H
#define CAR_MONITOR_H

#include <systemc.h>
#include <random>

SC_MODULE(CarMonitor) {
  // four signal to target 4 directions car, True means there is a car in specific direction.
  sc_out<int> NS_car_comming;
  sc_out<int> SN_car_comming;
  sc_out<int> WE_car_comming;
  sc_out<int> EW_car_comming;

  SC_HAS_PROCESS(CarMonitor);
  CarMonitor(sc_module_name name, sc_event* car_comming_event_ptr_, char *datafile = nullptr);
  ~CarMonitor();

  sc_event* car_comming_event_ptr;
  void car_monitor_thread();
  int get_random_num();

  ifstream *in;
  bool use_random;
  std::mt19937 gen;
  std::uniform_int_distribution<> distrib;
};

#endif // CAR_MONITOR_H
