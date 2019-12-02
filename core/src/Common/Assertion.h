#pragma once

#include <assert.h>
#include <string>
#include <exception>

#ifdef NDEBUG
#define ASD_ASSERT(x, message) 
#else
#define ASD_ASSERT(x, message) \
    if (!(x))                                                                                                                            \
        throw std::exception((std::string("Assert : ") + std::string(__FILE__) + " : " + std::to_string(__LINE__) + std::string(" : ") + \
                              std::string(message))                                                                                      \
                                     .c_str());
#endif

#define ASD_VERIFY(x, message) \
    if (!(x))                                                                                                                            \
        throw std::exception((std::string("Verify : ") + std::string(__FILE__) + " : " + std::to_string(__LINE__) + std::string(" : ") + \
                              std::string(message))                                                                                      \
                                     .c_str());
