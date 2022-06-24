#pragma once

#include "Basics.h"

namespace vml {

/**
 *  Complex Number, polar representation
 */

struct Complex
{
    // attributes
    Float ampli;
    Float phase;
    
    // constructors
    Complex();
    Complex(Float);
    Complex(Float,Float);
    
    // methods
    Float re() const;
    Float im() const;
    
    void conjugate();
    Complex conjugated() const;
    
    // operators
    Complex operator-() const;
    void operator += (const Complex&);
    void operator -= (const Complex&);
    void operator *= (const Complex&);
    void operator /= (const Complex&);

    // printing
    friend std::ostream& operator << (std::ostream& os, const Complex& v);
};

// multiplication
Complex operator * (const Complex& u, const Complex& v);
// division
Complex operator / (const Complex& u, const Complex& v);

// cartesian arithmetic
Complex cartesian(Float re, Float im);
Complex operator + (const Complex& u, const Complex& v);
Complex operator - (const Complex& u, const Complex& v);

// power functions
Complex pow(const Complex& u, const Complex& v);
Complex exp(const Complex& u);
Complex sqrt(const Complex& u);

// constants
const Complex J { Complex(1.f, .5f * pi) };

} /* vml */
