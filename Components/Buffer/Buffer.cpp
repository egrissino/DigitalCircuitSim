/*
 * Copyright (c) GrissinoPublishing 2024
 *
 *  Licenced under MIT Open Source Licence
 *
 */

#include <Buffer.hpp>

using namespace DCSim;
using namespace Componenets;

//=================================================================//

Buffer::Buffer() : BusComponent()
{
    #ifdef DEBUG_PRINT_CLASS_INIT
    printf("Buffer id %d\n", this->id);
    #endif
}

//=================================================================//

void Buffer::evaluate() 
{
    #ifdef DEBUG_PRINT_CLASS_EVAL
    printf("Buffer evaluate : ID %d \n", this->id);
    #endif

    // Eval output enable in base class
    this->BusComponent::evaluate();
    
    if (this->OutputEnable.get_value() == kLogicHigh) 
    {
        #ifdef DEBUG_PRINT_CLASS_ENABLE
        if(this->get_uuid() == DEBUG_PRINT_CLASS_ENABLE_ID) 
        {
            printf("Buffer Output Enable : ID %d | val : 0x%02x\n", this->id, getPinGroup(this->D_pins));
        }
        #endif // DEBUG_PRINT_CLASS_ENABLE

        copyPinGroup(this->D_pins, this->Q_pins);
    }
    
}

//=================================================================//
