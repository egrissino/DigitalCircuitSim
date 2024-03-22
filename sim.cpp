/*
 * Copyright (c) GrissinoPublishing 2024
 *
 *  Licenced under MIT Open Source Licence
 *
 */

#include <cassert>
#include <sim.hpp>

using namespace DCSim;

int SimObj::UUID = 0;

//=================================================================//
// ===================================
// Pin group functions

unsigned int DCSim::getPinGroup(pinGroup_t group) 
{
    unsigned int value = 0;
    for (int i = 0; i < group.num_pins; i++) 
    {
        value |= ((group.pins[i].get_value() &0x01) << i);
    }
    
    return value;
}

//=================================================================//

pinGroup_t DCSim::setPinGroup(pinGroup_t group, unsigned int value)
 {
    
    for (int i = 0; i < group.num_pins; i++) 
    {
        PinValue_E_t val = (PinValue_E_t)((value >> i) & (0x01));

        if ((group.pins[i].get_uuid() >= PIN_FILTER_MIN) && (group.pins[i].get_uuid() <= PIN_FILTER_MAX))
        {
            printf("Setting Pin: %d, %d\n", group.pins[i].get_uuid(), val);
        }
        
        group.pins[i].set_value(val);
    }
    
    return group;
}

//=================================================================//

pinGroup_t DCSim::copyPinGroup(pinGroup_t src, pinGroup_t dest) 
{
    // Use minimum pins
    int n_pins = std::min(src.num_pins, dest.num_pins);
    
    for (int i = 0; i < n_pins; i++) {
        dest.pins[i].set_value( src.pins[i].get_value() );
    }
    
    return dest;
}

//=================================================================//
// ===================================
// Pin comomon functions

Pin::Pin() : SimObj()
{
    printf (" Pin: %d\n", get_uuid());
}

//=================================================================//

void Pin::set_parent(Component* comp)
{
    this->parent = comp;
}

//=================================================================//

Component* Pin::get_parent() 
{
    return this->parent;
}

//=================================================================//

void TriStatePin::set_state(PinState_E_t pin_state)
{
    switch (pin_state) 
    {
        case kOutput:
            this->pinState = kOutput;
            break;
        case kHighZ:
            this->pinState = kHighZ;
            this->pinValue = kLogicLow;
            break;
        default:
            printf("Bad pin state\n");
            break;
    }
}

//=================================================================//
// ===================================
// IO Pin

void IOPin::set_state(PinState_E_t pin_state) 
{
    switch (this->pinState) {
        case kInput:
            this->pinState = kInput;
            break;
        case kOutput:
            this->pinState = kOutput;
            break;
        default:
            break;
    }
}

//=================================================================//
// ===================================
// Component

Component::Component() : SimObj()
{

}

//=================================================================//

Component::~Component() 
{
    for (Pin* pin : this->connected_pins) {
        pin->set_parent(nullptr);
    }
    
    this->connected_pins.clear();
}

//=================================================================//

PinValue_E_t Component::getMyPinValue (Pin* pin)
{
    int pin_id = pin->get_uuid();
    for (Pin* pin : this->connected_pins)
    {
        if (pin->get_uuid() == pin_id)
        {
            return pin->get_value();
        }
    }
}

//=================================================================//

PinState_E_t Component::getMyPinState (Pin* pin)
{
    int pin_id = pin->get_uuid();
    for (Pin* pin : this->connected_pins)
    {
        if (pin->get_uuid() == pin_id)
        {
            return pin->get_state();
        }
    }
}

//=================================================================//

void Component::add_pin(Pin* pin) 
{
    pin->set_parent(this); // need to remove link on ~Pin and ~Component
    connected_pins.push_back(pin);
}

//=================================================================//

void Component::evaluate() 
{
    // Do nothing?
}

//=================================================================//
// ===================================
// ElectricalNode

ElectricalNode::ElectricalNode() : SimObj()
{
    return;
}

//=================================================================//

ElectricalNode::~ElectricalNode() 
{
}

//=================================================================//

void ElectricalNode::set_id(int new_id)
{
    this->id = new_id;
}

//=================================================================//

PinValue_E_t ElectricalNode::get_value() 
{
    return this->value;
}

//=================================================================//
// ElectricalNode::evaluate() 
void ElectricalNode::evaluate() 
{
    // Evaluate nodes based on all connected pins

    int node_id = get_uuid();
    if ((node_id >= NODE_FILTER_MIN) && (node_id <= NODE_FILTER_MAX))
    {
        printf("Electrical Node Eval %d\n", node_id);

        for (int i=0;i<this->connected_pins.size();i++){
            auto pin = this->connected_pins[i];
            PinState_E_t pin_state = pin->get_state();
            int id = pin->get_uuid();
            printf("PinID: %d \t| PinState: %d\n", id, pin_state);
        }

    }
    
    this->in_pins.clear();
    this->out_pins.clear();
    
    // Sort Pins
    for (Pin* pin : this->connected_pins) 
    {
        PinState_E_t pin_state = pin->get_state();
        //printf("PinID: %d \t| PinState: %d\n", pin->get_id(), pin_state);
        switch (pin_state) 
        {
            // Handle driving state
            case kInput:
                //printf("Adding Input Pin\n");
                this->in_pins.push_back(pin);
                break;
            case kOutput:
                //printf("Adding Output Pin\n");
                this->out_pins.push_back(pin);
                break;
            case kHighZ:
                //printf("HighZ Pin\n"); add as input pin?
                break;
            case kGround:
                //printf("Node Grounded\n");
                this->grounded = true;
                break;
            case kSource:
                //printf("Node DC Source\n");
                this->high = true;
                break;
            default:
                break;
        }
    }
    
    assert(!(this->grounded && this->high));
    
    this->value = kPinValMax;
    
    if (this->grounded) 
    {
        //printf("Node Short!\n");
        this->value = kLogicLow;
    }
    
    if (this->high) 
    {
        //printf("Node High!\n");
        this->value = kLogicHigh;
    }
    
    //printf("DEBUG\n");
    
    for (Pin* pin : this->out_pins) 
    {
        int out_pin_id = pin->get_uuid();
        if ((out_pin_id >= PIN_FILTER_MIN) && (out_pin_id <= PIN_FILTER_MAX))
        {
            // printf("Out: %d\n", out_pin_id);
        }

        if (this->value == kPinValMax ) {
            this->value = pin->get_value();
            continue;
        }
        
        assert(pin->get_value() == this->value);
    }
    
    for (Pin* pin : this->in_pins) {
        int in_pin_id = pin->get_uuid();
        if ((in_pin_id >= PIN_FILTER_MIN) && (in_pin_id <= PIN_FILTER_MAX))
        {
            // printf("In: %d\n", in_pin_id);
        }
        
        pin->set_value(this->value);
    }
    
}

//=================================================================//

void ElectricalNode::connect(Pin* pin) {
//    printf("Connecting new pin to node: %d\n", this->id);
//    printf("id: %d\n", pin->get_uuid());
//    printf("State: %d\n", pin->get_state());
//    printf("Value: %d\n", pin->get_value());
    
    this->connected_pins.push_back(pin);
}

//=================================================================//
