#pragma once

#include "Types.hpp"
#include "TXTException.hpp"


class TXTApplication {

public:
    TXTApplication()
    {
        if (StartTxtDownloadProg() != KELIB_ERROR_NONE) {
            throw TXTException();
        }

        ta = GetKeLibTransferAreaMainAddress();
    }

    ~TXTApplication() { StopTxtDownloadProg(); }

protected:
    TransferArea* ta { nullptr };
};