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

class Decoder3to8 : public BusComponent
{
private:
public:
    Decoder3to8();

    void evaluate();
};

};
};
