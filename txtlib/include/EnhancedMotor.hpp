#pragma once

#include "TxtController.hpp"

class EnhancedMotor {
EnhancedMotor() = default;

    EnhancedMotor(TxtController controller, MotorId id) : id(id), controller(controller) 
    {
        controller.setup_enhanced_motor(id);
    }

private:
    MotorId id;
    TxtController controller;
};