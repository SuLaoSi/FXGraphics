#ifndef _MATH_COMMON_H_
#define _MATH_COMMON_H_

#include <type_traits>

namespace FX {

    namespace Math {

        constexpr double TOLERANCE = 1e-6;

        template<typename T>
        inline bool isZero(T num, float tol = TOLERANCE)
        {
            static_assert(std::is_floating_point<T>::value || std::is_integral<T>::value, "Only basic data types can be compared with 0.");
            
            if (std::is_floating_point<T>::value)
            {
                return -tol < num && num < tol;
            }
            else
            {
                return num == 0;
            }
        }

        template<typename T>
        inline bool isEqual(T left, T right, float tol = TOLERANCE)
        {
            static_assert(std::is_floating_point<T>::value || std::is_integral<T>::value, "Only basic data types can be compared with 0.");

            if (std::is_floating_point<T>::value)
            {
                auto def = left - right;
                return -tol < def && def < tol;
            }
            else
            {
                return left == right;
            }
        }

    } // namespace Math

} // namespace FX

#endif // _MATH_COMMON_H_
