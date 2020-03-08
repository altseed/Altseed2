#pragma once

#include <cstring>
#include <memory>
#include <vector>

#include "../BaseObject.h"
#include "../Graphics/BatchRenderer.h"
#include "../Math/Vector2F.h"

namespace Altseed {

template <typename T>
class Array : public BaseObject {
private:
    std::vector<T> vector_;

public:
    Array() {}
    Array(int32_t size) { vector_.resize(size); }

    // void CopyTo(T* array, int32_t size) {
    //    for (size_t i = 0; i < size; i++) {
    //        array[i] = this->vector_.at(i);
    //    }
    //}

    // void CopyTo(std::shared_ptr<Array<T>> array, int32_t size) {
    //    for (size_t i = 0; i < size; i++) {
    //        array->vector_.at(i) = this->vector_.at(i);
    //    }
    //}

    /**
     * @brief データをクリアする
     */
    void Clear() { this->vector_.clear(); }

    /**
     * @brief 要素数を取得
     */
    int32_t GetCount() { return this->vector_.size(); }

    /**
     * @brief 要素数を変更
     */
    void Resize(int32_t size) { this->vector_.resize(size); }

    /**
     * @brief 内部の vector オブジェクトを取得
     */
    std::vector<T>& GetVector() { return this->vector_; }

    /**
     * @brief 内部データの生ポインタを取得
     */
    void* GetData() { return this->vector_.data(); }

    /**
     * @brief 配列をコピーする
     * 危険！：C# 連携用！Core内部で使う機会はほぼないはず
     */
    void Assign(void* ptr, int32_t size) {
        T* p = static_cast<T*>(ptr);
        this->vector_.assign(p, p + size);
    }

    /**
     * @brief 配列をコピーする
     * 危険！：C# 連携用！Core内部で使う機会はほぼないはず。ptrは予めコピーに十分な領域を確保すること
     */
    void CopyTo(void* ptr) { std::memcpy(ptr, this->vector_.data(), this->vector_.size()); }

    /**
     * @brief インデックスアクセス
     * 危険！：C# 連携用！Core内部で使うな
     */
    T GetAt(int32_t index) const { return this->vector_[index]; }

    /**
     * @brief インデックスアクセス
     * 危険！：C# 連携用！Core内部で使うな
     */
    void SetAt(int32_t index, T value) { this->vector_[index] = value; }

    /**
     * @brief インスタンスを生成します。
     */
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
using Vector2FArray = Array<Vector2F>;

}  // namespace Altseed