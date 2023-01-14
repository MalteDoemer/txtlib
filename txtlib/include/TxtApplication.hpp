#pragma once

#include <chrono>
#include <thread>

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

    ~application() { StopTxtDownloadProg(); }

protected:
    txt::controller txt;
};

}