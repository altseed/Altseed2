#pragma once

#include <map>
#include <memory>
#include <mutex>
#include <thread>

#include "../BaseObject.h"

namespace Altseed {

    template<typename T> class Lockable;

    template<typename T>
    class Locked {
    private:
        Lockable<T>& lockable_;
        std::lock_guard<std::mutex> lock;
        
    public:

        Locked(Lockable<T>& lockable) : lockable_(lockable), lock(std::lock_guard<std::mutex>(lockable.valueMtx_)) { }

        T& Get() { return lockable_.value_; }
    };

    template<typename T>
    class Lockable {
        friend class Locked<T>;
    
    private:
        T value_;
        std::mutex valueMtx_;

    public:
        Locked<T> Lock() { return Locked<T>(*this); }
    };

    template<typename T, typename U>
    class ThreadSafeMap {
    private:
        std::map<T, Lockable<U>> map_;
        std::mutex mapMutex_;

    public:
        Lockable<U> & operator [] (T key) {
            std::lock_guard<std::mutex> lock(mapMutex_);
            return map_[key];
        }
    };

} // namespace Altseed
