

#include "Common.hpp"
#include "TxtException.hpp"

class TxtController {

public:
    TxtController() = default;

    explicit TxtController(TransferArea* ta) : ta(ta) {}

    TransferArea& transfer_area() { return *ta; }

    const TransferArea& transfer_area() const { return *ta; }

private:
    TransferArea* ta { nullptr };
};