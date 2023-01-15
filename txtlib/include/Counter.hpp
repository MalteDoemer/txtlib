#pragma once

#include "TxtController.hpp"

namespace txt {

class counter {

public:
    counter(txt::controller txt, txt::counter_id id, txt::edge edge = txt::edge::rising) : txt(txt), id(id)
    {
        txt.configure_counter(id, edge);
        reset();
        last_value = count();
    }

    void reset()
    {
        txt.reset_counter(id);

        while (!txt.is_counter_resetted(id)) {}
    }

    i16 count() { return txt.get_counter_value(id); }

    bool state() { return txt.get_counter_state(id); }

    void update()
    {
        auto val = count();
        changed = val != last_value;
        last_value = val;
    }

    bool has_changed() { return changed; }

private:
    i16 last_value;
    bool changed;

    txt::counter_id id;
    txt::controller txt;
};
}