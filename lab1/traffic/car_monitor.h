#ifndef DIVIDER_H
#define DIVIDER_H

#include <systemc.h>
#include <random>

SC_MODULE(CarMonitor) {
  // four signal to target 4 directions car, True means there is a car in specific direction.
  sc_out<int> NS;
  sc_out<int> SN;
  sc_out<int> WE;
  sc_out<int> EW;

  SC_HAS_PROCESS(CarMonitor);
  CarMonitor(sc_module_name name, char *datafile = nullptr);
  ~CarMonitor();

  void car_monitor_thread();
  int get_random_num();

  ifstream *in;
  bool use_random;
  std::mt19937 gen;
  std::uniform_int_distribution<> distrib;
};

#endif // DIVIDER_H
