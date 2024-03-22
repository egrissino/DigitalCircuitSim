/*
 * Copyright (c) GrissinoPublishing 2024
 *
 *  Licenced under MIT Open Source Licence
 *
 */


#include <Latch.hpp>

using namespace DCSim;
using namespace Componenets;

//=================================================================//

Latch::Latch() : Buffer()
{

    add_pin(&LatchEnable);

    D_pins.num_pins = N_BUS_BITS;
    D_pins.pins = this->D;

    Q_pins.num_pins = N_BUS_BITS;
    Q_pins.pins = this->Q;
    
    printf("Latch id %d : pins: LE: %d | OE: %d\n", this->get_uuid(), LatchEnable.get_uuid(), OutputEnable.get_uuid());
}

//=================================================================//

uint8_t Latch::getLatchValue() 
{
    return this->latchVal.byte;
}

//=================================================================//

void Latch::evaluate() 
{
    #ifdef DEBUG_PRINT
    // printf("Latch evaluate : ID: %d \n", this->id);
    #endif

    // Eval output enable in base class
    

    if ( LatchEnable.get_value() == kLogicHigh ) 
    {
        set_state(kHighZ);
        latchVal.byte = getPinGroup(D_pins);
        #ifdef DEBUG_PRINT
        if(this->id == ID_NONE) 
        {
           printf("Latch Load : ID: %d | val : %d\n", get_uuid(), getPinGroup(D_pins));
        }
        #endif
        
    } else 
    {
        this->BusComponent::evaluate();
        if (OutputEnable.get_value() == kLogicHigh) 
        {
            set_state(kOutput);
            #ifdef DEBUG_PRINT
            if(this->id == 50) 
            {
                printf("Latch Output Enable : ID %d | val : 0x%02x\n", this->id, getPinGroup(this->D_pins));
            }
            #endif
            setPinGroup(Q_pins, this->latchVal.byte);
        }
    }
}

//=================================================================//
