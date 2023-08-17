#ifndef _BASIC_VECTOR_H_
#define _BASIC_VECTOR_H_

#include "math_common.h"

namespace FX {

    template<typename T>
    struct vec2 {
        union { T x = 0; T r; T s; };
        union { T y = 0; T g; T t; };

        bool isZero(void) const
        {
            return Math::isZero(this->x) && Math::isZero(this->y);
        }

        bool operator==(const vec2& other) const
        {
            return Math::isEqual(this->x, other.x) && Math::isEqual(this->y, other.y);
        }

        bool operator!=(const vec2& other) const
        {
            return !Math::isEqual(this->x, other.x) || !Math::isEqual(this->y, other.y);
        }

        vec2& operator=(const vec2& other)
        {
            if (this != &other)
            {
                this->x = other.x;
                this->y = other.y;
            }
            return *this;
        }
    };

    using vec2f = vec2<float>;
    using vec2i = vec2<int>;
    using vec2us = vec2<unsigned short>;

    template<typename T>
    struct vec3 {
        union { T x = 0; T r; T s; };
        union { T y = 0; T g; T t; };
        union { T z = 0; T b; T p; };

        bool isZero(void) const
        {
            return Math::isZero(this->x) && Math::isZero(this->y) && Math::isZero(this->z);
        }

        bool operator==(const vec3& other) const
        {
            return Math::isEqual(this->x, other.x) && Math::isEqual(this->y, other.y) && Math::isEqual(this->z, other.z);
        }

        bool operator!=(const vec3& other) const
        {
            return !Math::isEqual(this->x, other.x) || !Math::isEqual(this->y, other.y) || !Math::isEqual(this->z, other.z);
        }

        vec3& operator=(const vec3& other)
        {
            if (this != &other)
            {
                this->x = other.x;
                this->y = other.y;
                this->z = other.z;
            }
            return *this;
        }
    };

    using vec3f = vec3<float>;
    using vec3i = vec3<int>;
    using vec3us = vec3<unsigned short>;

    template<typename T>
    struct vec4 {
        union { T x = 0; T r; T s; };
        union { T y = 0; T g; T t; };
        union { T z = 0; T b; T p; };
        union { T w = 0; T a; T q; };

        bool isZero(void) const
        {
            return Math::isZero(this->x) && Math::isZero(this->y) && Math::isZero(this->z) && Math::isZero(this->w);
        }

        bool operator==(const vec4& other) const
        {
            return Math::isEqual(this->x, other.x) && Math::isEqual(this->y, other.y) && Math::isEqual(this->z, other.z) && Math::isEqual(this->w, other.w);
        }

        bool operator!=(const vec4& other) const
        {
            return !Math::isEqual(this->x, other.x) || !Math::isEqual(this->y, other.y) || !Math::isEqual(this->z, other.z) || !Math::isEqual(this->w, other.w);
        }

        vec4& operator=(const vec4& other)
        {
            if (this != &other)
            {
                this->x = other.x;
                this->y = other.y;
                this->z = other.z;
                this->w = other.w;
            }
            return *this;
        }
    };

    using vec4f = vec4<float>;
    using vec4i = vec4<int>;
    using vec4us = vec4<unsigned short>;

} // namespace FX

#endif // _BASIC_VECTOR_H_
