/*
 * Copyright (c) GrissinoPublishing 2024
 *
 *  Licenced under MIT Open Source Licence
 *
 */

#pragma once

#include <sim.hpp>

namespace DCSim {
namespace Componenets {

class Clock : public Component {
private:
    bool state {0};
    
    float time {0};         // sec
    float frequency {0};    // hz
    float period    {0};    // sec
    
    float last_time {0};
    float elapsed {0};
    
public:
    Clock();
    ~Clock() {};
    
    OutputPin Clk;
    InputPin Enable;
    
    void set_time(float time);
    float get_time();
    
    void set_frequency(float freq);
    void evaluate() override;
    
};

};
};
