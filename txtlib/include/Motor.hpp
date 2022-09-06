
#pragma once

#include "TxtController.hpp"

class Motor {

public:
    Motor() = default;

    Motor(TxtController controller, MotorId id) : id(id), controller(controller) { controller.setup_motor(id); }

    bool set(Direction direction, u32 duty)
    {
        if (controller.transfer_area().ftX1config.motor[id] != 1)
            return false;

        if (duty > 512)
            return false;

        if (direction == Forward) {
            controller.transfer_area().ftX1out.duty[id * 2] = duty;
            controller.transfer_area().ftX1out.duty[id * 2 + 1] = 0;
        } else {
            controller.transfer_area().ftX1out.duty[id * 2] = 0;
            controller.transfer_area().ftX1out.duty[id * 2 + 1] = duty;
        }

        return true;
    }

    void link(Motor& other) 
    {
        controller.transfer_area().ftX1out.master[id] = 0;
        controller.transfer_area().ftX1out.master[id] = id + 1;
    }

    void unlink() {
        controller.transfer_area().ftX1out.master[id] = 0;
    }

    bool start(u32 distance) 
    { 
        controller.transfer_area().ftX1out.distance[id] = distance;
        controller.transfer_area().ftX1in.motor_ex_reached[id] = false;
        controller.transfer_area().ftX1out.motor_ex_cmd_id[id]++;

        return true;
    }

    void stop()
    {
        controller.transfer_area().ftX1out.duty[id * 2] = 0;
        controller.transfer_area().ftX1out.duty[id * 2 + 1] = 0;
    }

private:
    MotorId id;
    TxtController controller;
};