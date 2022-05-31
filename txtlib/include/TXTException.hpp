#pragma once

#include <stdexcept>
#include <unordered_map>

#include "KeLibTxtDl.h"

class TxtException : std::exception {

public:
    explicit TxtException(u32 error_code) : error_code(error_code) { msg = "txt error: " + std::to_string(error_code); }

    explicit TxtException(std::string msg) : msg(msg) {}

    const char* what() const noexcept override { return msg.c_str(); }

private:
    std::string msg;
    u32 error_code { KELIB_ERROR_UNDEFINED };
};