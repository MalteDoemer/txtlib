#pragma once

#include "controller.hpp"

namespace txt {

class button {

public:
    button(txt::controller txt, txt::input_id input) : txt(txt), input(input)
    {
        txt.configure_input(input, txt::input_mode::resistance, txt::digital::yes);
        last_state = state();
    }

    bool state() { return txt.get_input(input); }

    void update()
    {
        auto val = state();
        changed = val != last_state;

        pressed = !last_state && val;
        released = last_state && !val;

        last_state = val;
    }

    bool has_changed() { return changed; }

    bool has_pressed() { return pressed; }

    bool has_released() { return released; }

private:
    bool last_state;
    bool changed = false;
    bool pressed = false;
    bool released = false;

    txt::input_id input;
    txt::controller txt;
};
}