/*
 * Copyright (c) GrissinoPublishing 2024
 *
 *  Licenced under MIT Open Source Licence
 *
 */

#pragma once

#include <sim.hpp>
// #include <Bus.hpp>
#include <Buffer.hpp>
// #include <BusComponent.hpp>

namespace DCSim {
namespace Componenets {

extern const int IR_ID;

class Latch : public Buffer
{
private:
    byte_t  latchVal {0};
public:
    Latch();
    ~Latch() {};
    
    InputPin LatchEnable;

    uint8_t getLatchValue();
    void evaluate();
    
};

};
};
