/*
 * Copyright (c) GrissinoPublishing 2024
 *
 *  Licenced under MIT Open Source Licence
 *
 */

#include <Logic.hpp>
#include <sim.hpp>
#include <Bus.hpp>
#include <BusComponent.hpp>

using namespace DCSim;
using namespace Componenets;

//=================================================================//

LogicGate1In1Out::LogicGate1In1Out() 
{
    add_pin(&this->In1);
    add_pin(&this->Out1);

    printf("Gate id %d : pins: in: %d | out: %d\n", this->get_uuid(), In1.get_uuid(), Out1.get_uuid());
}

//=================================================================//

LogicGate2In1Out::LogicGate2In1Out() 
{
    add_pin(&this->In2);
    printf("Gate id %d : pins: in: %d\n", this->get_uuid(), In2.get_uuid());
}

//=================================================================//

LogicGate3In1Out::LogicGate3In1Out() 
{
    add_pin(&this->In3);
    printf("Gate id %d : pins: in: %d\n", this->get_uuid(), In3.get_uuid());
}

//=================================================================//

LogicGate4In1Out::LogicGate4In1Out() 
{
    add_pin(&this->In4);
    printf("Gate id %d : pins: in: %d\n", this->get_uuid(), In4.get_uuid());
}

//=================================================================//

NotGate::NotGate() 
{
}

//=================================================================//

void NotGate::evaluate() 
{
    bool curr_val = this->In1.get_value();
    Out1.set_value((PinValue_E_t)(!curr_val));
}

//=================================================================//

NorGate::NorGate() {

}

//=================================================================//

void NorGate::evaluate() 
{
    Out1.set_value((PinValue_E_t)( !((bool)In1.get_value() | (bool)In2.get_value() )) );
}

//=================================================================//

OrGate::OrGate() 
{

}

//=================================================================//

void OrGate::evaluate() 
{
    Out1.set_value((PinValue_E_t)( (bool)In1.get_value() | (bool)In2.get_value() ));
}

//=================================================================//

OrGate3::OrGate3()
{

}

//=================================================================//

void OrGate3::evaluate() 
{
    Out1.set_value((PinValue_E_t)( (bool)In1.get_value() | (bool)In2.get_value() | (bool)In3.get_value() ));
}

//=================================================================//

OrGate4::OrGate4()
{

}

//=================================================================//

void OrGate4::evaluate() 
{
    Out1.set_value((PinValue_E_t)( (bool)In1.get_value() | (bool)In2.get_value() | (bool)In3.get_value() | (bool)In4.get_value()));
}

//=================================================================//