#include "vml/vec3.h"

using namespace vml;

// ----------------------------------------------
// Konstruktoren

/**
 * @brief Standar Konstruktor.
 *
 * Initialisiert explizit die x-, y- und z-Koordinate des Vektors.
 */
Vec3::Vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z)
{}

/**
 * @brief Konstruktor mit nur einer Zahl.
 *
 * Initialisiert alle drei Koordinaten mit dem selben Wert.
 *
 * @param all der Wert von der x-, y- und z-Koordinate
 */
Vec3::Vec3(float all) : Vec3(all, all, all)
{}

/**
 * @brief Nullvektor (Default Konstruktor)
 *
 * Initialisiert beide Koordinaten auf 0.
 */
Vec3::Vec3() : Vec3(0.f, 0.f, 0.f)
{}


// ----------------------------------------------
// Operatoren

/**
 * @name Mutierende Operatoren
 *
 * Diese Funktionen veränderen die Daten des Vec3.
 */
///@{
/** Invertierung */
Vec3 Vec3::operator -() const
{
    return Vec3(-x, -y, -z);
}
/** Addition */
void Vec3::operator += (const Vec3& other)
{
    x += other.x; y += other.y; z += other.z;
}
/** Subtraction */
void Vec3::operator -= (const Vec3& other)
{
    x -= other.x; y -= other.y; z -= other.z;
}
/** Skalierung mit einem Skalar */
void Vec3::operator *= (float factor)
{
    x *= factor; y *= factor; z *= factor;
}
/** Invertierte Skalierung durch Division mit einem Skalar */
void Vec3::operator /= (float factor)
{
    x /= factor; y /= factor; z /= factor;
}
///@}


/**
 * @brief Länge des Vektors.
 *
 * Berechnet die zweite Vektornorm (aka die Länge) des Vektors.
 */
float Vec3::norm() const
{
    return sqrt(x*x + y*y + z*z);
}

/**
 * @brief Einheitsvektor.
 *
 * Gibt den Vektor zurück, der in die selbe Richtung zeigt, aber eine Länge von 1 hat. Das wird durch das Dividieren mit der Länge des Vektors erreicht.
 */
Vec3 Vec3::normalized() const
{
    float l { norm() };
    return Vec3(x/l, y/l, z/l);
}

// ----------------------------------------------
// Namespace Methoden

/**
 * @brief Vektor Addition `+`.
 *
 * Die Summe von zwei Vektoren. Wegen des Kommutativgesetzes ist die Reihenfolge von `u` und `v` egal
 */
Vec3 vml::operator + (const Vec3& u, const Vec3& v)
{
    return Vec3(u.x + v.x, u.y + v.y, u.z + v.z);
}

/**
 * @brief Vector Subtraktion `-`.
 *
 * Die Differenz von zwei Vektoren oder Punkten. Der resultierene Vektor entspricht dem Vektor zwischen den Punkten `u` und `v` (Spitze minus Anfang).
 */
Vec3 vml::operator - (const Vec3& u, const Vec3& v)
{
    return Vec3(u.x - v.x, u.y - v.y, u.z - v.z);
}

///@{
/**
 * @brief Skalare Multiplikation.
 *
 * Die Skalierung eines Vektors `v` um einen `factor`. Die die Koordinaten des Vektors werden alle mit `factor` multipliziert.
 */
Vec3 vml::operator * (float factor, const Vec3& v)
{
    return Vec3(factor * v.x, factor * v.y, factor * v.z);
}
Vec3 vml::operator * (const Vec3& v, float factor)
{
    return Vec3(factor * v.x, factor * v.y, factor * v.z);
}
///@}

/**
 * @brief Skalare Division.
 *
 * Die Division eines Vektors `v` und eines Skalars `a` entspricht der Multiplikation mit dem Kehrwert von `a`. Diese Operation ist allerdings nicht kommutativ.
 */
Vec3 vml::operator / (const Vec3& v, float divident)
{
    return Vec3(v.x / divident, v.y / divident, v.z / divident);
}

/**
 * @brief Abstand zwischen zwei Punkten.
 *
 * Die Länge der Differenz aus zwei Vektorn.
 * Die Reihenfolgen von u und v spielt keine Rolle.
 */
float vml::distance(const Vec3& u, const Vec3& v)
{
    Vec3 d{u - v};
    return d.norm();
}

/**
 * @brief Skalarprodukt (dot product).
 *
 * Berechet das Skaraprodukt von zwei Vektoren `u` und `v`.
 */
float vml::dot(const Vec3& u, const Vec3& v)
{
    return u.x * v.x + u.y * v.y + u.z * v.z;
}


/**
 * @brief Orbit Vektor.
 *
 * Diese Funktion erzeugt einen Einheitsvektor über zwei Winkel
 *
 * @param yaw Stellt die Drehung des Vektors innerhalb der x-z-Ebene ein.
 * @param pitch Entspricht dem Winkel zwischen dem Vektor und der x-z-Ebene.
 */
Vec3 vml::orbit(float yaw, float pitch)
{
    return Vec3(cos(yaw) * cos(pitch), sin(pitch), sin(yaw) * cos(pitch));
}

/**
 * @brief Kreuzproduct (cross product).
 *
 * Berechnet das [Kreuzproduct](https://de.wikipedia.org/wiki/Kreuzprodukt) aus den Vektoren `u` und `v`.
 * Das Ergebnis ist ein Vektor, welche rechtwinklig zu den beiden Eingangsvektoren steht und dessen Längen dem Produkt der Eingangslängen entspricht.
 */
Vec3 vml::cross(const Vec3& u, const Vec3& v)
{
    return Vec3(u.y * v.z - u.z * v.y,
                u.z * v.x - u.x * v.z,
                u.x * v.y - u.y * v.x);
}

// ----------------------------------------------
// Debugging

/**
 * @brief Print Overload.
 *
 * Printet die x-, y- und z-Koordinate.
 *
 * @param os Outstream (cout)
 * @param v ein Vec3
 */
std::ostream& ::vml::operator<< (std::ostream& os, const Vec3& v)
{
    os << "(" << v.x << "," << v.y << "," << v.z << ")";
    return os;
}
