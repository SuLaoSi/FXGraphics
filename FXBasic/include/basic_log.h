#ifndef _BASIC_LOG_H_
#define _BASIC_LOG_H_

#include <iostream>
#include <chrono>

namespace FX {

    class BasicLog {
    private:
        BasicLog(void) = default;
        ~BasicLog(void) = default;

    public:
        enum LogType : unsigned char {
            kInfo = 0,
            kWarn,
            kError
        };

        template<typename... Messages>
        static void out(LogType type, Messages... messages)
        {
            printPreInfo(type);
            printMessage(messages...);
        }

    private:
        static void printPreInfo(LogType type)
        {
            auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            std::tm stamp = { 0 };
            ::localtime_s(&stamp, &now);
            std::cout << "[";
            stamp.tm_hour < 10 ? std::cout << "0" << stamp.tm_hour : std::cout << stamp.tm_hour;
            std::cout << ":";
            stamp.tm_min < 10 ? std::cout << "0" << stamp.tm_min : std::cout << stamp.tm_min;
            std::cout << ":";
            stamp.tm_sec < 10 ? std::cout << "0" << stamp.tm_sec : std::cout << stamp.tm_sec;
            std::cout << "]";

            switch (type)
            {
                case kInfo:
                    std::cout << "[INFO] ";
                    break;
                case kWarn:
                    std::cout << "[WARN] ";
                    break;
                case kError:
                    std::cout << "[ERROR] ";
                    break;
                default:
                    std::cout << "[----] ";
                    break;
            }
        }

        template<typename Message, typename... Messages>
        static void printMessage(Message message, Messages... messages)
        {
            std::cout << message;
            printMessage(messages...);
        }

        static void printMessage(void)
        {
            std::cout << std::endl;
        }
    };

} // namespace FX

#endif // _BASIC_LOG_H_
