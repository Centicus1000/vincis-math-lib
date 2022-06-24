#pragma once

#include "Basics.h"
#include "parse.h"

#include <string> // for parsing

namespace vml
{

/**
 * @brief 2D Vector.
 *
 * Vec2 is the vml:: implementation of a two dimensional vector object. The API is designed to be similar to GLSL: `Vec2 = (x,y)`.
 * @seealso https://www.khronos.org/opengl/wiki/Data_Type_(GLSL)
 */
struct Vec2
{
    /// vector dimensions
    static const int size{ 2 };

    
    // Attributes
    /**
     * @brief The Coordinates.
     *
     * The coordinates are stored as named members of the Vec2-struct to allow for convenient member call via the `.`-operator.
     */
    Float x, y;

    // Constructors
    Vec2(Float, Float);
    Vec2(Float);
    Vec2();

    // Methods
    Float norm() const;
    Vec2 normalized() const;
    Vec2 rotated(Float) const;
    std::string TikZ(const char*) const;
    
    // Subscription
    /// @Todo: subscription, to allow for array style member access, member should be stored sequentially, so no flow control is needed.

    // Operators
    Vec2 operator -() const;
    void operator += (const Vec2&);
    void operator -= (const Vec2&);
    void operator *= (Float);
    void operator /= (Float);
};

// ----------------------------------------------
// Namespace Methods

Vec2 operator + (const Vec2& u, const Vec2& v);
Vec2 operator - (const Vec2& u, const Vec2& v);
Vec2 operator * (Float factor, const Vec2& v);
Vec2 operator * (const Vec2& v, Float factor);
Vec2 operator / (const Vec2& v, Float dividend);
std::ostream& operator << (std::ostream&, const Vec2&);

Vec2 polar(Float angle);
Float distance(const Vec2& u, const Vec2& v);
Float dot(const Vec2& u, const Vec2& v);


// ----------------------------------------------
// Parsing
namespace parse
{

bool stoV2(Vec2&, const String&);
bool stoV2vec(std::vector<Vec2>&, const String&);
String toString(const Vec2&);

} /* namespace parse */

} /* namespace vml */
