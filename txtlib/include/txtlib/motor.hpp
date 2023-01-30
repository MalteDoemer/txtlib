
#pragma once

#include "controller.hpp"

namespace txt {

class motor {

public:
    motor(txt::controller txt, txt::motor_id id) : txt(txt), id(id)
    {
        txt.configure_motor_output(id, true);
        stop();
    }

    void enhanced_mode(int distance, u8 master_idx)
    {
        txt.set_motor_master(id, master_idx);
        txt.set_motor_distance(id, distance);
    }

    void normal_mode()
    {
        txt.set_motor_master(id, 0);
        txt.set_motor_distance(id, 0);
    }

    void start(int duty, txt::direction direction)
    {
        txt.set_motor(id, duty, direction);

        if (txt.is_enhanced_motor(id)) {
            txt.start_motor_command(id);
        }
    }

    void stop()
    {
        txt.set_motor(id, 0, txt::direction::halt);
        normal_mode();
    }

    bool has_stopped() { return txt.is_motor_command_finished(id); }

private:
    txt::motor_id id;
    txt::controller txt;
};

}