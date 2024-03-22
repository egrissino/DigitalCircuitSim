/*
 * Copyright (c) GrissinoPublishing 2024
 *
 *  Licenced under MIT Open Source Licence
 *
 */

#pragma once

#include <sim.hpp>

namespace DCSim {
namespace Componenets {

class EEPROM : public Component 
{
protected:
    uint8_t* memory;

    // Chip Process
    uint8_t get_data();
    void set_data(uint8_t data);
    void set_io_pin_state(PinState_E_t pin_state);

public:
    EEPROM(int numBusPins, int numAddressPins);
    ~EEPROM();

    int MEMORY_SIZE;
    const char* name {"EEPROM"};
    
    // IO and Address Pin groups
    pinGroup_t io_pins;
    pinGroup_t addr_pins;

    // Public Functions
    void programMemory(uint16_t address, uint8_t data);
    int loadProgram(uint8_t* program, int progSize);
    uint8_t readoutMemory(uint16_t address);
    
    // EEPROM control
    InputPin OutputEnable;
    InputPin WriteEnable;
    InputPin ChipEnable;

    // Evaluate timestep
    void evaluate() override;
};

};
};
