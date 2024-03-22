/*
 * Copyright (c) GrissinoPublishing 2024
 *
 *  Licenced under MIT Open Source Licence
 *
 */

#include <AT28C64.hpp>

using namespace DCSim;
using namespace Vendor;
using namespace Atmel;

AT28C64::AT28C64()
 : EEPROM(AT28C64_NUM_IO_PINS,AT28C64_NUM_ADDR_PINS)
{
    add_pin(&NotChipEnable);
    add_pin(&NotWriteEnable);
    add_pin(&NotOutputEnable);
}

void AT28C64::evaluate()
{
    if (NotChipEnable.get_value() == kLogicLow)
    {
        ChipEnable.set_value(kLogicHigh);
    }

    if (NotWriteEnable.get_value() == kLogicLow)
    {
        WriteEnable.set_value(kLogicHigh);
    }

    if (NotOutputEnable.get_value() == kLogicLow)
    {
        OutputEnable.set_value(kLogicHigh);
    }

    this->EEPROM::evaluate();
}