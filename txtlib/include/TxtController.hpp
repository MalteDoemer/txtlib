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

        if (is_motor) {
            transfer_area().ftX1out.distance[motor] = 0;
            transfer_area().ftX1out.master[motor] = 0;
        }

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

    /*
    void start_single_motor_command(txt::motor_id motor, int distance, int duty, txt::direction direction)
    {
        if (motor < M1 || motor > M4)
            throw txt::exception(KELIB_ERROR_WRONG_PARAMETER_1_VALUE);

        if (duty < 0 || duty > 512)
            throw txt::exception(KELIB_ERROR_WRONG_PARAMETER_3_VALUE);

        // check if output is configured as motor
        if (transfer_area().ftX1config.motor[motor] != 1)
            throw txt::exception(KELIB_ERROR_WRONG_MODE);

        // set the distance
        transfer_area().ftX1out.distance[motor] = distance;

        // zero means no master
        transfer_area().ftX1out.master[motor] = 0;

        // set the duty values
        set_motor(motor, duty, direction);

        // start the motor command
        transfer_area().ftX1in.motor_ex_reached[motor] = 0;
        transfer_area().ftX1out.motor_ex_cmd_id[motor]++;
    } */

    /**
     *  Starts a enhanced motor command. 
     *  Either distance or master have to be set.
     */
    void start_motor_command(txt::motor_id motor)
    {
        if (motor < M1 || motor > M4)
            throw txt::exception(KELIB_ERROR_WRONG_PARAMETER_1_VALUE);

        if (!is_enhanced_motor(motor))
            throw txt::exception(KELIB_ERROR_WRONG_MODE);

        transfer_area().ftX1in.motor_ex_reached[motor] = 0;
        transfer_area().ftX1out.motor_ex_cmd_id[motor]++;
    }

    /**
     * Checks if the motor command has finished.
     */
    bool is_motor_command_finished(txt::motor_id motor)
    {
        if (motor < M1 || motor > M4)
            throw txt::exception(KELIB_ERROR_WRONG_PARAMETER_1_VALUE);

        return transfer_area().ftX1in.motor_ex_reached[motor] == 1;
    }

    /**
     * Checks if the motor is using the enhanced motor control.
     */
    bool is_enhanced_motor(txt::motor_id motor)
    {
        if (motor < M1 || motor > M4)
            throw txt::exception(KELIB_ERROR_WRONG_PARAMETER_1_VALUE);

        return transfer_area().ftX1out.distance[motor] != 0 || transfer_area().ftX1out.master[motor] != 0;
    }

    /**
     * Sets the distance for the enhanced motor control.
     *
     * If the distance is greater than zero, enhanced motor control is enabled.
     * If it is zero and no master is set, enhanced motor control is disabled.
     */
    void set_motor_distance(txt::motor_id motor, int distance)
    {
        if (motor < M1 || motor > M4)
            throw txt::exception(KELIB_ERROR_WRONG_PARAMETER_1_VALUE);

        transfer_area().ftX1out.distance[motor] = distance;
    }

    /**
     * Set the "master" of a motor in order to synchronize two motors.
     * @param master_idx 0 means no master; 1, 2, 3, 4 correspond to M1, M2, M3, M4
     *
     * @note If master and/or distance is non-zero the motor will be in enhanced mode.
     */
    void set_motor_master(txt::motor_id motor, u8 master_idx)
    {
        if (motor < M1 || motor > M4)
            throw txt::exception(KELIB_ERROR_WRONG_PARAMETER_1_VALUE);

        if (master_idx < 0 || master_idx > M4 + 1)
            throw txt::exception(KELIB_ERROR_WRONG_PARAMETER_2_VALUE);

        transfer_area().ftX1out.master[motor] = master_idx;
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