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

    void run()
    {
        init();
        while (loop())
            ;
    }

    ~TxtApplication() { StopTxtDownloadProg(); }

protected:
    virtual void init() {}

    virtual bool loop()
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        return true;
    }

protected:
    TxtController txt;
};