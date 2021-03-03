#pragma once

#ifndef NDEBUG
#include "debug_new.h"
#endif

template<class C>
class LeakDetector {
public:
    LeakDetector() noexcept {
        get().n += 1;
    }

    LeakDetector(const LeakDetector &) noexcept {
        get().n += 1;
    }

    LeakDetector &operator=(const LeakDetector &) noexcept = default;

    ~LeakDetector() {
        if (--(get().n) < 0) {
            std::cerr << "!!!! DELETED A DANGLING POINTER TO " << className() << std::endl;
        }
    }

private:
    class LeakCounter
    {
    public:
        LeakCounter() = default;
        ~LeakCounter()
        {
            if (n > 0)
            {
                std::cerr << "!!!! LEAKED " << n << " INSTANCES OF " << className() << std::endl;
            }
        }

        std::atomic<int> n;
    };

    static const char *className() {
        return C::classNameForLeakReport();
    }

    static LeakCounter& get() noexcept {
        static LeakCounter c;
        return c;
    }
};

#ifdef NDEBUG
#define LEAK_DETECTOR(OwnerClass)
#else
#define LEAK_DETECTOR(OwnerClass) \
        friend class LeakDetector<OwnerClass>; \
        static const char* classNameForLeakReport() noexcept { return #OwnerClass; } \
        LeakDetector<OwnerClass> leakDetector ## __LINE__;
#endif
