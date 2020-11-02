#pragma once

#include <stdint.h>
#include <stdio.h>

#include <atomic>
#include <memory>

#include "Common/Assertion.h"

namespace Altseed2 {

class Core;

class BaseObject {
private:
    //! reference counter
    mutable std::atomic<int32_t> reference_;

    //! retain reference (to protect to core disposed)
    std::shared_ptr<Core> core_;

    std::u16string instanceName_;
    int32_t id_;

    bool terminateingEnabled_ = false;

public:
    BaseObject();
#ifdef NDEBUG
    virtual ~BaseObject();
#else
    virtual ~BaseObject() noexcept(false);
#endif

#if !USE_CBG

    //! Increase a reference counter
    int32_t AddRef();

    //! Decrease a reference counter
    int32_t Release();

    const char16_t* GetInstanceName() const;
    void SetInstanceName(const std::u16string& instanceName);
    void SetInstanceName(const char* instanceName);

    //! Get current reference counter
    int32_t GetRef() const { return reference_; }
#endif

    int32_t GetId() const { return id_; }

#if !USE_CBG

    bool GetIsTerminateingEnabled() const;
    void SetIsTerminateingEnabled(bool value);

    /**
        @brief  called when terminating
        @note
        Don't dispose BaseObject here
    */
    virtual void OnTerminating() {}
#endif
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

template <class T, class... Arg>
std::shared_ptr<T> MakeAsdShared(Arg&&... args) {
    return std::shared_ptr<T>(new T(args...), ReferenceDeleter<T>());
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

}  // namespace Altseed2

#endif