#pragma once

#include "TxtController.hpp"

class Lamp {
public:
    Lamp() = default;

    Lamp(TxtController controller, OutputId id) : id(id), controller(controller) 
    { 
        controller.setup_output(id); 
    }

    bool activate(u32 brightness) 
    {
        if (controller.transfer_area().ftX1config.motor[(u8)id * 2])
            return false;

        if (brightness > 512)
            return false;

        controller.transfer_area().ftX1out.duty[id] = brightness;
        return true;
    }

    void deactivate() 
    {
        controller.transfer_area().ftX1out.duty[id] = 0;
    }

private:
    OutputId id;
    TxtController controller;
};