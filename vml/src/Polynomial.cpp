#include "vml/Polynomial.h"
#include "vml/fft.h" // for efficient polynomial multiplication

using namespace vml;


/// default constructor
/// creates a degree 0 Polynom with one coefficient of value 0.f
Polynomial::Polynomial() : coeffs({ 0.f }) {};

/// coefficient initializer
/// allows initialization through initializer list: Polynomial({ 1.f, 2.f, 3.f })
/// @param _coeffs vector of coefficients
Polynomial::Polynomial(std::vector<float> _coeffs) : coeffs(_coeffs)
{}


/// degree of polynomial
/// degree n = number of coeficient - 1
int Polynomial::degree() const
{
    return coeffs.size() - 1;
}

/// query coefficients
/// indicies bigger than N return 0., no error is thrown
const float& Polynomial::operator[] (int index) const
{
    static Float zero{ 0.f };
    if (index > degree()) return zero;
    return coeffs[ index ];
}
float& Polynomial::operator[] (int index)
{
    if (index > degree()) resize(index);
    return coeffs[ index ];
}


/// derivative
/// returns the derivative of the polynomial as a diffrent polymonial
Polynomial Polynomial::derivative() const
{
    const int newN { degree() };
    if (newN == 0) return Polynomial();
    std::vector<float> newcoeff( newN );
    
    for(int i{0}; i < newN; i++) {
        newcoeff[i] = (i+1)*coeffs[i+1];
    }
    
    return Polynomial(newcoeff);
}

/// zero padding
/// appends 0.f coefficients to match the new degree
/// @param new_degree new value of degree
void Polynomial::resize(int newDegree)
{
    coeffs.resize(newDegree+1, 0.f);
}

void Polynomial::shrinkToFit()
{
    int i{ degree() };
    while (abs(coeffs[i]) < 1e-3f) i--;
    coeffs.resize(i+1);
}

// ----------------------------------------------
// Parsing

/// printing and debugging
std::ostream& vml::operator << (std::ostream& os, const Polynomial& p)
{
    return os << parse::toString(p);
}

#include <sstream>
std::string vml::parse::toString(const Polynomial& p)
{
    std::stringstream ss;
    bool shouldSeparateNextTerm{ false };
    
    for
    (
        int i{ 0 }, n{p.degree()};
        i <= n;
        i++
    )
    {
        // skip terms with coefficients of value = 0
        if (p[i] == 0.f)  continue;
        
        // check if terms should be separated by a '+'
        if (shouldSeparateNextTerm) ss << " + ";
        
        // add terms, but conditionally omit 'x' or exponent
        if      (i == 0) ss << p[i];
        else if (i == 1) ss << p[i] << "x";
        else             ss << p[i] << "x^" << i;
        
        // raise flag, if a term was added
        shouldSeparateNextTerm = true;
    }
    
    // in case of polynomial with all zero coeffs
    if (!shouldSeparateNextTerm) ss << "0";
    
    return ss.str();
}


bool extractTermsExponent(unsigned& e, parse::String& s)
{
    using namespace parse;
    const auto pos{ s.find_first_of("^")};
    if (pos != String::npos)
    {
        return stou(e, s.substr(pos+1));
    }
    
    if (s.find_first_of("x") != String::npos)
    {
        e = 1;
        return true;
    }
    
    e = 0;
    Float fbuf;
    return stof(fbuf, s);
}

bool vml::parse::stoPolynomial(Polynomial& p, const String& s)
{
    // delete old coeffs
    p.resize(-1);
    
    String::size_type start{ 0 };
    String::size_type stop{ s.find_first_of("+") };
    
    while (true)
    {
        String term{ s.substr(start, stop-start) };
        
        unsigned exponent;
        if (!extractTermsExponent(exponent, term)) return false;
        
        // if exponent is not 0, find position of the 'x'
        String::size_type xpos
        {
            (exponent != 0) ? term.find_first_of("x") : String::npos
        };
        // try to extract the coeff as a float type
        Float coefficient;
        if (!stof(coefficient, term.substr(0,xpos))) return false;
        // add extracted coefficient to polynomial
        p[exponent] += coefficient;
        
        // determine start and stop of next term
        if (stop == String::npos) break;
        start = stop + 1;
        stop = s.find_first_of("+", start);
    }
    p.shrinkToFit();
    return true;
}

/// polynomial multiplication
/// multiplies two polynomila s using the fft and inverse fft like discribed here https://www.youtube.com/watch?v=h7apO7q16V0
Polynomial vml::operator * (const Polynomial& P1, const Polynomial& P2)
{
    // find degrees smallest degree that is power of two
    int n { (P1.degree()+1) * (P2.degree()+1) }; // who has more coeffs
    int N { static_cast<int>(std::pow(2, ceil(log2(n)))) }; // ceil to power of 2
    
    // initialize spectrum with 1 + j0
    std::vector<Complex> spectrum (N, Complex(1.f, 0.f));
    
    for (const Polynomial& P : {P1, P2})
    {
        // copy polynomial
        Polynomial p {P};
        // add padding to match N
        p.resize( N-1 );
        // convert coeffs into complex spectrum using fft
        std::vector<Complex> c { fft(p.coeffs) };
        // multiply to spectrums
        for (int i{0}; i<N; i++) spectrum[i] *= c[i];
    }
    
    // convert back to coefficients
    spectrum = ifft(spectrum);
    
    // initialize coeffs with 0.f
    std::vector<float> coeffs (N);
    // only take the real part
    for (int i{0}; i<N; i++) coeffs[i] = spectrum[i].re();
    
    // create polynomial
    Polynomial p(coeffs);
    // remove unnessecary padding
    p.shrinkToFit();
    
    return p;
}
