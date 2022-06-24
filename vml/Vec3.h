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
    Float x;
    /// Die y-Koordinate
    Float y;
    /// Die z-Koordinate
    Float z;
    
    // Konstruktoren
    Vec3(Float, Float, Float);
    Vec3(Float);
    Vec3();
    
    // Methoden
    Float norm() const;
    Vec3 normalized() const;
    
    // Operatoren
    Vec3 operator -() const;
    void operator += (const Vec3& other);
    void operator -= (const Vec3& other);
    void operator *= (Float factor);
    void operator /= (Float factor);
    
    // Debugging
    friend std::ostream& operator << (std::ostream& os, const Vec3& v);
};


// ----------------------------------------------
// Namespace Methoden

Vec3 operator + (const Vec3& u, const Vec3& v);
Vec3 operator - (const Vec3& u, const Vec3& v);
Vec3 operator * (Float factor, const Vec3& v);
Vec3 operator * (const Vec3& v, Float factor);
Vec3 operator / (const Vec3& v, Float divident);

Float distance(const Vec3& u, const Vec3& v);
Float dot(const Vec3& u, const Vec3& v);
Vec3 orbit(Float yaw, Float pitch);
Vec3 cross(const Vec3& a, const Vec3& b);


// ----------------------------------------------
// Parsing
namespace parse
{

bool stoV3(Vec3&, const String&);
bool stoV3vec(std::vector<Vec3>&, const String&);
String toString(const Vec3&);

} /* namespace parse */

} /* namespace vml */
