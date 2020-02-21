#pragma once

#include <memory>
#include <vector>

namespace Altseed {

template <typename T>
class Array : public BaseObject {
private:
    std::vector<T> vector_;

public:
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
        this->vector_ = std::vector<T> v(p, p + size);
    }
};

using Int8Array = Array<int8_t>;
using Int32Array = Array<int32_t>;

}  // namespace Altseed