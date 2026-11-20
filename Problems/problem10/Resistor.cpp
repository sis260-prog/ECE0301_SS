#include "Resistor.hpp"

void Resistor::set_value(double r){ // rejects negative resistances, then stores with default version

  if (r < 0){
    throw std::invalid_argument("Resistance cannot be negative");
  }

  Component::set_value(r);
}

double Resistor::get_current() const { // uses get voltage, throws logic error if terminal not connected
  
  double v = get_voltage();

  if (get_value() == 0) {
    throw std::logic_error("Resistance is 0, cannot divide by 0");
  }

  return v / get_value();
}