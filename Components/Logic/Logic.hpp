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

class LogicGate1In1Out : public Component 
{
public:
    InputPin In1;
    OutputPin Out1;

    LogicGate1In1Out();
};

class LogicGate2In1Out : public LogicGate1In1Out 
{
public:
    InputPin In2;

    LogicGate2In1Out();
};

class LogicGate3In1Out : public LogicGate2In1Out 
{
public:
    InputPin In3;

    LogicGate3In1Out();
};

class LogicGate4In1Out : public LogicGate3In1Out 
{
public:
    InputPin In4;

    LogicGate4In1Out();
};

class NotGate : public LogicGate1In1Out
{
private:    
public:
    NotGate();
    void evaluate();
};

class NorGate : public LogicGate2In1Out
{
private:
public:
    NorGate();
    void evaluate();
};

class OrGate : public LogicGate2In1Out
{
private:
public:
    OrGate();
    void evaluate();
};


class OrGate3 : public LogicGate3In1Out
{
private:
public:
    OrGate3();
    void evaluate();
};

class OrGate4 : public LogicGate4In1Out
{
private:
public:
    OrGate4();
    void evaluate();
};

};
};
