/*
 * Copyright (c) GrissinoPublishing 2024
 *
 *  Licenced under MIT Open Source Licence
 *
 */

#include <Decoder3to8.hpp>

using namespace DCSim;
using namespace Componenets;

//=================================================================//

Decoder3to8::Decoder3to8() : BusComponent()
{
    this->D_pins.num_pins = 4;
}

//=================================================================//

void Decoder3to8::evaluate() 
{

    // Evaluate output enable
    this->BusComponent::evaluate();

    // Get 3 input bits
    uint8_t inData = getPinGroup(this->D_pins) & 0x07;

    // Shift 2^0 up by vale of inData 
    uint8_t outData = (0x00) | (1 << inData);

    // Set the output pins wiht the outdata
    setPinGroup(this->Q_pins, outData);
    
}

//=================================================================//
