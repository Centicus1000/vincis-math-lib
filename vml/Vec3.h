#pragma once

#include "Basics.h"

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
struct Vec3
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
    Vec3(float, float, float);
    Vec3(float);
    Vec3();
    
    // Methoden
    float norm() const;
    Vec3 normalized() const;
    
    // Operatoren
    Vec3 operator -() const;
    void operator += (const Vec3& other);
    void operator -= (const Vec3& other);
    void operator *= (float factor);
    void operator /= (float factor);
    
    // Debugging
    friend std::ostream& operator << (std::ostream& os, const Vec3& v);
};


// ----------------------------------------------
// Namespace Methoden

Vec3 operator + (const Vec3& u, const Vec3& v);
Vec3 operator - (const Vec3& u, const Vec3& v);
Vec3 operator * (float factor, const Vec3& v);
Vec3 operator * (const Vec3& v, float factor);
Vec3 operator / (const Vec3& v, float divident);

float distance(const Vec3& u, const Vec3& v);
float dot(const Vec3& u, const Vec3& v);
Vec3 orbit(float yaw, float pitch);
Vec3 cross(const Vec3& a, const Vec3& b);

} /* vml */
