#pragma once

#include "Common.hpp"
#include "TxtException.hpp"

enum CounterId {
    C1 = 0,
    C2 = 1,
    C3 = 2,
    C4 = 3,
};

enum MotorId {
    M1 = 0,
    M2,
    M3,
    M4,
};

enum OutputId: u8 {
    O1 = 0,
    O2,
    O3,
    O4,
    O5,
    O6,
    O7,
    O8,
};

enum InputId: u8 {
    I1 = 0,
    I2,
    I3,
    I4,
    I5,
    I6,
    I7,
    I8,
};

enum Direction : i8 {
    Forward = -1,
    Backward = 1, 
};

class TxtController {

public:
    TxtController() = default;

    explicit TxtController(TransferArea* ta) : ta(ta) {}

    void setup_input(InputId input, InputMode mode, bool digital) 
    {
        ta->ftX1config.uni[input].mode = mode;
        ta->ftX1config.uni[input].digital = digital;
        ta->ftX1in.uni[input] = 0;
        update_config();
    }

    void setup_motor(MotorId motor) 
    {
        ta->ftX1config.motor[motor] = true;
        ta->ftX1out.distance[motor] = 0;
        ta->ftX1out.master[motor] = 0;
        update_config();
    }

    void setup_enhanced_motor(MotorId motor) 
    {
        ta->ftX1config.motor[motor] = true;
        ta->ftX1out.distance[motor] = 1;
        ta->ftX1out.master[motor] = 0;
        update_config();
    }

    void setup_output(OutputId output) 
    {
        int id = output / 2;
        ta->ftX1config.motor[id] = false;
        update_config();
    }

    TransferArea& transfer_area() { return *ta; }

    const TransferArea& transfer_area() const { return *ta; }

private:
    void update_config() 
    {
        ta->ftX1state.config_id++;
    }


private:
    TransferArea* ta { nullptr };
};