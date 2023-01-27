#pragma once

#include <iostream>
#include <optional>

#include <Motor.hpp>
#include <Button.hpp>
#include <Counter.hpp>
#include <PwmOutput.hpp>
#include <Ultrasonic.hpp>
#include <TxtApplication.hpp>

#include <JsonRPCServer.hpp>

namespace explorer {

class app : public txt::application {

public:
    app() :
        button(txt, txt::I1),
        ultrasonic(txt, txt::I6),
        m1(txt, txt::M1),
        m2(txt, txt::M2),
        lamp1(txt, txt::O7),
        lamp2(txt, txt::O8),
        server(8484, "/explorer")
    {
        server.add_method("set_lights", txt::net::get_handle(&app::set_lights, *this), { "on" });
    }

    void setup() override
    {
        // start the server
        // Note: this blocks the current thread preventing update from being called.
        server.start_listening();
    }

    void rotate(txt::direction direction, std::optional<int> degrees)
    {
        if (direction == txt::direction::halt) {
            stop();
            return;
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
    }

    void move(txt::direction direction, std::optional<int> distance)
    {
        if (direction == txt::direction::halt) {
            stop();
            return;
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
    }

    void stop()
    {
        m1.stop();
        m2.stop();
    }

    int wait()
    {
        while (!m1.has_stopped() && !m2.has_stopped()) {}
        return 0;
    }

    int set_lights(bool on)
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

    int get_distance() { return ultrasonic.distance(); }

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