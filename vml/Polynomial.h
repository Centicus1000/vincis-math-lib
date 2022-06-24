#pragma once

#include "Basics.h"
#include "Complex.h"
#include "parse.h"

#include <vector>

namespace vml
{

/**
 coefficient representation of a polynomial
 */

class Polynomial
{
    // attributes
    std::vector<float> coeffs;
    
public:
    // constructor
    Polynomial();
    Polynomial(std::vector<float> _coeffs);
    
    // subsciption
    const float& operator[] (int) const; // query coeffs
    float& operator[] (int); // query coeffs
    
    // methods
    int degree() const; // size of coeffs - 1
    Polynomial derivative() const;
    void resize(int);
    void shrinkToFit();
    
    // evaluation (call operator)
    template <typename T> T operator() (const T&) const;
    
    // parse string
//    static Polynomial parse(std::string&);
    
    // polynomial multiplication via FFT
    friend Polynomial operator * (const Polynomial&, const Polynomial&);
};

// ----------------------------------------------
// Evaluation

/// polynom value
/// calulates the output of the polynomial given a ceratin input
/// T can be any number type (float, int, or vml::Complex)
/// overloads the function call operator ()
/// in O(n) time complexity
/// (has to be in .h according to https://stackoverflow.com/a/3261131/5416171)
/// @param x input
template <typename T> T Polynomial::operator() (const T& x) const
{
    T xi    { 1. }; // tracks the powers of x
    T y     { 0. }; // tracks the output
    
    for (float c : coeffs)
    {
        y  += c * xi;
        xi *= x;
    }
    return y;
}


// ----------------------------------------------
// Parsing

std::ostream& operator << (std::ostream&, const Polynomial&);

namespace parse
{

bool stoPolynomial(Polynomial&, const String&);
String toString(const Polynomial&);

} /* namespace parse */
} /* namespace vml */
