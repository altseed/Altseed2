#pragma once

#include <stdint.h>
#include <stdio.h>
#include <atomic>
#include <memory>

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
    int32_t AddRef() { throw "Unimplemented"; }

    //! Decrease a reference counter
    int32_t Release() { throw "Unimplemented"; }

	//! Get current reference counter
	int32_t GetRef() const { return reference_; }
};

}  // namespace altseed