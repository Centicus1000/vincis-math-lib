#include "vml/Vec2.h"

using namespace vml;

// ----------------------------------------------
// Constructors

/**
 * @brief Standard Constructor.
 *
 * Initializes the two coordinates explicitly via parameter input. The order of the parameter corresponds to x, y.
 */
Vec2::Vec2(Float _x, Float _y) : x(_x), y(_y)
{}


/**
 * @brief Single Number Constructor.
 *
 * Initializes both attributes to the same value which is supplied via parameter input. This calls the Standard Constructor.
 *
 * @param both the value that all attributes are set to
 */
Vec2::Vec2(Float both) : Vec2(both, both)
{}

/**
 * @brief Zero Element  (Default Constructor)
 *
 * Initializes both attributes to the default value of zero. This calls the Standard Constructor.
 */
Vec2::Vec2() : Vec2(0.f, 0.f)
{}


// ----------------------------------------------
// Operators

/**
 * @brief Inversion.
 *
 * Applying the non-binary minus operator, the signs of all attributes is toggled. Positives become negative and vice versa.
 */
Vec2 Vec2::operator -() const
{
    return Vec2(-x, -y);
}

/**
 * @brief Add Assignment.
 *
 * Adds the attributes of a different Vec2 to the attributes of this Vec2.
 * @param other a Vec2 whose values are added to this Vec2's attributes
 */
void Vec2::operator += (const Vec2& other)
{
    x += other.x; y += other.y;
}

/**
 * @brief Subtraction Assignment.
 *
 * Subtracts the attributes of a different Vec2 from the attributes of this Vec2.
 * @param other a Vec2 whose values are subtracted from this Vec2's attributes
 */
void Vec2::operator -= (const Vec2& other)
{
    x -= other.x; y -= other.y;
}

/**
 * @brief Scalar Scaling.
 *
 * Scales the attributes linearly by multiplying them with a scalar factor.
 * @param factor scalar which in multiplied to all attributes
 */
void Vec2::operator *= (Float factor)
{
    x *= factor; y *= factor;
}

/**
 * @brief Scalar Divison.
 *
 * Scales the attributes linearly by multiplying them with a scalar factor. The factor is the inverse of the given parameter
 * @param dividend scalar that all attributes are divided by
 */
void Vec2::operator /= (Float dividend)
{
    Float factor{ 1.f / dividend};
    x *= factor; y *= factor;
}
///@}

// ----------------------------------------------
// (Other) Methods

/**
 * @brief Vector Length.
 *
 * Calculates the second vector norm, i.e., the Euclidian norm or the vector length. This is the square root all the sum of the squares of all attributes.
 */
Float Vec2::norm() const
{
    return sqrt(x*x + y*y);
}

/**
 * @brief Unit Vector.
 *
 * Returns the a vector of length = 1, pointing in the same direction as this Vec4. This is done by dividing each attribute by the length of the vector.
 */
Vec2 Vec2::normalized() const
{
    Float l{ 1.f / norm() };
    return Vec2(x*l, y*l);
}

/**
 * @brief Rotated Vektor.
 *
 * This function returns a vector that has the same length but has been rotated by `angle`. The rotation is done by multiplying by the rotation matrix.
 *
 * @param angle Angle of rotation (relative to start)
 */
Vec2 Vec2::rotated(Float angle) const
{
    return Vec2(x*cos(angle) - y*sin(angle),
                x*sin(angle) + y*cos(angle));
}

// ----------------------------------------------
// Namespace Methods

/**
 * @brief Vector Operatoren.
 *
 * Implementation of the binary operators (`+`,`-`,`*`,`/`)  for Vec4, which follow the standard math rules
 */
///@{
Vec2 vml::operator + (const Vec2& u, const Vec2& v)
{
    return Vec2(u.x + v.x, u.y + v.y);
}
Vec2 vml::operator - (const Vec2& u, const Vec2& v)
{
    return Vec2(u.x - v.x, u.y - v.y);
}
Vec2 vml::operator * (Float factor, const Vec2& v)
{
    return Vec2(factor * v.x, factor * v.y);
}
Vec2 vml::operator * (const Vec2& v, Float factor)
{
    return Vec2(factor * v.x, factor * v.y);
}
Vec2 vml::operator / (const Vec2& v, Float dividend)
{
    Float factor{ 1.f / dividend };
    return Vec2(factor * v.x, factor * v.y);
}
///@}

/**
 * @brief Vector Distance.
 *
 * Calculates the distance between two vectors. This is the length of the vector between u and v. The order of u and v does not matter.
 */
Float vml::distance(const Vec2& u, const Vec2& v)
{
    return (u - v).norm();
}


/**
 * @brief Polare Konstruktion eines Einheitsvektors
 *
 * Konstruiert einen Vektor mit einer Länge `= 1` (Einheitsvektor), welcher in die Richtung von `angle` zeigt. Dabei zeigt der resultierende Vektor in Richtung der x-Achse, sobald `angle=0` gilt. Der Winkel wird in Radiant angegeben.
 *
 * @param angle Winkel zwischen x-Achse und resultierendem Vektor
 */
Vec2 vml::polar(Float angle)
{
    return Vec2(cos(angle), sin(angle));
}

/**
 * @brief Skalarprodukt (dot product).
 *
 * Berechnet das Skaraprodukt von zwei Vektoren `u` und `v`.
 */
Float vml::dot(const Vec2& u, const Vec2& v)
{
    return u.x * v.x + u.y * v.y;
}

// ----------------------------------------------
// String Conversion

std::string Vec2::TikZ(const char* optionals = "") const
{
    std::stringstream ss{};
    ss << "\\draw[" << optionals << "] ";
    ss << (*this) << " circle(5pt) ;";
    return ss.str();
}


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
    try
    {
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
std::string vml::parse::toString(const Vec2& v)
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
    os << parse::toString(v);
    return os;
}
