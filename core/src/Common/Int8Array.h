#pragma once

#include <memory>
#include <vector>

namespace Altseed {
class Int8Array : public std::vector<int8_t>, public BaseObject {
public:
    void CopyTo(int8_t* array, int32_t size) {
        for (size_t i = 0; i < size; i++) {
            array[i] = at(i);
        }
    }
    void CopyTo(std::shared_ptr<Int8Array> array, int32_t size) {
        for (size_t i = 0; i < size; i++) {
            array->at(i) = at(i);
        }
    }
};
}  // namespace Altseed