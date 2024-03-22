/*
 * Copyright (c) GrissinoPublishing 2024
 *
 *  Licenced under MIT Open Source Licence
 *
 */

#include <Clock.hpp>

using namespace DCSim;
using namespace Componenets;

//=================================================================//

Clock::Clock() {
     add_pin(&this->Clk);
     add_pin(&this->Enable);

     #ifdef DEBUG_PRINT_CLASS_INIT
     printf("Latch id %d : pins: LE: %d | OE: %d\n", this->get_uuid(), Clk.get_uuid(), Enable.get_uuid());
     #endif
}

//=================================================================//

void Clock::set_time(float new_time) {
//    printf("Clock Setting time\n");
    this->time = new_time;
}

//=================================================================//

float Clock::get_time() {
    return this->time;
}

//=================================================================//

void Clock::set_frequency(float freq) {
    this->frequency = freq;
    this->period = 0.5 / freq;
}

//=================================================================//

void Clock::evaluate() {
    
    #ifdef DEBUG_PRINT
    printf("Clock Eval\n");
    #endif
    
    if (this->Enable.get_value() == kLogicHigh) {

        #ifdef DEBUG_PRINT_CLASS_ENABLE
        printf("Clock Eval Enable\n");
        #endif

        this->elapsed += this->time - this->last_time;
        if (this->elapsed >= this->period) {
            
            this->state = !this->state;
            this->elapsed = 0;

            #if defined(DEBUG_PRINT) || 1
            printf("Clock Toggle: T: %f |\tC: %d\t", this->time, this->state);
            #endif
        }
        
        this->last_time = this->time;
    }
    
    Clk.set_value((PinValue_E_t)state);
}

//=================================================================//
