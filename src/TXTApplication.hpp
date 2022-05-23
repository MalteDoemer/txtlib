#pragma once

#include <stdint.h>
#include <stddef.h>
#include <stdexcept>

#include "FtShmem.h"
#include "KeLibTxtDl.h"

using TransferArea = FISH_X1_TRANSFER;

class TXTApplication {

public:
    TXTApplication()
    {
        if (StartTxtDownloadProg() != KELIB_ERROR_NONE) {
            // TODO: good exception handling
            throw std::exception();
        }

        ta = GetKeLibTransferAreaMainAddress();
    }

    ~TXTApplication() { StopTxtDownloadProg(); }

protected:
    TransferArea* ta { nullptr };
};