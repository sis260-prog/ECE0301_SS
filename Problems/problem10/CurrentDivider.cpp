#include "CurrentDivider.hpp"

int CurrentDivider::get_num_resistors() const
{
    return 0;
}

double CurrentDivider::get_source_current() const
{
    return 0.0;
}

double CurrentDivider::get_resistance(int idx) const
{
    return 0.0;
}

double CurrentDivider::get_resistor_voltage() const
{
    return 0.0;
}

double CurrentDivider::get_resistor_current(int idx) const
{
    return 0.0;
}

void CurrentDivider::set_source_current(double c)
{
}

void CurrentDivider::set_resistance(int idx, double r)
{
}
