#pragma once

#include "basics.h"

#include <array>

namespace vml {

/**
 * @brief 4D vector.
 *
 * Vec4 is the vml:: implementation of a four dimensional vector object. The API is designed to be similar to GLSL: `Vec4 = (x,y,z,w)`.
 * @seealso https://www.khronos.org/opengl/wiki/Data_Type_(GLSL)
 */
struct Vec4
{
    /// vector dimensions
    static const int size{ 4 };

    // Attributes
    /**
     * @brief The Coordinates.
     *
     * The coordinates are stored as named members of the Vec4-struct to allow for convenient member call via the `.`-operator.
     */
    float x, y, z, w;

    // Constructors
    Vec4(float, float, float, float);
    Vec4(float);
    Vec4();

    /**
     * @brief Templated Array Constructor.
     *
     * Enables initialisation of a Vec4 by passing an instance of a type that support the subscription operator, e.g. std::vector or std::array. This enable easy conversion from other C++libraries to vml-compatible data.
     */
    template<typename ArrayType>
    Vec4(const ArrayType& data) :
    Vec4(data[0], data[1], data[2], data[3])
    {}

    // Methods
    float norm() const;
    Vec4 unit() const;
    std::array<float, size> array() const;

    // subscription
    /// @Todo: subscription, to allow for array style member access, member should be stored sequentially, so no flow control is needed.

    // Operators
    Vec4 operator -() const;
    void operator += (const Vec4&);
    void operator -= (const Vec4&);
    void operator *= (float);
    void operator /= (float);

    // Debugging
    friend std::ostream& operator << (std::ostream&, const Vec4&);
};

// ----------------------------------------------
// Namespace Methods

Vec4 operator + (const Vec4& u, const Vec4& v);
Vec4 operator - (const Vec4& u, const Vec4& v);
Vec4 operator * (const Vec4& v, float factor);
Vec4 operator * (float factor, const Vec4& v);
Vec4 operator / (const Vec4& v, float dividend);

float distance(const Vec4& u, const Vec4& v);
float dot(const Vec4& u, const Vec4& v);

} /* vml */
