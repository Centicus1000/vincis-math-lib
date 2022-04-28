#ifndef vml_vec4_h
#define vml_vec4_h

#include "basics.h"

#include <array>

namespace vml {

/**
 * @brief Vierdimensionaler Vektor.
 *
 * Vec2 ist die vml Implementierung eines 2D-Vektors. Die API ist inspiriert von [GLSL](https://www.khronos.org/opengl/wiki/Data_Type_(GLSL)).
 * `vec4 = (x,y,z,w)`
 */
struct vec4
{
    /// Dimension des Vektor
    static const int size { 4 };

    ///@{
    /// Die Koordinaten
    float x;
    float y;
    float z;
    float w;
    ///@}
    
    // Konstruktoren
    vec4(float, float, float, float);
    vec4(float);
    vec4(std::array<float, size>);
    vec4();
    
    // Methoden
    float norm() const;
    vec4 unit() const;
    std::array<float, size> array() const;
    
    // Operatoren
    vec4 operator -() const;
    void operator += (const vec4&);
    void operator -= (const vec4&);
    void operator *= (float);
    void operator /= (float);
    
    // Debugging
    friend std::ostream& operator << (std::ostream&, const vec4&);
};

// ----------------------------------------------
// Namespace Methoden

vec4 operator + (const vec4& u, const vec4& v);
vec4 operator - (const vec4& u, const vec4& v);
vec4 operator * (const vec4& v, float factor);
vec4 operator * (float factor, const vec4& v);
vec4 operator / (const vec4& v, float divident);

float distance(const vec4& u, const vec4& v);
float dot(const vec4& u, const vec4& v);

} /* vml */
#endif /* vml_vec4_h */
