#include "vml/vec4.h"

using namespace vml;

// ----------------------------------------------
// Konstruktoren

/**
 * @brief Standard Konstruktor.
 *
 * Initialisiert explizit die vier Koordinaten des Vektors.
 */
vec4::vec4(float _x, float _y, float _z, float _w) :
x(_x), y(_y), z(_z), w(_w)
{}

/**
 * @brief Konstruktor mit nur einer Zahl.
 *
 * Initialisiert alle vier Koordinaten mit dem selben Wert.
 *
 * @param all der Wert von allen Koordinaten
 */
vec4::vec4(float all) : vec4(all, all, all, all) {}

/**
 * @brief Array-Konstruktor.
 *
 * Ermöglicht das initialisieren des Vektors über einen std::array
 */
vec4::vec4(std::array<float, size> data) :
vec4(data[0], data[1], data[2], data[3])
{}


/**
 * @brief Nullvektor (Default Konstruktor)
 *
 * Initialisiert alle vier Koordinaten auf 0.
 */
vec4::vec4() : vec4(0.f, 0.f, 0.f, 0.f)
{}


// ----------------------------------------------
// Operatoren

/**
 * @name Mutierende Operatoren
 *
 * Diese Funktionen veränderen die Daten des Vec2.
 */
///@{
/** Invertierung */
vec4 vec4::operator -() const
{
    return vec4(-x, -y, -z, -w);
}
/** Addition */
void vec4::operator += (const vec4& other)
{
    x += other.x; y += other.y; z += other.z; w += other.w;
}
/** Subtraction */
void vec4::operator -= (const vec4& other)
{
    x -= other.x; y -= other.y; z -= other.z; w -= other.w;
}
/** Skalierung mit einem Skalar */
void vec4::operator *= (float factor)
{
    x *= factor; y *= factor; z *= factor; w *= factor;
}
/** Invertierte Skalierung durch Division mit einem Skalar */
void vec4::operator /= (float factor)
{
    x /= factor; y /= factor; z /= factor; w /= factor;
}
///@}

/**
 * @brief Länge des Vektors.
 *
 * Berechnet die zweite Vektornorm (aka die Länge) des Vektors.
 */
float vec4::norm() const
{
    return sqrt(x*x + y*y + z*z + w*w);
}

/**
 * @brief Einheitsvektor.
 *
 * Gibt den Vektor zurück, der in die selbe Richtung zeigt, aber eine Länge von 1 hat. Das wird durch das Dividieren mit der Länge des Vektors erreicht.
 */
vec4 vec4::unit() const
{
    float l { norm() };
    return vec4(x/l, y/l, z/l, w/l);
}


/**
 * @brief Konvertierung zu std::array.
 *
 * Erstellt einen 4-dimensionalen std::array, welcher die Koordinaten des Vec4 enthält.
 */
std::array<float, vec4::size> vec4::array() const
{
    return {x, y, z, w};
}

// ----------------------------------------------
// Namespace Methoden

/**
 * @brief Vektor Addition `+`.
 *
 * Die Summe von zwei Vektoren. Wegen des Kommutativgesetzes ist die Reihenfolge von `u` und `v` egal
 */
vec4 vml::operator + (const vec4& u, const vec4& v)
{
    return vec4(u.x + v.x, u.y + v.y, u.z + v.z, u.w + v.w);
}

/**
 * @brief Vector Subtraktion `-`.
 *
 * Die Differenz von zwei Vektoren oder Punkten. Der resultierende Vektor entspricht dem Vektor zwischen den Punkten `u` und `v` (Spitze minus Anfang).
 */
vec4 vml::operator - (const vec4& u, const vec4& v)
{
    return vec4(u.x - v.x, u.y - v.y, u.z - v.z, u.w + v.w);
}

///@{
/**
 * @brief Multiplikation mit Skalar.
 *
 * Die Skalierung eines Vektors `v` um einen `factor`. Die die Koordinaten des Vektors werden alle mit `factor` multipliziert.
 */
vec4 vml::operator * (const vec4& v, float factor)
{
    return vec4(factor * v.x, factor * v.y, factor * v.z, factor * v.w);
}
vec4 vml::operator * (float factor, const vec4& v)
{
    return vec4(factor * v.x, factor * v.y, factor * v.z, factor * v.w);
}
///@{

/**
 * @brief Division mit Skalar.
 *
 * Die Division eines Vektors `v` und eines Skalars `divident` entspricht der Multiplikation mit dem Kehrwert von `divident`. Diese Operation ist allerdings nicht kommutativ.
 */
vec4 vml::operator / (const vec4& v, float divident)
{
    return vec4(v.x / divident, v.y / divident, v.z / divident, v.w / divident);
}

/**
 * @brief Abstand zwischen zwei Punkten.
 *
 * Die Länge der Differenz aus zwei Vektoren.
 * Die Reihenfolgen von u und v spielt keine Rolle.
 */
float vml::distance(const vec4& u, const vec4& v)
{
    vec4 d{u - v};
    return d.norm();
}

/**
 * @brief Skalarprodukt (dot product).
 *
 * Berechnet das Skaraprodukt von zwei Vektoren `u` und `v`.
 */
float vml::dot(const vec4& u, const vec4& v)
{
    return u.x * v.x + u.y * v.y + u.z * v.z + u.w * v.w;
}

// ----------------------------------------------
// Debugging

/**
 * @brief Print Overload.
 *
 * Gibt die alle vier Koordinaten aus. Dabei werden die runden Klammern `()` zur Begrenzung verwendet.
 *
 * @param os Outstream (cout)
 * @param v ein Vec2
 */
std::ostream& ::vml::operator<< (std::ostream& os, const vec4& v)
{
    os << "(" << v.x << "," << v.y << "," << v.z << "," << v.w << ")";
    return os;
}
