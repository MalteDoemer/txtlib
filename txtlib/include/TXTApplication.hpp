#pragma once

#include <chrono>
#include <thread>

#include "Common.hpp"
#include "TxtException.hpp"
#include "TxtController.hpp"

class TxtApplication {

public:
    TxtApplication()
    {
        auto ret = StartTxtDownloadProg();
        if (ret != KELIB_ERROR_NONE) {
            throw TxtException(ret);
        }

        auto ta = GetKeLibTransferAreaMainAddress();

        if (!ta)
            throw TxtException("unable to get transfer area");

        txt = TxtController(ta);
    }

    ~TxtApplication() { StopTxtDownloadProg(); }




protected:
    TxtController txt;
};