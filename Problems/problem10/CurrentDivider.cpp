#include "CurrentDivider.hpp"
#include <stdexcept>

void CurrentDivider::check_resistor_idx(int idx) const{ // valid nums for resistor is from 0 to n -1
 
    if (idx < 0 || idx >= get_num_resistors()){

    throw std::out_of_range("Resistor index out of range");
  
    }
}

void CurrentDivider::update_node_voltage(){ // node 1 volt, node 0 stays at 0V
    double g_total = 0;
  for (int i = 1; i <= get_num_resistors(); i++){

    // a 0 ohm resistor shorts node 1
    if (get_component_value(i) == 0){
      set_node_voltage(1, 0);
      return;
    }
    g_total += 1.0 / get_component_value(i);
  }
  set_node_voltage(1, get_component_value(0) / g_total);
}

// 2 nodes, all components between node 1 and 0
CurrentDivider::CurrentDivider(double c, double res[], int num_res): Network(2, num_res + 1) { // 4a

if (num_res < 1) {
    throw std::invalid_argument("Current divider needs at least one resistor");
}

// source, terminal A at ground, terminal B at node 
CurrentSource *cs = new CurrentSource();
 set_component(0, cs);
 connect_component_terminal_a(0, 0);
 connect_component_terminal_b(0, 1);
 set_component_value(0, c);

  // components 1 to n, resistors in parallel, terminal B (+) at node 1
  for (int i = 1; i <= num_res; i++) {

    Resistor *r = new Resistor();
    set_component(i, r);
    connect_component_terminal_a(i, 0);
    connect_component_terminal_b(i, 1);
    set_component_value(i, res[i - 1]); // rejects negatives

  }

  update_node_voltage();

}

// returns num of resistors in the circuit
int CurrentDivider::get_num_resistors() const { // 4b
    return get_num_components() - 1;
}

// when source componenet is 0
double CurrentDivider::get_source_current() const { // 4c
    return get_component_current(0);
}

// resistor idx is component idx + 1
double CurrentDivider::get_resistance(int idx) const { // 4d
    check_resistor_idx(idx);
  return get_component_value(idx + 1);
}

// all resistors get same volt
double CurrentDivider::get_resistor_voltage() const { // 4e
    return get_component_voltage(1);
}

// ohms law in get_current w/ new node voltage
double CurrentDivider::get_resistor_current(int idx) const { // 4f
    check_resistor_idx(idx);
  return get_component_current(idx + 1);
}

// new current source val
void CurrentDivider::set_source_current(double c){ // 4g
    set_component_value(0, c);
  update_node_voltage();
}

// sets specified resistor to val
void CurrentDivider::set_resistance(int idx, double r){ // 4g
    check_resistor_idx(idx);
  set_component_value(idx + 1, r);
  update_node_voltage();
}
