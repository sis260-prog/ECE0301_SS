#include "PracticalVsCircuit.hpp"
#include <vector>
#include <cmath>

// resistor 0 is RS, resistor 1 is RL 
PracticalVsCircuit::PracticalVsCircuit(double vs, double rs, double rl)  : VoltageDivider(vs, std::vector<double>{rs, rl}.data(), 2)
{ // 5a
}

// terminal volt = ideal source - drop across RS
double PracticalVsCircuit::get_source_voltage() const { // 5b
    return VoltageDivider::get_source_voltage() - get_resistor_voltage(0);
}

// set_resistance updates node volt and throws negative vals
void PracticalVsCircuit::set_load(double rl){ // 5c
    set_resistance(1, rl);
}

// returns the power delivered
double PracticalVsCircuit::get_load_power() const { // 5d
    double vl = get_resistor_voltage(1);
  return vl * vl / get_resistance(1);
}

//changes load then compares Pl to max power
bool PracticalVsCircuit::maximum_power_transfer(double rl) { // 5e
    set_load(rl);
  double vs = VoltageDivider::get_source_voltage(); // ideal source voltage
  double p_max = vs * vs / (4 * get_resistance(0));
  return std::abs(get_load_power() - p_max) <= 1e-9;
}
