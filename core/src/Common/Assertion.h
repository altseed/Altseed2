#pragma once

#include <assert.h>

#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>

#ifdef NDEBUG
#define ASD_ASSERT_FORCE(message)
#define ASD_ASSERT(x, message)
#else
#define ASD_ASSERT_FORCE(message)                                                                                           \
    {                                                                                                                       \
        auto msg =                                                                                                          \
                (std::string("Assert : ") + std::string(__FILE__) + " : " + std::to_string(__LINE__) + std::string(" : ") + \
                 std::string(message));                                                                                     \
        std::cout << msg << std::endl;                                                                                      \
        throw std::runtime_error(msg.c_str());                                                                              \
    }
#define ASD_ASSERT(x, message) \
    if (!(x)) ASD_ASSERT_FORCE(message)
#endif

#define ASD_VERIFY(x, message)                                                                                              \
    if (!(x)) {                                                                                                             \
        auto msg =                                                                                                          \
                (std::string("Verify : ") + std::string(__FILE__) + " : " + std::to_string(__LINE__) + std::string(" : ") + \
                 std::string(message));                                                                                     \
        std::cout << msg << std::endl;                                                                                      \
        throw std::runtime_error(msg.c_str());                                                                              \
    }
