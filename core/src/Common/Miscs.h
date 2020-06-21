#pragma once

#include <algorithm>

namespace Altseed2 {

template <class T>
constexpr const T& clamp(const T& v, const T& low, const T& high) {
    return std::max(std::min(v, high), low);
}

}  // namespace Altseed