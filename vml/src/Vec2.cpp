#include "vml/Vec2.h"

using namespace vml;

// ----------------------------------------------
// Konstruktoren

/**
 * @brief Standard Konstruktor.
 *
 * Initialisiert explizit die x- und y-Koordinate des Vektors.
 */
Vec2::Vec2(float _x, float _y) : x(_x), y(_y)
{}

/**
 * @brief Konstruktor mit nur einer Zahl.
 *
 * Initialisiert beide Koordinaten mit dem selben Wert.
 *
 * @param both der Wert von der x- und y-Koordinate
 */
Vec2::Vec2(float both) : Vec2(both, both)
{}

/**
 * @brief Nullvektor (Default Konstruktor)
 *
 * Initialisiert beide Koordinaten auf 0.
 */
Vec2::Vec2() : Vec2(0.f, 0.f)
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
Vec2 Vec2::operator -() const
{
    return Vec2(-x, -y);
}
/** Addition */
void Vec2::operator += (const Vec2& other)
{
    x += other.x; y += other.y;
}
/** Subtraction */
void Vec2::operator -= (const Vec2& other)
{
    x -= other.x; y -= other.y;
}
/** Skalierung mit einem Skalar */
void Vec2::operator *= (float factor)
{
    x *= factor; y *= factor;
}
/** Invertierte Skalierung durch Division mit einem Skalar */
void Vec2::operator /= (float factor)
{
    x /= factor; y /= factor;
}
///@}


/**
 * @brief Länge des Vektors.
 *
 * Berechnet die zweite Vektornorm (aka die Länge) des Vektors.
 */
float Vec2::norm() const
{
    return sqrt(x*x + y*y);
}

/**
 * @brief Einheitsvektor.
 *
 * Gibt den Vektor zurück, der in die selbe Richtung zeigt, aber eine Länge von 1 hat. Das wird durch das Dividieren mit der Länge des Vektors erreicht.
 */
Vec2 Vec2::unit() const
{
    float l{ norm() };
    return Vec2(x/l, y/l);
}

/**
 * @brief Rotierter Vektor.
 *
 * Diese Funktioin gibt einen Vektor zurück, der zwar die selbe Länge besitzt, aber um den Winkel `angle` rotiert wurde.
 * Die Rotation erfolgt durch das Multiplizieren mit der Drehmatrix.
 *
 * @param angle Der Roationswinkel.
 */
Vec2 Vec2::rotated(float angle) const
{
    return Vec2(x*cos(angle) - y*sin(angle),
                x*sin(angle) + y*cos(angle));
}

// ----------------------------------------------
// Namespace Methoden

/**
 * @brief Vektor Addition `+`.
 *
 * Die Summe von zwei Vektoren. Wegen des Kommutativgesetzes ist die Reihenfolge von `u` und `v` egal
 */
Vec2 vml::operator + (const Vec2& u, const Vec2& v)
{
    return Vec2(u.x + v.x, u.y + v.y);
}

/**
 * @brief Vector Subtraktion `-`.
 *
 * Die Differenz von zwei Vektoren oder Punkten. Der resultierende Vektor entspricht dem Vektor zwischen den Punkten `u` und `v` (Spitze minus Anfang).
 */
Vec2 vml::operator - (const Vec2& u, const Vec2& v)
{
    return Vec2(u.x - v.x, u.y - v.y);
}

///@{
/**
 * @brief Multiplikation mit Skalar.
 *
 * Die Skalierung eines Vektors `v` um einen `factor`. Die die Koordinaten des Vektors werden alle mit `factor` multipliziert.
 */
Vec2 vml::operator * (float factor, const Vec2& v)
{
    return Vec2(factor * v.x, factor * v.y);
}
Vec2 vml::operator * (const Vec2& v, float factor)
{
    return Vec2(factor * v.x, factor * v.y);
}
///@}

/**
 * @brief Division mit Skalar.
 *
 * Die Division eines Vektors `v` und eines Skalars `divident` entspricht der Multiplikation mit dem Kehrwert von `divident`. Diese Operation ist allerdings nicht kommutativ.
 */
Vec2 vml::operator / (const Vec2& v, float divident)
{
    return Vec2(v.x / divident, v.y / divident);
}

