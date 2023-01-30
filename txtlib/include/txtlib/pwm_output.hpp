#pragma once

#include "controller.hpp"

namespace txt {

class pwm_output {

public:
    pwm_output(txt::controller txt, txt::output_id id) : txt(txt), id(id)
    {
        txt::motor_id motor_id = static_cast<txt::motor_id>(id / 2);
        txt.configure_motor_output(motor_id, false);
    }

    void on(int duty) { txt.set_output(id, duty); }

    void off() { txt.set_output(id, 0); }

private:
    txt::output_id id;
    txt::controller txt;
};

}
