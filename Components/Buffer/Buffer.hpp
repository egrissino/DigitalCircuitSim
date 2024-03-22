/*
 * Copyright (c) GrissinoPublishing 2024
 *
 *  Licenced under MIT Open Source Licence
 *
 */

#pragma once

#include <sim.hpp>
#include <BusComponent.hpp>

namespace DCSim {
namespace Componenets {

#ifndef DEBUG_PRINT_CLASS_ENABLE_ID
#define DEBUG_PRINT_CLASS_ENABLE_ID -2 // disable by default
#endif

class Buffer : public BusComponent
{
private:
public:
    Buffer();
    ~Buffer() {};
    
    void evaluate() override;
};

};
};
