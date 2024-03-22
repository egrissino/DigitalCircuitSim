/*
 * Copyright (c) GrissinoPublishing 2024
 *
 *  Licenced under MIT Open Source Licence
 *
 */

/*

8 bit Bus class

*/

#pragma once

#include <cstdint>
#include <sim.hpp>

namespace DCSim {
namespace Componenets {

#define N_BUS_BITS   8

extern const int MAR_BUS_ID;

class Bus8bit : public SimObj
{
protected:
    byte_t busVal {0};
public:
    Bus8bit();
    ~Bus8bit();
    ElectricalNode nodes[N_BUS_BITS];
    
    void attach(pinGroup_t pinGroup);
    
    void evaluate() override;
    
    void set_bit(uint8_t bit, bool val);
    bool get_bit(uint8_t bit);
    void set_value(uint8_t byteVal);
    byte_t get_value();
};

};
};
