#pragma once

#include <nlohmann/json.hpp>
#include <txtlib/controller.hpp>

namespace txt {

NLOHMANN_JSON_SERIALIZE_ENUM(txt::counter_id,
    {
        { C1, "C1" },
        { C2, "C2" },
        { C3, "C3" },
        { C4, "C4" },
    })

NLOHMANN_JSON_SERIALIZE_ENUM(txt::motor_id,
    {
        { M1, "M1" },
        { M2, "M2" },
        { M3, "M3" },
        { M4, "M4" },
    })

NLOHMANN_JSON_SERIALIZE_ENUM(txt::output_id,
    {
        { O1, "O1" },
        { O2, "O2" },
        { O3, "O3" },
        { O4, "O4" },
        { O5, "O5" },
        { O6, "O6" },
        { O7, "O7" },
        { O8, "O8" },
    })

NLOHMANN_JSON_SERIALIZE_ENUM(txt::input_id,
    {
        { I1, "I1" },
        { I2, "I2" },
        { I3, "I3" },
        { I4, "I4" },
        { I5, "I5" },
        { I6, "I6" },
        { I7, "I7" },
        { I8, "I8" },
    })

NLOHMANN_JSON_SERIALIZE_ENUM(txt::direction,
    {
        { txt::direction::forward, "forward" },
        { txt::direction::halt, "halt" },
        { txt::direction::backward, "backward" },
    })

NLOHMANN_JSON_SERIALIZE_ENUM(txt::input_mode,
    {
        { txt::input_mode::voltage, "voltage" },
        { txt::input_mode::resistance, "resistance" },
        { txt::input_mode::resistance_2, "resistance_2" },
        { txt::input_mode::ultrasonic, "ultrasonic" },
        { txt::input_mode::invalid, "invalid" },
    })

NLOHMANN_JSON_SERIALIZE_ENUM(txt::digital,
    {
        { txt::digital::yes, "yes" },
        { txt::digital::no, "no" },
    })

NLOHMANN_JSON_SERIALIZE_ENUM(txt::edge,
    {
        { txt::edge::falling, "falling" },
        { txt::edge::rising, "rising" },
    })

}