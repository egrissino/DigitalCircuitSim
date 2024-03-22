/*
 * Copyright (c) GrissinoPublishing 2024
 *
 *  Licenced under MIT Open Source Licence
 *
 */

/*

 Component that interfaces with 8 bit Bus

*/

#pragma once

#include <Bus.hpp>

namespace DCSim {
namespace Componenets {

class BusComponent : public Component
{
protected:
    // PinValue_E_t oe_state {kLogicLow};
public:
    InputPin D[N_BUS_BITS] ;
    TriStatePin Q[N_BUS_BITS];

    BusComponent();
    
    pinGroup_t D_pins;
    pinGroup_t Q_pins;

    InputPin OutputEnable;
    
    void set_state(PinState_E_t state);
    
    void evaluate() override;

};

};
};
