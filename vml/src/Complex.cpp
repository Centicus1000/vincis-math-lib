#include "vml/Complex.h"

using namespace vml;

// constructors
Complex::Complex() : Complex(0.f) {}
Complex::Complex(Float _ampli) :
ampli( abs(_ampli) ), phase( .5f* pi *(1 - sign(_ampli)) )
{
    if (ampli==0.f) phase = 0.f;
}

Complex::Complex(Float _ampli, Float _phase) : Complex(_ampli)
{
    phase += _phase;
}

// member methods
Float   Complex::re         () const { return ampli * cos(phase); }
Float   Complex::im         () const { return ampli * sin(phase); }
void    Complex::conjugate  ()       { phase *= -1.f; }
Complex Complex::conjugated () const { return Complex(ampli, -phase); }
Complex Complex::operator - () const { return Complex(ampli, phase + pi); }

void Complex::operator *= (const Complex& other)
{
    ampli *= other.ampli;
    phase += other.phase;
}
void Complex::operator /= (const Complex& other)
{
    ampli /= other.ampli;
    phase -= other.phase;
}

// printing
std::ostream& ::vml::operator << (std::ostream& os, const Complex& v)
{
    os << v.ampli << " e^( " << v.phase/pi << " jπ)";
    return os;
}


// multiplication
Complex vml::operator * (const Complex& u, const Complex& v)
{
    return Complex(u.ampli * v.ampli, u.phase + v.phase);
}

// division
Complex vml::operator / (const Complex& u, const Complex& v)
{
    return Complex(u.ampli / v.ampli, u.phase - v.phase);
}


// cartesian arithmetic
Complex vml::cartesian(Float re, Float im)
{
    Float ampli{ std::sqrt(re*re + im*im) };
    Float phase{ atan2(im, re) };
    return Complex( ampli, phase);
}

Complex vml::operator + (const Complex& u, const Complex& v) {
    Float re { u.re() + v.re() };
    Float im { u.im() + v.im() };
    return cartesian(re, im);
}
Complex vml::operator - (const Complex& u, const Complex& v) {
    Float re { u.re() - v.re() };
    Float im { u.im() - v.im() };
    return cartesian(re, im);
}


// power funtions
Complex vml::pow(const Complex& u, const Complex& v) {
    const Float lnr { log(u.ampli) };
    Float pot { lnr * v.re() - u.phase * v.im() };
    return Complex( expf(pot), lnr * v.im() + u.phase * v.re() );
}
Complex vml::exp(const Complex& u) {
    return pow(Complex( expf(1.f) ), u);
}
Complex vml::sqrt(const Complex& u) {
    return pow(u, .5f);
}
