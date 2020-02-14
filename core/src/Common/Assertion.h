#pragma once

#include <assert.h>
#include <exception>
#include <stdexcept>
#include <string>

#ifdef NDEBUG
#define ASD_ASSERT(x, message)
#else
#define ASD_ASSERT(x, message)                                                                                          \
    if (!(x))                                                                                                           \
        throw std::runtime_error((std::string("Assert : ") + std::string(__FILE__) + " : " + std::to_string(__LINE__) + \
                                  std::string(" : ") + std::string(message))                                            \
                                         .c_str());
#endif

#define ASD_VERIFY(x, message)                                                                                          \
    if (!(x))                                                                                                           \
        throw std::runtime_error((std::string("Verify : ") + std::string(__FILE__) + " : " + std::to_string(__LINE__) + \
                                  std::string(" : ") + std::string(message))                                            \
                                         .c_str());
