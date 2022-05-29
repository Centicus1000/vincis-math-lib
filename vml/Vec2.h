#pragma once

#include "Basics.h"
#include "parse.h" // Vec2.h add some functionaliy to parse namespace

#include <string> // for parsing

namespace vml {

/**
 * @brief Zweidimensionaler Vektor.
 *
 * Vec2 ist die vml Implementierung eines 2D-Vektors. Die API ist inspiriert von [GLSL](https://www.khronos.org/opengl/wiki/Data_Type_(GLSL)).
 * `Vec2 = (x,y)`
 */
struct Vec2
{
    /// Dimension des Vektor
    static const int size{ 2 };

    
    /// Die x-Koordinate
    float x;
    /// Die y-Koordinate
    float y;

    // Konstruktoren
    Vec2(float, float);
    Vec2(float);
    Vec2();

    // Methoden
    float norm() const;
    Vec2 unit() const;
    Vec2 rotated(float) const;
    
    // Operatoren
    Vec2 operator -() const;
    void operator += (const Vec2&);
    void operator -= (const Vec2&);
    void operator *= (float);
    void operator /= (float);
};

// ----------------------------------------------
// Namespace Methoden

Vec2 operator + (const Vec2& u, const Vec2& v);
Vec2 operator - (const Vec2& u, const Vec2& v);
Vec2 operator * (float factor, const Vec2& v);
Vec2 operator * (const Vec2& v, float factor);
Vec2 operator / (const Vec2& v, float divident);
std::ostream& operator << (std::ostream&, const Vec2&);


Vec2 polar(float angle);
float distance(const Vec2& u, const Vec2& v);
float dot(const Vec2& u, const Vec2& v);


// String conversion
namespace parse {

bool stoV2(Vec2&, const String&);
bool stoV2vec(std::vector<Vec2>&, const String&);
String to_string(const Vec2&);

} /* namespace parse */

} /* namespace vml */
