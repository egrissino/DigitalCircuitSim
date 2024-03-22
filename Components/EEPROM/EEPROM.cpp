/*
 * Copyright (c) GrissinoPublishing 2024
 *
 *  Licenced under MIT Open Source Licence
 *
 */

#include <EEPROM.hpp>

using namespace DCSim;
using namespace Componenets;

//=================================================================//

EEPROM::EEPROM(int numBusPins, int numAddressPins)
 : MEMORY_SIZE(1<<numAddressPins)
{
    // Setup the address pins and allocate InputPins
    addr_pins.num_pins = numAddressPins;
    addr_pins.pins = (InputPin*) malloc(sizeof(Pin) * numAddressPins);

    // Setup the IO pins and allocate IOPins
    io_pins.num_pins = numBusPins;
    io_pins.pins = (IOPin*) malloc(sizeof(Pin) * numBusPins);

    this->memory = (uint8_t*) malloc( MEMORY_SIZE );

    // add io pins and initalize to ground
    for (int i=0; i<numBusPins; i++) 
    {
        add_pin(&io_pins.pins[i]);
        io_pins.pins[i].set_value(kLogicLow);
    }
    
    // add the address pins and initalize to ground
    for (int i=0; i<numAddressPins; i++) 
    {
        add_pin(&addr_pins.pins[i]);
        addr_pins.pins[i].set_value(kLogicLow);
    }
    
    // Add the control pins to component
    add_pin(&OutputEnable);
    add_pin(&WriteEnable);
    add_pin(&ChipEnable);

    // 
    printf("EEPROM id %d : pins: OE: %d | WE: %d | CE: %d\n", this->get_uuid(), OutputEnable.get_uuid(), WriteEnable.get_uuid(), ChipEnable.get_uuid());
    printf("io: %d - %d | addr: %d - %d\n", io_pins.pins[0].get_uuid(), io_pins.pins[numBusPins-1].get_uuid(), addr_pins.pins[0].get_uuid(), addr_pins.pins[numAddressPins-1].get_uuid());
}

//=================================================================//

EEPROM::~EEPROM() 
{
    free(addr_pins.pins);
    free(io_pins.pins);
    free(memory);
}

//=================================================================//

void EEPROM::set_io_pin_state(PinState_E_t pin_state) 
{
    // printf ("Setting Pinstate: %d\n", pin_state);
    for (int i = 0; i < io_pins.num_pins;i++) 
    {
        // printf ("Setting state: %d\n", io[i].get_uuid());
        io_pins.pins[i].set_state(pin_state);
    }
}

//=================================================================//

void EEPROM::evaluate() 
{    
    #ifdef DEBUG_PRINT
//    printf("EEPROM evaluate\n");
    #endif
    
    if (this->ChipEnable.get_value() == kLogicLow) 
    {
        #ifdef DEBUG_PRINT
//        printf("EEPROM chip enable\n");
        #endif
        
        bool OE = (this->OutputEnable.get_value() == kLogicLow);
        bool WE = (this->WriteEnable.get_value() == kLogicLow);
        
        // If both are set, no function
        if ( OE && WE ) 
        {
            printf ("Bad State!\n");
            return;
        }
        
        if ( OE )
        {
            uint8_t val = get_data();
            set_io_pin_state(kOutput);
            setPinGroup(this->io_pins, val);

            #ifdef DEBUG_PRINT
            printf("EEPROM Output enable: %d : 0x%02x\n", getPinGroup(addr_pins), val);
            #endif
            return;
        } else
        {
            set_io_pin_state(kInput);
        }
        
        if ( WE )
        {
            #ifdef DEBUG_PRINT
            printf("EEPROM Write enable\n");
            #endif
            set_io_pin_state(kInput);
            set_data(getPinGroup(io_pins));
        }
        
    }
}

//=================================================================//

int EEPROM::loadProgram(uint8_t* program, int progSize)
{
    if (progSize > MEMORY_SIZE) 
    {
        return -1;
    }
    
    // mem copy?
    int i;
    for (i = 0; i < progSize; i++) 
    {
        this->memory[i] = program[i];
    }
    
    return i;
}

//=================================================================//

uint8_t EEPROM::get_data() 
{
    //this->dataBus->byte = this->memory[this->addrBus->byte];
    const int address = getPinGroup(addr_pins);
    // printf("Reading Data from addr: %d : %d\n", address, memory[address]);
    return memory[address];
}

void EEPROM::set_data(uint8_t data) 
{
    //this->memory[this->addrBus->byte] = this->dataBus->byte;
    const uint16_t addr = getPinGroup(this->addr_pins);
    this->memory[addr] = data;
}

uint8_t EEPROM::readoutMemory(uint16_t address) 
{
    return this->memory[address];
}

void EEPROM::programMemory(uint16_t address, uint8_t data) 
{
    //this->memory[this->addrBus->byte] = this->dataBus->byte;
    this->memory[address] = data;
}

//=================================================================//
