#include "vml/vec4.h"

using namespace vml;

// ----------------------------------------------
// Constructors

/**
 * @brief Standard Constructor.
 *
 * Initializes the four coordinates explicitly via parameter input. The order of the parameter corresponds to x, y, z, w.
 */
vec4::vec4(float _x, float _y, float _z, float _w) :
x(_x), y(_y), z(_z), w(_w)
{}

/**
 * @brief Single Number Constructor.
 *
 * Initializes all four attributes to the same value which is supplied via parameter input. This calls the Standard Constructor.
 *
 * @param all the value that all attributes are set to
 */
vec4::vec4(float all) : vec4(all, all, all, all) {}


/**
 * @brief Zero Element  (Default Constructor)
 *
 * Initializes all four attributes to the default value of zero. This calls the Standard Constructor.
 */
vec4::vec4() : vec4(0.f, 0.f, 0.f, 0.f)
{}


// ----------------------------------------------
// Operators

/**
 * @brief Inversion.
 *
 * Applying the non-binary minus operator, the signs of all attributes is toggled. Positives become negative and vice versa.
 */
vec4 vec4::operator -() const
{
    return vec4(-x, -y, -z, -w);
}

/**
 * @brief Add Assignment.
 *
 * Adds the attributes of a different vec4 to the attributes of this vec4.
 * @param other a vec4 whose values are added to this vec4's attributes
 */
void vec4::operator += (const vec4& other)
{
    x += other.x; y += other.y; z += other.z; w += other.w;
}

/**
 * @brief Subtraction Assignment.
 *
 * Subtracts the attributes of a different vec4 from the attributes of this vec4.
 * @param other a vec4 whose values are subtracted from this vec4's attributes
 */
void vec4::operator -= (const vec4& other)
{
    x -= other.x; y -= other.y; z -= other.z; w -= other.w;
}

/**
 * @brief Scalar Scaling.
 *
 * Scales the attributes linearly by multiplying them with a scalar factor.
 * @param factor scalar which in multiplied to all attributes
 */
void vec4::operator *= (float factor)
{
    x *= factor; y *= factor; z *= factor; w *= factor;
}

/**
 * @brief Scalar Divison.
 *
 * Scales the attributes linearly by multiplying them with a scalar factor. The factor is the inverse of the given parameter
 * @param dividend scalar that all attributes are divided by
 */
void vec4::operator /= (float dividend)
{
    float factor{ 1.f/dividend };
    x *= factor; y *= factor; z *= factor; w *= factor;
}

// ----------------------------------------------
// (Other) Methods

/**
 * @brief Vector Length.
 *
 * Calculates the second vector norm, i.e., the Euclidian norm or the vector length. This is the square root all the sum of the squares of all attributes.
 */
float vec4::norm() const
{
    return sqrt(x*x + y*y + z*z + w*w);
}

/**
 * @brief Unit Vector.
 *
 * Returns the a vector of length = 1, pointing in the same direction as this vec4. This is done by dividing each attribute by the length of the vector.
 */
vec4 vec4::unit() const
{
    float l{ 1.f / norm() };
    return vec4(x*l, y*l, z*l, w*l);
}


/**
 * @brief Conversion to `std::array`.
 *
 * Returns a four-dimensional `std::array` containing the four attributes in the order of x, y, z, w.
 */
std::array<float, vec4::size> vec4::array() const
{
    return {x, y, z, w};
}

// ----------------------------------------------
// Namespace Methods

/**
 * @brief Vector Operatoren.
 *
 * Implementation of the binary operators (`+`,`-`,`*`,`/`)  for vec4, which follow the standard math rules
 */
///@{
vec4 vml::operator + (const vec4& u, const vec4& v)
{
    return vec4(u.x + v.x, u.y + v.y, u.z + v.z, u.w + v.w);
}
vec4 vml::operator - (const vec4& u, const vec4& v)
{
    return vec4(u.x - v.x, u.y - v.y, u.z - v.z, u.w + v.w);
}
vec4 vml::operator * (const vec4& v, float factor)
{
    return vec4(factor * v.x, factor * v.y, factor * v.z, factor * v.w);
}
vec4 vml::operator * (float factor, const vec4& v)
{
    return vec4(factor * v.x, factor * v.y, factor * v.z, factor * v.w);
}
vec4 vml::operator / (const vec4& v, float dividend)
{
    float factor{ 1.f / dividend };
    return vec4(factor * v.x, factor * v.y, factor * v.z, factor * v.w);
}
///@}

/**
 * @brief Vector Distance.
 *
 * Calculates the distance between two vectors. This is the length of the vector between u and v. The order of u and v does not matter.
 */
float vml::distance(const vec4& u, const vec4& v)
{
    return (u - v).norm();
}

/**
 * @brief Dot Product.
 *
 * Calculates the dot product of u and v.
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
