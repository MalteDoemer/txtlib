#pragma once

#include "Types.hpp"
#include "TXTException.hpp"

class TXTApplication {

public:
    TXTApplication()
    {
        auto ret = StartTxtDownloadProg();

        if (ret != KELIB_ERROR_NONE) {
            throw TXTException(ret);
        }

        ta = GetKeLibTransferAreaMainAddress();

        if (!ta) {
            throw TXTException("unable to get a pointer to the transfer area");
        }
    }

    void run()
    {
        init();
        while(loop());
    }

protected:
    virtual void init() = 0;

    virtual bool loop() = 0;

    ~TXTApplication() { StopTxtDownloadProg(); }

protected:
    TransferArea* ta { nullptr };
};