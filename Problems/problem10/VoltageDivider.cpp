#include "VoltageDivider.hpp"

#include <stdexcept>

// n resistors need n + 1 nodes and n + 1 components
VoltageDivider::VoltageDivider(double v, double res[], int num_res) : Network(num_res + 1, num_res + 1){
  if (num_res < 1) {
    throw std::invalid_argument("Voltage divider needs at least one resistor");
  }

  // source, terminal A at ground, terminal B at node 1
  VoltageSource *vs = new VoltageSource();
  set_component(0, vs);
  connect_component_terminal_a(0, 0);
  connect_component_terminal_b(0, 1);
  set_component_value(0, v);

  // components 1 to n: resistors in series, terminal B (+) at the higher node
  for (int i = 1; i <= num_res; i++){

    Resistor *r = new Resistor();
    set_component(i, r);
    connect_component_terminal_b(i, i);
    if (i == num_res) {

      connect_component_terminal_a(i, 0); // last resistor returns to ground
    
    } else {

      connect_component_terminal_a(i, i + 1);
   
    }
    set_component_value(i, res[i - 1]); //  rejects negatives
  }

  update_node_voltages();
}

// node 1 is at the source voltage, each next node drops by I * R
void VoltageDivider::update_node_voltages() {

  double vs = get_component_value(0);

  double r_total = 0;
  for (int i = 1; i <= get_num_resistors(); i++) {
   
    r_total += get_component_value(i);
 
}
  double current = vs / r_total;

  set_node_voltage(1, vs);
  for (int i = 1; i < get_num_resistors(); i++) {
   
    set_node_voltage(i + 1, get_node_voltage(i) - current * get_component_value(i));
  
    }
}

int VoltageDivider::get_num_resistors() const {
  return get_num_components() - 1;
}

// if source is component 0
double VoltageDivider::get_source_voltage() const {
  return get_component_voltage(0);
}

double VoltageDivider::get_resistance(int idx) const
{
    return 0.0;
}

double VoltageDivider::get_resistor_voltage(int idx) const
{
    return 0.0;
}

double VoltageDivider::get_loop_current() const
{
    return 0.0;
}

void VoltageDivider::set_source_voltage(double v)
{
}

void VoltageDivider::set_resistance(int idx, double r)
{
}
