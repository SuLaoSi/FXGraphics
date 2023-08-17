#ifndef _BASIC_PLATFORM_H_
#define _BASIC_PLATFORM_H_

namespace FX {

#if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
    #define FX_WINDOWS
#elif defined(__APPLE__)
    #define FX_APPLE
#else
    #error "Unsupported platform!\n"
#endif

} // namespace FX

#endif // _BASIC_PLATFORM_H_
