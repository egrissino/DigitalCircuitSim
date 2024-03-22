/*
 * Copyright (c) GrissinoPublishing 2024
 *
 *  Licenced under MIT Open Source Licence
 *
 */

#pragma once

// #define DEBUG_PRINT

#include <cstdint>
#include <string>
#include <vector>

extern const int MAR_BUS_ID;
extern const int MAR_ID;
extern const int MAR_Q_PINS_ID;
extern const int IR_ID;
extern const int IR_D_PINS_ID;
extern const int MAIN_BUS_ID;

#define PIN_FILTER_MIN     (IR_D_PINS_ID)
#define PIN_FILTER_MAX     (IR_D_PINS_ID + 7)

#define NODE_FILTER_MIN     0 //(MAIN_BUS_ID + 1)
#define NODE_FILTER_MAX     0 //(MAIN_BUS_ID + 8)

#define ID_NONE -2

namespace DCSim {

// ====================================
// Base Sim object
// 

class SimObj
{
    static int UUID;
protected:
    int id;
public:
    SimObj() { this->id=SimObj::UUID++; }
    int get_uuid() const { return this->id; }

    virtual void evaluate() {};
};

// ====================================
// Pin and pin states
// 

typedef enum PinState_E {
    kInput,     // Has load impeadence
    kOutput,    // Push/pull
    kHighZ,     // High impeadence
    kSource,     // 5V DC source
    kGround,       // Ground
    kMaxState
} PinState_E_t;

typedef enum PinValue_E {
    kLogicLow,
    kLogicHigh,
    kPinValMax
} PinValue_E_t;

typedef struct byte_s {
    uint8_t byte;
    
    union {
        uint8_t bit0 : 1;
        uint8_t bit1 : 1;
        uint8_t bit2 : 1;
        uint8_t bit3 : 1;
        uint8_t bit4 : 1;
        uint8_t bit5 : 1;
        uint8_t bit6 : 1;
        uint8_t bit7 : 1;
    } bits;
    
    void clear() { this->byte = 0; }
} byte_t;

class Component;
    
class Pin : public SimObj
{
protected:
    PinState_E_t pinState ;
    PinValue_E_t pinValue ;
    
    Component* parent;
public:
   Pin();
//    ~Pin() {};
    
    PinState_E_t get_state() {return pinState;}
    PinValue_E_t get_value() {return pinValue;}
    
    void set_state(PinState_E_t pin_state) { pinState = pin_state; } 
    void set_value(PinValue_E_t pin_value) { pinValue = pin_value; }
    
    void set_id(int new_id) { id = new_id; }
    int get_id() { return id; }
    
    void set_parent(Component* comp);
    Component* get_parent();
};

class ConstStatePin : public Pin 
{
public:
    void set_state(PinState_E_t pin_state) {};
};

class InputPin : public ConstStatePin {
private:
public:
    InputPin()
    {
        pinState = kInput;
    };
};

class OutputPin : public ConstStatePin {
private:
public:
    OutputPin() {
        pinState = kOutput;
        pinValue = kLogicLow;
    };
};

class GroundPin : public ConstStatePin {
private:
public:
     GroundPin() {
        pinState = kGround;
        pinValue = kLogicLow;
    };
};

class SourcePin : public ConstStatePin {
private:
public:
     SourcePin() {
        pinState = kSource;
        pinValue = kLogicHigh;
    };

    void set_state(PinState_E_t pin_state) {};
};

class HighZPin : public ConstStatePin {
private:    
    PinState_E_t pinState {kHighZ};

    void set_state(PinState_E_t pin_state) {};
};


class IOPin : public Pin {
private:
public:
    IOPin() {
        pinState = kInput;
    };
    
    void set_state(PinState_E_t pin_state);
};

class TriStatePin : public OutputPin {
private:
public:
    TriStatePin() {
        pinState = kHighZ;
    }
    void set_state(PinState_E_t pin_state);
};

// ====================================
// Pin Groups
// 

typedef struct pin_group_s {
    int num_pins;
    Pin* pins;
} pinGroup_t;

typedef struct output_pin_group_s : public pin_group_s {
    int num_pins;
    OutputPin* pins;
} outputPinGroup_t;

typedef struct input_pin_group_s : public pin_group_s {
    int num_pins;
    InputPin* pins;
} inputPinGroup_t;

typedef struct tristate_pin_group_s : public pin_group_s {
    int num_pins;
    TriStatePin* pins;
} tristatePinGroup_t;

unsigned int getPinGroup(pinGroup_t group);
pinGroup_t copyPinGroup(pinGroup_t src, pinGroup_t dest);
pinGroup_t setPinGroup(pinGroup_t pins, unsigned int value);

// ====================================
// Componenets
// 
class Component : public SimObj
{
protected:
    std::vector<Pin*> connected_pins;
public:
    Component();
    ~Component();
    
    void add_pin(Pin* pin);
    PinValue_E_t getMyPinValue (Pin* pin);
    PinState_E_t getMyPinState (Pin* pin);
    // const char* name {"Component"};
    
    void evaluate() override;
};

// ====================================
// Electrical Node
// 

class ElectricalNode : public SimObj
{
private:
    std::vector<Pin*> connected_pins;
    std::vector<Pin*> in_pins;
    std::vector<Pin*> out_pins;
    
    float voltage;
    PinValue_E_t value;
    
    bool grounded {false};
    bool high {false};
    
    int id {-1};
    
public:
    ElectricalNode();
    ~ElectricalNode();
    
    void set_id(int new_id);
    void connect(Pin* pin);
    void evaluate() override;
    PinValue_E_t get_value();
};


// class Resistor : public Component
// {
// private:

// public:
//     void evaluate();
// };

// class Capacitor : public Component
// {

// };

}; // DCSim
