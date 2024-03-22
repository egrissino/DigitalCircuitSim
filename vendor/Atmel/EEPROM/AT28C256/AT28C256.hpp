/*
 * Copyright (c) GrissinoPublishing 2024
 *
 *  Licenced under MIT Open Source Licence
 *
 */

#pragma once

#include <sim.hpp>
#include <EEPROM.hpp>

namespace DCSim {
namespace Vendor {
namespace Atmel {


#define CONFIG_AT28C256 1

#define AT28C256_NUM_IO_PINS   8
#define AT28C256_NUM_ADDR_PINS 15

// #define MEMORY_SIZE    (1 << AT28C256_NUM_ADDR_PINS) // 8192

class AT28C256 : public Componenets::EEPROM 
{
private:
public:
    AT28C256();

    const char* name {"AT28C256"};
    
    InputPin NotOutputEnable;
    InputPin NotWriteEnable;
    InputPin NotChipEnable;
    
    void evaluate() override;
};

};
};
};
