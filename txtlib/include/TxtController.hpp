#pragma once

#include "Common.hpp"
#include "TxtException.hpp"

namespace txt {

enum counter_id : u8 {
    C1 = 0,
    C2 = 1,
    C3 = 2,
    C4 = 3,
};

enum motor_id : u8 {
    M1 = 0,
    M2,
    M3,
    M4,
};

enum output_id : u8 {
    O1 = 0,
    O2,
    O3,
    O4,
    O5,
    O6,
    O7,
    O8,
};

enum input_id : u8 {
    I1 = 0,
    I2,
    I3,
    I4,
    I5,
    I6,
    I7,
    I8,
};

enum direction : i8 {
    Forward = -1,
    Backward = 1,
};

enum input_mode : u8 {
    U = 0,
    R,
    R2,
    Ultrasonic,
    Invalid,
};

class controller {

public:
    controller() = default;

    explicit controller(txt::transfer_area* ta) : ta(ta) {}

    txt::transfer_area& transfer_area() { return *ta; }

    const txt::transfer_area& transfer_area() const { return *ta; }

private:
    void update_config() { ta->ftX1state.config_id++; }

private:
    txt::transfer_area* ta { nullptr };
};

}