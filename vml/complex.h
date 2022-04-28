#ifndef vml_complex_hpp
#define vml_complex_hpp

#include "basics.h"

namespace vml {

/**
 *  Complex Number, polar representation
 */

struct Complex
{
    // attributes
    float ampli;
    float phase;
    
    // constructors
    Complex();
    Complex(float);
    Complex(float,float);
    
    // methods
    float re() const;
    float im() const;
    
    void conjugate();
    Complex conjugated() const;
    
    // operators
    Complex operator-() const;
    void operator+= (const Complex&);
    void operator-= (const Complex&);
    void operator*= (const Complex&);
    void operator/= (const Complex&);

    // printing
    friend std::ostream& operator << (std::ostream& os, const Complex& v);
};

// multiplication
Complex operator * (const Complex& u, const Complex& v);
// division
Complex operator / (const Complex& u, const Complex& v);

// cartesian arithmetic
Complex cartesian(float re, float im);
Complex operator + (const Complex& u, const Complex& v);
Complex operator - (const Complex& u, const Complex& v);

// power funtions
Complex c_pow(const Complex& u, const Complex& v);
Complex c_exp(const Complex& u);
Complex c_sqrt(const Complex& u);

// constants
const Complex J { Complex(1.f, .5f * pi) };

} /* vml */

#endif /* vml_complex_hpp */
