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

AT28C256::AT28C256()
 : EEPROM(AT28C64_NUM_IO_PINS,AT28C64_NUM_ADDR_PINS)
{

}
