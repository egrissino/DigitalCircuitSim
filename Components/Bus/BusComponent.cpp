/*
 * Copyright (c) GrissinoPublishing 2024
 *
 *  Licenced under MIT Open Source Licence
 *
 */

/*

 Component that interfaces with 8 bit Bus

*/

#include <BusComponent.hpp>

using namespace DCSim;
using namespace Componenets;

BusComponent::BusComponent() : Component()
{
    // 
    for (int i=0; i<N_BUS_BITS; i++) 
    {
        add_pin(&D[i]);
    }

    // 
    for (int i=0; i<N_BUS_BITS; i++) 
    {
        add_pin(&Q[i]);
    }

    add_pin(&OutputEnable);

    D_pins.num_pins = N_BUS_BITS;
    D_pins.pins = this->D;

    Q_pins.num_pins = N_BUS_BITS;
    Q_pins.pins = this->Q;
    
    #ifdef DEBUG_PRINT_CLASS_INIT
    printf("Bus Component Tso: D: %d - %d | Q: %d - %d\n", D[0].get_uuid(), D[7].get_uuid(), Q[0].get_uuid(), Q[7].get_uuid());
    #endif
}


void BusComponent::set_state(PinState_E_t state) 
{
    switch (state) 
    {
        case kOutput:
            for (int i=0; i<Q_pins.num_pins; i++) 
            {
                Q_pins.pins[i].set_state(kOutput);
            }
            break;
        case kHighZ:
            for (int i=0; i<Q_pins.num_pins; i++) 
            {
                Q_pins.pins[i].set_state(kHighZ);
            }
            break;
        default:
            printf("Invalid pin state\n");
            break;
    }

    
}

void BusComponent::evaluate()
{

    this->Component::evaluate();

    if (this->OutputEnable.get_value() == kLogicHigh) 
    {
        // Set pins to output
        this->set_state(kOutput);
    } else 
    {
        // Set pins to hgih Z
        this->set_state(kHighZ);
    }

    // oe_state = this->OutputEnable.get_value();
}
