#pragma once

#include <stdint.h>
#include <stdio.h>
#include <atomic>
#include <memory>
#include "Common/Assertion.h"

namespace altseed {

class Core;

class BaseObject {
private:
    //! reference counter
    mutable std::atomic<int32_t> reference_;

    //! retain reference (to protect to core disposed)
    std::shared_ptr<Core> core_;

public:
    BaseObject();
    virtual ~BaseObject();

    //! Increase a reference counter
    int32_t AddRef() {
        std::atomic_fetch_add_explicit(&reference_, 1, std::memory_order_consume);
        return reference_;
    }

    //! Decrease a reference counter
    int32_t Release() {
        if (std::atomic_fetch_sub_explicit(&reference_, 1, std::memory_order_consume) == 1) {
            delete this;
            return 0;
        }
        return reference_;
    }

    //! Get current reference counter
    int32_t GetRef() const { return reference_; }

    virtual void OnTerminating() {}
};

template <typename T>
struct ReferenceDeleter {
    void operator()(T* p) {
        if (p != nullptr) {
            p->Release();
            p = nullptr;
        }
    }
};

template <class T>
std::shared_ptr<T> MakeAsdShared() {
	return std::shared_ptr<T>(new T(), ReferenceDeleter<T>());
}

template <class T>
std::shared_ptr<T> CreateSharedPtr(T* p) {
    if (p == nullptr) return nullptr;
    return std::shared_ptr<T>(p, ReferenceDeleter<T>());
}

template <class T>
std::shared_ptr<T> CreateAndAddSharedPtr(T* p) {
    if (p == nullptr) return nullptr;

    p->AddRef();
    return std::shared_ptr<T>(p, ReferenceDeleter<T>());
}

template <class T>
T* AddAndGetSharedPtr(std::shared_ptr<T> sp) {
    auto p = sp.get();
    if (p == nullptr) return nullptr;

    p->AddRef();
    return p;
}

}  // namespace altseed