/**
 * @brief Polare Konstruktion eines Einheitsvektors
 *
 * Konstruiert einen Vektor mit einer Länge `= 1` (Einheitsvektor), welcher in die Richtung von `angle` zeigt. Dabei zeigt der resultierende Vektor in Richtung der x-Achse, sobald `angle=0` gilt. Der Winkel wird in Radiant angegeben.
 *
 * @param angle Winkel zwischen x-Achse und resultierendem Vektor
 */
Vec2 vml::polar(float angle)
{
    return Vec2(cos(angle), sin(angle));
}

/**
 * @brief Abstand zwischen zwei Punkten.
 *
 * Die Länge der Differenz aus zwei Vektoren.
 * Die Reihenfolgen von u und v spielt keine Rolle.
 */
float vml::distance(const Vec2& u, const Vec2& v)
{
    Vec2 d{u - v};
    return d.norm();
}

/**
 * @brief Skalarprodukt (dot product).
 *
 * Berechnet das Skaraprodukt von zwei Vektoren `u` und `v`.
 */
float vml::dot(const Vec2& u, const Vec2& v)
{
    return u.x * v.x + u.y * v.y;
}

// ----------------------------------------------
// String Conversion


/**
 * @brief String Parsing Vec2.
 *
 * Ließt die daten von einem String und schriebt sie in einen Vec2.
 * Bei einem erfolgreichen Parsing wird true zurückgegeben.
 * Der String sollte im Tupelformat  "(x,y)" sein um korrekt gelesen zu werden. Whitespaces werden vorher entfernt
 * @param v2 Referenz zu einem Vec2
 * @param s Vec2 als string.
 */
bool ::vml::parse::stoV2(Vec2& v2, const String& s)
{
    // find indicies of special characters
    const auto bl{ s.find_first_of("(") }; // left bracket
    const auto cm{ s.find_first_of(",") }; // comma
    const auto br{ s.find_first_of(")") }; // right bracket
    // return false if one of them doesn't exist
    if (bl==String::npos || cm==String::npos || br==String::npos) return false;
    // write data to Vec2 reference
    try {
    v2.x = std::stof(s.substr(bl + 1, cm));
    v2.y = std::stof(s.substr(cm + 1, br));
    } catch(...){ return false; }
    return true;
}

/**
 * @brief Konvertiere String zu einem Vec2-Vector.
 *
 * Vec2-Vector hat als String dieses Format: "[ (x1, y1), (x2, y2), ..., (xn, yn) ]".
 * Dabei darf nur jedes zweite Komma als Trennzeichen des Vectors interpretiert werden.
 */
bool vml::parse::stoV2vec(std::vector<Vec2>& v2v, const String& s)
{
    v2v.clear();
    // find opening brace
    auto start{ s.find_first_of("[") };
    if (start==String::npos) return false;
    
    // repeadetly find commas and parse string inbetween
    auto stop{ s.find_first_of(",") };
    while (stop!=String::npos)
    {
        // only take every second comma
        stop = s.find_first_of(",", stop+1);
        // no second comma, means last element
        if (stop==String::npos) break;
        // try to parse Vec2 from string and push back
        Vec2 v;
        if (!stoV2(v, s.substr(start+1, stop))) return false;
        v2v.push_back(v);
        // find next comma
        start = stop;
        stop = s.find_first_of(",", start+1);
    }
    // find closing brace
    stop = s.find_first_of("]");
    if (stop==String::npos) return false;
    // empty vector is possible
    if (s[start]=='[') return true;
    // try to parse Vec2 from string and push back
    Vec2 v;
    if (!stoV2(v, s.substr(start+1, stop))) return false;
    v2v.push_back(v);
    v2v.shrink_to_fit();
    return true;
}

#include <sstream>
/**
 * @brief Vec2 als ein String.
 *
 * Konvertiert den Vec2 in einen string.
 * Es wird das Klammerformat `(x,y)` verwendet, da es mit der TikZ-Syntax kombinierbar ist.
 * @param v2 Referenz zu einem Vec2
 */
std::string vml::parse::to_string(const Vec2& v)
{
    std::stringstream ss;
    ss << '(' << v.x << ',' << v.y << ')';
    return ss.str();
}

/**
 * @brief Print Overload.
 *
 * Gibt die x- und y-Koordinaten aus.
 * Es wird das Klammerformat `(x,y)` verwendet, da es mit der TikZ-Syntax kombinierbar ist.
 *
 * @param os Outstream (cout)
 * @param v ein Vec2
 */
std::ostream& vml::operator<< (std::ostream& os, const Vec2& v)
{
    os << parse::to_string(v);
    return os;
}
