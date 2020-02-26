#pragma once

#include <memory>
#include <vector>

#include "../BaseObject.h"

namespace Altseed {

template <typename T>
class Array : public BaseObject {
private:
    std::vector<T> vector_;

public:
    Array() {}

    Array(int32_t size) { vector_.resize(size); }

    void CopyTo(T* array, int32_t size) {
        for (size_t i = 0; i < size; i++) {
            array[i] = this->vector_.at(i);
        }
    }

    void CopyTo(std::shared_ptr<Array<T>> array, int32_t size) {
        for (size_t i = 0; i < size; i++) {
            array->vector_.at(i) = this->vector_.at(i);
        }
    }

    void Clear() { this->vector_.clear(); }

    std::vector<T>& GetVector() { return this->vector_; }

    int32_t GetCount() { return this->vector_.size(); }

    void* GetData() { return this->vector_.data(); }

    void SetData(void* ptr, int32_t size) {
        T* p = static_cast<T*>(ptr);
        this->vector_ = std::vector<T>(p, p + size);
    }

    void WriteDataTo(void* ptr) { std::memcpy(ptr, this->vector_.data(), this->vector_.size()); }

    void Resize(int32_t size) { this->vector_.resize(size); }

    static std::shared_ptr<Array<T>> Create(int32_t size) {
        auto obj = MakeAsdShared<Array<T>>(size);
        return obj;
    }
};

struct BatchVertex;

using Int8Array = Array<int8_t>;
using Int32Array = Array<int32_t>;
using FloatArray = Array<float>;
using VertexArray = Array<BatchVertex>;

}  // namespace Altseed