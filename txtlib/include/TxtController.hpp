#pragma once

#include "Common.hpp"
#include "TxtException.hpp"

namespace txt {

enum counter_id : u8 {
    C1 = 0,
    C2 = 1,
    C3 = 2,
    C4 = 3,
};

enum motor_id : u8 {
    M1 = 0,
    M2,
    M3,
    M4,
};

enum output_id : u8 {
    O1 = 0,
    O2,
    O3,
    O4,
    O5,
    O6,
    O7,
    O8,
};

enum input_id : u8 {
    I1 = 0,
    I2,
    I3,
    I4,
    I5,
    I6,
    I7,
    I8,
};

enum class direction : i8 {
    forward = -1,
    halt = 0,
    backward = 1,
};

enum class input_mode : u8 {
    voltage = 0,
    resistance,
    resistance_2,
    ultrasonic,
    invalid,
};

enum class digital : u8 {
    no = 0,
    yes,
};

enum class edge : u8 {
    rising,
    falling,
};

class controller {

public:
    controller() = default;

    explicit controller(txt::transfer_area* ta) : ta(ta) {}

    txt::transfer_area& transfer_area() { return *ta; }

    const txt::transfer_area& transfer_area() const { return *ta; }

public:
    /**
     * Configures the mode of the inputs (I1-I8).
     * This also clears the input to zero.
     */
    void configure_input(txt::input_id input, txt::input_mode mode, txt::digital digital)
    {
        if (input < I1 || input > I8)
            throw txt::exception(KELIB_ERROR_WRONG_PARAMETER_1_VALUE);

        auto mode_raw = static_cast<u8>(mode);
        auto is_digital = digital == txt::digital::yes;

        transfer_area().ftX1in.uni[input] = 0;
        transfer_area().ftX1config.uni[input].mode = mode_raw;
        transfer_area().ftX1config.uni[input].digital = is_digital;

        update_config();
    }

    /**
     * Configures counter inputs to be rising or falling edge (C1-C4)
     */
    void configure_counter(txt::counter_id counter, txt::edge edge)
    {
        if (counter < C1 || counter > C4)
            throw txt::exception(KELIB_ERROR_WRONG_PARAMETER_1_VALUE);

        auto is_rising_edge = edge == txt::edge::rising;

        transfer_area().ftX1config.cnt[counter].mode = is_rising_edge;

        update_config();
    }

    /**
     * Configures motor outputs (M1-M4).
     * - true : two outputs considered as motor
     * - false: two outputs considered seperatly
     */
    void configure_motor_output(txt::motor_id motor, bool is_motor)
    {
        if (motor < M1 || motor > M4)
            throw txt::exception(KELIB_ERROR_WRONG_PARAMETER_1_VALUE);

        transfer_area().ftX1config.motor[motor] = is_motor;

        update_config();
    }

    /**
     * Start/Stop a motor.
     * The duty is given in a range from 0-512, it corresponds to the output voltage (0-9V).
     *
     * Note: directions are arbitrary - it depends on how the wires are connected.
     *
     */
    void set_motor(txt::motor_id motor, int duty, txt::direction direction)
    {
        if (motor < M1 || motor > M4)
            throw txt::exception(KELIB_ERROR_WRONG_PARAMETER_1_VALUE);

        if (duty < 0 || duty > 512)
            throw txt::exception(KELIB_ERROR_WRONG_PARAMETER_2_VALUE);

        // check if output is configured as motor
        if (transfer_area().ftX1config.motor[motor] != 1)
            throw txt::exception(KELIB_ERROR_WRONG_MODE);

        switch (direction) {
        case txt::direction::halt:
            transfer_area().ftX1out.duty[motor * 2] = 0;
            transfer_area().ftX1out.duty[motor * 2 + 1] = 0;
            break;
        case txt::direction::forward:
            transfer_area().ftX1out.duty[motor * 2] = duty;
            transfer_area().ftX1out.duty[motor * 2 + 1] = 0;
            break;
        case txt::direction::backward:
            transfer_area().ftX1out.duty[motor * 2] = 0;
            transfer_area().ftX1out.duty[motor * 2 + 1] = duty;
            break;
        default:
            throw txt::exception("invalid state");
        }
    }

    /**
     *  Set the voltage of a given output (O1-O8).
     *  The duty is given in a range from 0-512, it corresponds to the output voltage (0-9V).
     */
    void set_output(txt::output_id output, int duty)
    {
        if (output < O1 || output > O8)
            throw txt::exception(KELIB_ERROR_WRONG_PARAMETER_1_VALUE);

        if (duty < 0 || duty > 512)
            throw txt::exception(KELIB_ERROR_WRONG_PARAMETER_2_VALUE);

        // check if output is configured as output and not motor
        if (transfer_area().ftX1config.motor[output / 2] != 0)
            throw txt::exception(KELIB_ERROR_WRONG_MODE);

        transfer_area().ftX1out.duty[output] = duty;
    }

    /**
     * Read the value of a given input (I1-I8).
     */
    i16 get_input(txt::input_id input)
    {
        if (input < I1 || input > I8)
            throw txt::exception(KELIB_ERROR_WRONG_PARAMETER_1_VALUE);

        return transfer_area().ftX1in.uni[input];
    }

    /**
     * Read the current state of a counter.
     */
    bool get_counter_state(txt::counter_id counter)
    {
        if (counter < C1 || counter > C4)
            throw txt::exception(KELIB_ERROR_WRONG_PARAMETER_1_VALUE);

        return transfer_area().ftX1in.cnt_in[counter];
    }

    /**
     * Read the current value/count of a counter.
     */
    i16 get_counter_value(txt::counter_id counter)
    {
        if (counter < C1 || counter > C4)
            throw txt::exception(KELIB_ERROR_WRONG_PARAMETER_1_VALUE);

        return transfer_area().ftX1in.counter[counter];
    }

    /**
     * Initiates the reset of a counter.
     */
    void reset_counter(txt::counter_id counter)
    {
        if (counter < C1 || counter > C4)
            throw txt::exception(KELIB_ERROR_WRONG_PARAMETER_1_VALUE);

        transfer_area().ftX1out.cnt_reset_cmd_id[counter]++;
        transfer_area().ftX1in.cnt_resetted[counter] = 0;
    }

    bool is_counter_resetted(txt::counter_id counter) 
    {
        if (counter < C1 || counter > C4)
            throw txt::exception(KELIB_ERROR_WRONG_PARAMETER_1_VALUE);

        return transfer_area().ftX1in.cnt_resetted[counter] == 1;
    }

private:
    void update_config() { transfer_area().ftX1state.config_id++; }

private:
    txt::transfer_area* ta { nullptr };
};

}