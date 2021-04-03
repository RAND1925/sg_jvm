#pragma once

#include <string>

#include "windows.h"


inline constexpr unsigned char operator "" _b(unsigned long long arg) noexcept {
    return static_cast<unsigned char>(arg);
}
