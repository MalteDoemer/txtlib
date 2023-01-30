#pragma once

#include <iostream>
#include <optional>

#include <txtlib/motor.hpp>
#include <txtlib/button.hpp>
#include <txtlib/counter.hpp>
#include <txtlib/pwm_output.hpp>
#include <txtlib/ultrasonic.hpp>
#include <txtlib/application.hpp>

#include <txtnet/jsonrpc_server.hpp>

namespace txt {

constexpr int port = 8484;

class explorer : public txt::application {

public:
    explorer() :
        button(txt, I1),
        ultrasonic(txt, I6),
        m1(txt, M1),
        m2(txt, M2),
        lamp1(txt, O7),
        lamp2(txt, O8),
        server(port, "/explorer")
    {
        auto& app = *this;

        server.add_method("set_lights", txt::net::get_handle(&explorer::set_lights, app), { "on" });
        server.add_method("rotate", txt::net::get_handle(&explorer::rotate, app), { "direction", "degrees" });
        server.add_method("move", txt::net::get_handle(&explorer::move, app), { "direction", "distance" });
        server.add_method("stop", txt::net::get_handle(&explorer::stop, app));
        server.add_method("wait", txt::net::get_handle(&explorer::wait, app));
        server.add_method("get_distance", txt::net::get_handle(&explorer::get_distance, app));
    }

    void setup() override
    {
        // start the server
        // Note: this blocks the current thread preventing update from being called.
        server.start_listening();
    }

    i32 rotate(txt::direction direction, std::optional<int> degrees)
    {
        if (direction == txt::direction::halt) {
            stop();
            return 0;
        }

        if (degrees.has_value()) {
            // roughly calulate the distance from the given angle
            int dist = (int)(2.777777777 * (double)(degrees.value() - 2));

            // enable enhanced mode
            m1.enhanced_mode(dist, 0); // no master
            m2.enhanced_mode(dist, 1); // m1 is the master
        } else {
            m1.normal_mode();
            m2.normal_mode();
        }

        // let the motors run in opposite direction
        auto left_dir = direction;
        auto right_dir = direction == txt::direction::forward ? txt::direction::backward : txt::direction::forward;

        // start the motors on full power
        m1.start(512, left_dir);
        m2.start(512, right_dir);

        return 0;
    }

    i32 move(txt::direction direction, std::optional<int> distance)
    {
        if (direction == txt::direction::halt) {
            stop();
            return 0;
        }

        if (distance.has_value()) {
            // enable enhanced mode
            m1.enhanced_mode(distance.value(), 0); // no master
            m2.enhanced_mode(distance.value(), 1); // m1 is the master
        } else {
            m1.normal_mode();
            m2.normal_mode();
        }

        // start both motors on full power in the same direction
        m1.start(512, direction);
        m2.start(512, direction);

        return 0;
    }

    i32 stop()
    {
        m1.stop();
        m2.stop();
        return 0;
    }

    i32 wait()
    {
        while (!m1.has_stopped() && !m2.has_stopped()) {}
        return 0;
    }

    i32 set_lights(bool on)
    {
        if (on) {
            lamp1.on(512);
            lamp2.on(512);
        } else {
            lamp1.off();
            lamp2.off();
        }

        return 0;
    }

    i16 get_distance() { return ultrasonic.distance(); }

private:
    txt::motor m1;
    txt::motor m2;
    txt::button button;
    txt::pwm_output lamp1;
    txt::pwm_output lamp2;
    txt::ultrasonic ultrasonic;

    txt::net::jsonrpc_server server;
};

}