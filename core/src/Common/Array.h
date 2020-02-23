#pragma once

#include <memory>
#include <vector>

namespace Altseed {

struct BatchVertex;

template <typename T>
class Array : public std::vector<T>, public BaseObject {
public:
    void CopyTo(T* array, int32_t size) {
        for (size_t i = 0; i < size; i++) {
            array[i] = this->at(i);
        }  // namespace Altseed
    }
    void CopyTo(std::shared_ptr<Array<T>> array, int32_t size) {
        for (size_t i = 0; i < size; i++) {
            array->at(i) = this->at(i);
        }
    }
};

using Int8Array = Array<int8_t>;
using Int32Array = Array<int32_t>;
using FloatArray = Array<float>;
using BatchVertexArray = Array<BatchVertex>;

}  // namespace Altseed