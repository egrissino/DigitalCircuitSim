/*
 * Copyright (c) GrissinoPublishing 2024
 *
 *  Licenced under MIT Open Source Licence
 *
 */

/*

8 bit Bus class

*/

#include <Bus.hpp>

using namespace DCSim;
using namespace Componenets;

void printBus(Bus8bit* bus) 
{    
    printf("Bus %d\n", bus->get_uuid());
    for(int i=0;i<N_BUS_BITS;i++) {
        printf(" bit: %d | %d\n", i, bus->get_bit(i));
    }
}

Bus8bit::Bus8bit() : SimObj()
{
    // Constructor
    busVal.byte = 0;

    #ifdef DEBUG_PRINT_CLASS_INIT
    printf ("Bus: %d\n", this->get_uuid ());
    for (int i = 0; i < N_BUS_BITS;i++) 
    {
        printf ("Node: %d\n", this->nodes[i].get_uuid ());
    }
    #endif
}

Bus8bit::~Bus8bit() 
{
    
}

void Bus8bit::attach(pinGroup_t pinGroup)
{
    
    int n_pins = std::min(N_BUS_BITS, pinGroup.num_pins);
    for (int i = 0; i < n_pins;i++) 
    {
        // this->nodes[i].set_id(i);
        this->nodes[i].connect(&pinGroup.pins[i]);
    }
}

void Bus8bit::evaluate() 
{
    #ifdef DEBUG_PRINT
    printf("Bus Eval: %d\n", id);
    #endif
    uint8_t val = 0;
    for (int i = 0; i < N_BUS_BITS;i++) 
    {
        this->nodes[i].evaluate();
        val |= ( (0x01 & this->nodes[i].get_value()) << i );
    }

    if (this->get_uuid () == ID_NONE)
    {
       printf ("Bus Val: %d\n", val); 
    }
    
    this->set_value(val);
}

bool Bus8bit::get_bit(uint8_t bit) 
{
    if ((bit >= 0) && (bit < N_BUS_BITS)) 
    {
        return this->nodes[bit].get_value();
    }
    return 0;
}

void Bus8bit::set_bit(uint8_t bit, bool val) 
{
    switch (bit) 
    {
        case 0:
            this->busVal.bits.bit0 = (uint8_t)val;
            break;
        case 1:
            this->busVal.bits.bit1 = (uint8_t)val;
            break;
        case 2:
            this->busVal.bits.bit2 = (uint8_t)val;
            break;
        case 3:
            this->busVal.bits.bit3 = (uint8_t)val;
            break;
        case 4:
            this->busVal.bits.bit4 = (uint8_t)val;
            break;
        case 5:
            this->busVal.bits.bit5 = (uint8_t)val;
            break;
        case 6:
            this->busVal.bits.bit6 = (uint8_t)val;
            break;
        case 7:
            this->busVal.bits.bit7 = (uint8_t)val;
            break;
        default:
            break;
            
    }
}

void Bus8bit::set_value(uint8_t byteVal) 
{
    this->busVal.byte = byteVal;
}

byte_t Bus8bit::get_value() 
{
    return this->busVal;
}

