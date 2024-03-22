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


#define CONFIG_AT28C64 1

#define AT28C64_NUM_IO_PINS   8
#define AT28C64_NUM_ADDR_PINS 12

// #define MEMORY_SIZE    (1 << AT28C64_NUM_ADDR_PINS) // 8192

class AT28C64 : public Componenets::EEPROM 
{
private:
public:
    AT28C64();

    const char* name {"AT28C64"};
    
    InputPin NotOutputEnable;
    InputPin NotWriteEnable;
    InputPin NotChipEnable;
    
    void evaluate() override;
};

};
};
};
