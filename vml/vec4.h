#ifndef vml_vec4_h
#define vml_vec4_h

#include "basics.h"

#include <array>

namespace vml {

/**
 * @brief 4D vector.
 *
 * vec4 is the vml:: implementation of a four dimensional vector object. The API is designed to be similar to GLSL: `vec4 = (x,y,z,w)`.
 * @seealso https://www.khronos.org/opengl/wiki/Data_Type_(GLSL)
 */
struct vec4
{
    /// vector dimenisions
    static const int size{ 4 };

    // Attributes
    /**
     * @brief The Coordinates. namez
     *
     * The coordinates are stored as named members of the vec4-struct to allow for convient member call via the `.`-operator.
     */
    float x, y, z, w;

    // Constructors
    vec4(float, float, float, float);
    vec4(float);
    vec4();

    /**
     * @brief Temaplated Array Constructor.
     *
     * Enables initializasion of a vec4 by passing an instance of a type that support the subscription operator, e.g. std::vector or std::array. This enable easy conversion from other C++libraries to vml-compatible data.
     */
    template<typename ArrayType>
    vec4(const ArrayType& data) :
    vec4(data[0], data[1], data[2], data[3])
    {}

    // Methods
    float norm() const;
    vec4 unit() const;
    std::array<float, size> array() const;

    // subscription
    /// @Todo: subscription, to allow for array style member access, member should be stored sequentially, so no flow control is needed.

    // Operators
    vec4 operator -() const;
    void operator += (const vec4&);
    void operator -= (const vec4&);
    void operator *= (float);
    void operator /= (float);

    // Debugging
    friend std::ostream& operator << (std::ostream&, const vec4&);
};

// ----------------------------------------------
// Namespace Methods

vec4 operator + (const vec4& u, const vec4& v);
vec4 operator - (const vec4& u, const vec4& v);
vec4 operator * (const vec4& v, float factor);
vec4 operator * (float factor, const vec4& v);
vec4 operator / (const vec4& v, float dividend);

float distance(const vec4& u, const vec4& v);
float dot(const vec4& u, const vec4& v);

} /* vml */
#endif /* vml_vec4_h */
