#ifndef vml_vec2_h
#define vml_vec2_h

#include "basics.h"
#include "parse.h" // vec2.h add some functionaliy to parse namespace

#include <string> // for parsing

namespace vml {

/**
 * @brief Zweidimensionaler Vektor.
 *
 * Vec2 ist die vml Implementierung eines 2D-Vektors. Die API ist inspiriert von [GLSL](https://www.khronos.org/opengl/wiki/Data_Type_(GLSL)).
 * `vec2 = (x,y)`
 */
struct vec2
{
    /// Dimension des Vektor
    static const int size{ 2 };

    
    /// Die x-Koordinate
    float x;
    /// Die y-Koordinate
    float y;

    // Konstruktoren
    vec2(float, float);
    vec2(float);
    vec2();

    // Methoden
    float norm() const;
    vec2 unit() const;
    vec2 rotated(float) const;
    
    // Operatoren
    vec2 operator -() const;
    void operator += (const vec2&);
    void operator -= (const vec2&);
    void operator *= (float);
    void operator /= (float);
};

// ----------------------------------------------
// Namespace Methoden

vec2 operator + (const vec2& u, const vec2& v);
vec2 operator - (const vec2& u, const vec2& v);
vec2 operator * (float factor, const vec2& v);
vec2 operator * (const vec2& v, float factor);
vec2 operator / (const vec2& v, float divident);
std::ostream& operator << (std::ostream&, const vec2&);


vec2 polar(float angle);
float distance(const vec2& u, const vec2& v);
float dot(const vec2& u, const vec2& v);


// String conversion
namespace parse {

bool stoV2(vec2&, const String&);
bool stoV2vec(std::vector<vec2>&, const String&);
String to_string(const vec2&);

} /* namespace parse */

} /* namespace vml */
#endif /* vml_vec2_h */
