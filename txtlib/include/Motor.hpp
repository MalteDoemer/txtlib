
#pragma once

#include "TxtController.hpp"

enum Direction : i8 {
    Left = -1,
    Right = 1, 
};

class Motor {

public:
    Motor() = default;

    Motor(TxtController controller, MotorId id) : id(id), controller(controller) 
    {
        controller.setup_motor(id, true);
    }

    void start(Direction direction, u32 duty) 
    {
        if (duty > 512)
            return;

        if (direction == Left) {
            controller.transfer_area().ftX1out.duty[id * 2] = duty;
            controller.transfer_area().ftX1out.duty[id * 2 + 1] = 0;
        } else {
            controller.transfer_area().ftX1out.duty[id * 2] = 0;
            controller.transfer_area().ftX1out.duty[id * 2 + 1] = duty;
        }
    }

    void stop() {
        controller.transfer_area().ftX1out.duty[id * 2] = 0;
        controller.transfer_area().ftX1out.duty[id * 2 + 1] = 0;
    }
    
private:
    MotorId id;
    TxtController controller;
};