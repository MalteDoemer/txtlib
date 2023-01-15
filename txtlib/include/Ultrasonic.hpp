#pragma once

#include "TxtController.hpp"

namespace txt {

class ultrasonic {

public:
    ultrasonic(txt::controller txt, txt::input_id input) : txt(txt), input(input)
    {
        txt.configure_input(input, txt::input_mode::ultrasonic, txt::digital::no);
        last_value = distance();
    }

    /**
     * Get the distance reported by the ultrasonic sensor in centimeters.
     *
     * - ULTRASONIC_MIN is the minimum value reported by the sensor.
     * - ULTRASONIC_MAX is the maximum value reported by the sensor (i.e. there is nothing in the way).
     * - ULTRASONIC_OVR ???
     * - NO_ULTRASONIC means no ultrasonic sensor is present.
     */
    i16 distance() { return txt.get_input(input); }

    void update()
    {
        auto val = distance();
        changed = val != last_value;
        last_value = val;
    }

    bool has_changed() { return changed; }

private:
    i16 last_value;
    bool changed = false;

    txt::input_id input;
    txt::controller txt;
};

}