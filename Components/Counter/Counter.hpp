/*
 * Copyright (c) GrissinoPublishing 2024
 *
 *  Licenced under MIT Open Source Licence
 *
 */



/*

SN74HC161 - binary syncronous counter

1 - _CLR    16 - VCC
2 - CLK     15 - RCO
3 - A       14 - QA
4 - B       13 - QB
5 - C       12 - QC
6 - D       11 - QD
7 - ENP     10 - Ent
8 - GND     9  - _LOAD

*/

#pragma once

#include <sim.hpp>
#include <BusComponent.hpp>

namespace DCSim {
namespace Componenets {

#define N_CONTROL_PINS 4

class Counter : public BusComponent
{
private:
    bool last_clock {false};
    uint8_t value {0};
        
public:
    Counter();
    ~Counter() {};
    
    InputPin Count;
    InputPin Clear;
    InputPin Load;
    InputPin Reset;
    
    InputPin Clock;
    
    // Unused for this model now
    OutputPin Rco;
    OutputPin Ent;
    
    void evaluate() override;
    uint8_t get_value() {return this->value;}
    
};

#define N_RING_COUNTER_MAX 8

class RingCounter : public Component
{
private:
    bool last_clock {false};
    byte_t byte {1};
    ElectricalNode serDataNode;
    
    void set_pins();
    
public:
    RingCounter(int num_slots);
    ~RingCounter() {};
    
    InputPin Clear;
    InputPin Ser;
    InputPin Clock;
    
    OutputPin Q[N_RING_COUNTER_MAX];
    pinGroup_t Q_pins;
    
    byte_t getByteVal() {return byte;}
    void evaluate() override;
    
};

};
};
