#ifndef vml_vec3_h
#define vml_vec3_h

#include "basics.h"

namespace vml {


/**
 * @brief Dreidimensionaler Vektor.
 *
 * Vec3 ist die vml Implementierung eines 3D-Vektors. Die API ist inspiriert von [GLSL](https://www.khronos.org/opengl/wiki/Data_Type_(GLSL)).
 * Die Achsen korrespondieren zu den OpenGL-Achsen:
 *  - x-Achse: Links nach Rechts
 *  - y-Achse: Unten nach Oben
 *  - z-Achse: Vorne nach Hinten
 */
struct vec3
{
    /// Dimension des Vektor
    static const int size{ 3 };
    
    /// Die x-Koordinate
    float x;
    /// Die y-Koordinate
    float y;
    /// Die z-Koordinate
    float z;
    
    // Konstruktoren
    vec3(float, float, float);
    vec3(float);
    vec3();
    
    // Methoden
    float norm() const;
    vec3 normalized() const;
    
    // Operatoren
    vec3 operator -() const;
    void operator += (const vec3& other);
    void operator -= (const vec3& other);
    void operator *= (float factor);
    void operator /= (float factor);
    
    // Debugging
    friend std::ostream& operator << (std::ostream& os, const vec3& v);
};


// ----------------------------------------------
// Namespace Methoden

vec3 operator + (const vec3& u, const vec3& v);
vec3 operator - (const vec3& u, const vec3& v);
vec3 operator * (float factor, const vec3& v);
vec3 operator * (const vec3& v, float factor);
vec3 operator / (const vec3& v, float divident);

float distance(const vec3& u, const vec3& v);
float dot(const vec3& u, const vec3& v);
vec3 orbit(float yaw, float pitch);
vec3 cross(const vec3& a, const vec3& b);

} /* vml */
#endif /* vml_vec3_h */
