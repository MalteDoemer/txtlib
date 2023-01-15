#pragma once

#include "Common.hpp"
#include "TxtException.hpp"
#include "TxtController.hpp"

namespace txt {

class application {

public:
    application()
    {
        auto ret = StartTxtDownloadProg();
        if (ret != KELIB_ERROR_NONE) {
            throw txt::exception(ret);
        }

        auto ta = GetKeLibTransferAreaMainAddress();

        if (!ta)
            throw txt::exception("unable to get transfer_area");

        txt = txt::controller(ta);
    }

    void start()
    {
        setup();
        running = true;

        while (running) {
            update();
        }
    }

    void stop() { running = false; }

    virtual void setup() {}

    virtual void update() {}

protected:
    txt::controller txt;

    bool running { false };
};

}