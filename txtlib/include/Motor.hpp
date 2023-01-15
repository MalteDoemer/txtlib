
#pragma once

#include "TxtController.hpp"

namespace txt {

class motor {

public:
    motor(txt::controller txt, txt::motor_id id) : txt(txt), id(id)
    {
        txt.configure_motor_output(id, true);
        stop();
    }

    void start(int duty, txt::direction direction) { txt.set_motor(id, duty, direction); }

    void stop() { txt.set_motor(id, 0, txt::direction::halt); }

private:
    txt::motor_id id;
    txt::controller txt;
};

}