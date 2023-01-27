#pragma once

#include <optional>
#include <nlohmann/json.hpp>

namespace std {
template<typename T> void from_json(const nlohmann::json& j, std::optional<T>& opt)
{
    if (j.is_null()) {
        opt = {};
    } else {
        opt = j.get<T>();
    }
}

template<typename T> void to_json(nlohmann::json& j, const std::optional<T>& opt)
{
    if (opt.has_value()) {
        j = opt.value();
    } else {
        j = nullptr;
    }
}
}