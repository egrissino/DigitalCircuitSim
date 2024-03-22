/*
 * Copyright (c) GrissinoPublishing 2024
 *
 *  Licenced under MIT Open Source Licence
 *
 */

#include <Counter.hpp>

using namespace DCSim;
using namespace Componenets;

//=================================================================//

Counter::Counter() : BusComponent()
{
     add_pin(&Count);
     add_pin(&Clear);
     add_pin(&Load);
     add_pin(&Reset);
     add_pin(&Clock);
     add_pin(&Rco);
     add_pin(&Ent);

    Q_pins.num_pins = N_BUS_BITS;
    Q_pins.pins = this->Q;
    
    printf("Counter id %d : pins: Count: %d | Clear: %d | Load: %d | Reset: %d | Clock: %d | Rco: %d | Ent: %d\n",
           this->get_uuid(),
           Count.get_uuid(),
           Clear.get_uuid(),
           Load.get_uuid(),
           Reset.get_uuid(),
           Clock.get_uuid(),
           Rco.get_uuid(),
           Ent.get_uuid());
}

//=================================================================//

void Counter::evaluate()
{
    #ifdef DEBUG_PRINT
//    printf("Counter Eval\n");
    #endif
    
    // this->BusComponent::evaluate();
    set_state(kOutput);

    // Clear Async (active low)
    if (Clear.get_value() == kLogicLow) {
        #ifdef DEBUG_PRINT
        printf("Counter Clear\n");
        #endif
        value = 0;
    }
    
    // If clock is rising
    bool clock = Clock.get_value();
    if (clock && !last_clock) {
        // load (active low)
        if (Load.get_value() == kLogicLow) {
            #ifdef DEBUG_PRINT
            printf("Counter Load\n");
            #endif
            value = getPinGroup(D_pins);
        } else {
            // Count
            if (Count.get_value() == kLogicHigh) {
                value++;
                #ifdef DEBUG_PRINT
                printf("Counter Count: %d\n", value);
                #endif
                
            }
        }
    }
    
    setPinGroup({N_BUS_BITS,this->Q}, value);
    last_clock = clock;
    
}

//=================================================================//

RingCounter::RingCounter(int num_slots)
{

    Q_pins.num_pins = N_RING_COUNTER_MAX;
    Q_pins.pins = &this->Q[0];

    add_pin(&this->Clear);
    add_pin(&this->Clock);
    add_pin(&this->Ser);

    for (int i = 0; i < this->Q_pins.num_pins;i++) 
    {
        add_pin(&this->Q_pins.pins[i]);
    }

    this->serDataNode.connect(&this->Ser);

    if ((num_slots < N_RING_COUNTER_MAX) && (num_slots >= 1))
    {
        this->serDataNode.connect(&this->Q[num_slots-1]);
    }
}

//=================================================================//

void RingCounter::set_pins() 
{
    for(int i=0;i<N_RING_COUNTER_MAX;i++)
    {
        this->Q_pins.pins[i].set_value( (PinValue_E_t)((this->byte.byte >> i) & 0x1) );
    }
}

//=================================================================//

void RingCounter::evaluate() 
{
    #ifdef DEBUG_PRINT_CLASS_EVAL
    printf("RingCounter Eval\n");
    #endif
    
    // clear active low
    if (this->Clear.get_value() == kLogicLow) 
    {
        this->byte.byte = 1;
    }
    else
    {
        // If clock is rising
        bool clock = Clock.get_value();
        if (clock && !last_clock) 
        {
            // Eval serial data node first
            serDataNode.evaluate();

            // Shift data
            this->byte.byte <<= 1;

            // Get ser input
            if (this->Ser.get_value() == kLogicHigh) 
            {
                this->byte.byte |= 1;
            }

            #ifdef DEBUG_PRINT
            printf("RingCounter: %d\n", this->byte.byte & 0x1F);
            #endif
        }

        // Keep track of last clock for edge detect
        last_clock = clock;
    }
    
    // Set pins to match byte
    this->set_pins();
    
}

//=================================================================//
