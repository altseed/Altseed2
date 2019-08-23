#pragma once

#include <vector>

namespace altseed {
class Int8Array : public std::vector<int8_t> {
    void CopyTo(int8_t* array, int32_t size) {
        for (size_t i = 0; i < size; i++) {
            array[i] = at(i);
        }
    }
};
}  // namespace altseed