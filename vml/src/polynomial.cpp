#include "vml/polynomial.h"
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
int Polynomial::degree() const { return coeffs.size() - 1; }

/// query coefficients
/// indicies bigger than N return 0., no error is thrown
float Polynomial::operator[] (int index) const
{
    if (index > degree()) return 0.f;
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
void Polynomial::add_padding(int new_degree)
{
    if (new_degree <= degree()) return;
    coeffs.resize(new_degree+1, 0.f);
}

void Polynomial::remove_padding()
{
    int i {degree()};
    while (abs(coeffs[i]) < 1e-3f) i--;
    coeffs.resize(i+1);
}

/// printing and debugging
std::ostream& ::vml::operator << (std::ostream& os, const Polynomial& p) {
    int i{ -1 }; // index tracker
    int n{ p.degree() };
    if (n==0)
    {
        os << p.coeffs[0] << " (const)";
        return os;
    }
    for (float c : p.coeffs) {
        i++;
//        if      (c == 0.f)  continue;
        if      (i == 0)    os << c;
        else if (i == 1)    os << c << "x";
        else                os << c << "x^" << i;
        if      (i < n)     os << " + ";
    }
    return os;
}

/// polynomial multiplication
/// multiplies two polynomila s using the fft and inverse fft like discribed here https://www.youtube.com/watch?v=h7apO7q16V0
Polynomial vml::operator * (const Polynomial& P1, const Polynomial& P2)
{
    // find degrees smallest degree that is power of two
    int n { (P1.degree()+1) * (P2.degree()+1) }; // who has more coeffs
    int N { static_cast<int>(pow(2, ceil(log2(n)))) }; // ceil to power of 2
    
    // initialize spectrum with 1 + j0
    std::vector<Complex> spectrum (N, Complex(1.f, 0.f));
    
    for (const Polynomial& P : {P1, P2})
    {
        // copy polynomial
        Polynomial p {P};
        // add padding to match N
        p.add_padding( N-1 );
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
    p.remove_padding();
    
    return p;
}
