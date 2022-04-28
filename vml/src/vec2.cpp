#include "vml/vec2.h"

using namespace vml;

// ----------------------------------------------
// Konstruktoren

/**
 * @brief Standard Konstruktor.
 *
 * Initialisiert explizit die x- und y-Koordinate des Vektors.
 */
vec2::vec2(float _x, float _y) : x(_x), y(_y)
{}

/**
 * @brief Konstruktor mit nur einer Zahl.
 *
 * Initialisiert beide Koordinaten mit dem selben Wert.
 *
 * @param both der Wert von der x- und y-Koordinate
 */
vec2::vec2(float both) : vec2(both, both)
{}

/**
 * @brief Nullvektor (Default Konstruktor)
 *
 * Initialisiert beide Koordinaten auf 0.
 */
vec2::vec2() : vec2(0.f, 0.f)
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
vec2 vec2::operator -() const
{
    return vec2(-x, -y);
}
/** Addition */
void vec2::operator += (const vec2& other)
{
    x += other.x; y += other.y;
}
/** Subtraction */
void vec2::operator -= (const vec2& other)
{
    x -= other.x; y -= other.y;
}
/** Skalierung mit einem Skalar */
void vec2::operator *= (float factor)
{
    x *= factor; y *= factor;
}
/** Invertierte Skalierung durch Division mit einem Skalar */
void vec2::operator /= (float factor)
{
    x /= factor; y /= factor;
}
///@}


/**
 * @brief Länge des Vektors.
 *
 * Berechnet die zweite Vektornorm (aka die Länge) des Vektors.
 */
float vec2::norm() const
{
    return sqrt(x*x + y*y);
}

/**
 * @brief Einheitsvektor.
 *
 * Gibt den Vektor zurück, der in die selbe Richtung zeigt, aber eine Länge von 1 hat. Das wird durch das Dividieren mit der Länge des Vektors erreicht.
 */
vec2 vec2::unit() const
{
    float l{ norm() };
    return vec2(x/l, y/l);
}

/**
 * @brief Rotierter Vektor.
 *
 * Diese Funktioin gibt einen Vektor zurück, der zwar die selbe Länge besitzt, aber um den Winkel `angle` rotiert wurde.
 * Die Rotation erfolgt durch das Multiplizieren mit der Drehmatrix.
 *
 * @param angle Der Roationswinkel.
 */
vec2 vec2::rotated(float angle) const
{
    return vec2(x*cos(angle) - y*sin(angle),
                x*sin(angle) + y*cos(angle));
}

// ----------------------------------------------
// Namespace Methoden

/**
 * @brief Vektor Addition `+`.
 *
 * Die Summe von zwei Vektoren. Wegen des Kommutativgesetzes ist die Reihenfolge von `u` und `v` egal
 */
vec2 vml::operator + (const vec2& u, const vec2& v)
{
    return vec2(u.x + v.x, u.y + v.y);
}

/**
 * @brief Vector Subtraktion `-`.
 *
 * Die Differenz von zwei Vektoren oder Punkten. Der resultierende Vektor entspricht dem Vektor zwischen den Punkten `u` und `v` (Spitze minus Anfang).
 */
vec2 vml::operator - (const vec2& u, const vec2& v)
{
    return vec2(u.x - v.x, u.y - v.y);
}

///@{
/**
 * @brief Multiplikation mit Skalar.
 *
 * Die Skalierung eines Vektors `v` um einen `factor`. Die die Koordinaten des Vektors werden alle mit `factor` multipliziert.
 */
vec2 vml::operator * (float factor, const vec2& v)
{
    return vec2(factor * v.x, factor * v.y);
}
vec2 vml::operator * (const vec2& v, float factor)
{
    return vec2(factor * v.x, factor * v.y);
}
///@}

/**
 * @brief Division mit Skalar.
 *
 * Die Division eines Vektors `v` und eines Skalars `divident` entspricht der Multiplikation mit dem Kehrwert von `divident`. Diese Operation ist allerdings nicht kommutativ.
 */
vec2 vml::operator / (const vec2& v, float divident)
{
    return vec2(v.x / divident, v.y / divident);
}

/**
 * @brief Polare Konstruktion eines Einheitsvektors
 *
 * Konstruiert einen Vektor mit einer Länge `= 1` (Einheitsvektor), welcher in die Richtung von `angle` zeigt. Dabei zeigt der resultierende Vektor in Richtung der x-Achse, sobald `angle=0` gilt. Der Winkel wird in Radiant angegeben.
 *
 * @param angle Winkel zwischen x-Achse und resultierendem Vektor
 */
vec2 vml::polar(float angle)
{
    return vec2(cos(angle), sin(angle));
}

/**
 * @brief Abstand zwischen zwei Punkten.
 *
 * Die Länge der Differenz aus zwei Vektoren.
 * Die Reihenfolgen von u und v spielt keine Rolle.
 */
float vml::distance(const vec2& u, const vec2& v)
{
    vec2 d{u - v};
    return d.norm();
}

/**
 * @brief Skalarprodukt (dot product).
 *
 * Berechnet das Skaraprodukt von zwei Vektoren `u` und `v`.
 */
float vml::dot(const vec2& u, const vec2& v)
{
    return u.x * v.x + u.y * v.y;
}

// ----------------------------------------------
// Debugging

/**
 * @brief Print Overload.
 *
 * Gibt die x- und y-Koordinaten aus.
 * Es wird das Klammerformat `(x,y)` verwendet, da es mit der TikZ-Syntax kombinierbar ist.
 *
 * @param os Outstream (cout)
 * @param v ein Vec2
 */
std::ostream& ::vml::operator<< (std::ostream& os, const vec2& v)
{
    os << "(" << v.x << "," << v.y << ")";
    return os;
}
