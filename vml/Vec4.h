#pragma once

#include "Basics.h"

#include <array>

namespace vml {

/**
 * @brief 4D Vector.
 *
 * Vec4 is the vml:: implementation of a four dimensional vector object. The API is designed to be similar to GLSL: `Vec4 = (x, y, z, w)`.
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
    Float x, y, z, w;

    // Constructors
    Vec4(Float, Float, Float, Float);
    Vec4(Float);
    Vec4();

    /**
     * @brief Templated Array Constructor.
     *
     * Enables initialization of a Vec4 by passing an instance of a type that supports the sub^^scription operator, e.g., std::vector or std::array. This enables easy conversion from other C++libraries to vml-compatible data.
     */
    template<typename ArrayType>
    Vec4(const ArrayType& data) :
    Vec4(data[0], data[1], data[2], data[3])
    {}

    // Methods
    Float norm() const;
    Vec4 normalized() const;
    std::array<Float, size> array() const;

    // Subscription
    /// @Todo: subscription, to allow for array style member access, member should be stored sequentially, so no flow control is needed.

    // Operators
    Vec4 operator -() const;
    void operator += (const Vec4&);
    void operator -= (const Vec4&);
    void operator *= (Float);
    void operator /= (Float);

    // Debugging
    friend std::ostream& operator << (std::ostream&, const Vec4&);
};

// ----------------------------------------------
// Namespace Methods

Vec4 operator + (const Vec4& u, const Vec4& v);
Vec4 operator - (const Vec4& u, const Vec4& v);
Vec4 operator * (const Vec4& v, Float factor);
Vec4 operator * (Float factor, const Vec4& v);
Vec4 operator / (const Vec4& v, Float dividend);

Float distance(const Vec4& u, const Vec4& v);
Float dot(const Vec4& u, const Vec4& v);

///@Todo: Parsing

} /* vml */
