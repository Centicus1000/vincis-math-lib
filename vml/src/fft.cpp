#include "vml/fft.h"

using namespace vml;

typedef std::vector<Complex> cvector;
typedef std::vector<float>   fvector;


/// split into even elements
/// static function to split vector into only even elements
/// @param invec input vector
//template <typename T>
//static std::vector<T> _split_even(const std::vector<T>& v)
//{
//    const int n { static_cast<int>((v.size()+1) / 2) };
//    if (n == 0) return { 0 }; // vector of one element
//    std::vector<T> u(n);
//    for(int i{0}; i < n; i++) u[i] = v[ 2*i ];
//    return u;
//}

/// split into odd elements
/// static function to split vector into only odd elements
/// @param invec input vector
//template <typename T>
//static std::vector<T> _split_odd(const std::vector<T>& v)
//{
//    const int n { static_cast<int>(v.size() / 2) };
//    if (n == 0) return { 0 }; // vector of one element
//
//    std::vector<T> u(n);
//    for(int i{0}; i < n; i++) u[i] = v[ 2*i+1 ];
//
//    return u;
//}


/// fast fourier transfor (FFT)
/// transforms a float vector into a complex spektrum
/// has O(n log n) time complexity thanks to recursion
/// length of input vector should be a power of 2
/// @param fvec input vector
cvector vml::fft(const fvector& fvec)
{
    int n{ static_cast<int>(fvec.size()) };
    
    // break recursion
    if (n==1) return { fvec[0] };
    
    Complex w{ 1.f, 2.f * pi / n };
    
    cvector ce{ fft(_split_even(fvec)) };
    cvector co{ fft(_split_odd (fvec)) };
    
    cvector cvec (n);
    for (int i{0}; i<n/2; i++)
    {
        cvec[i    ] = ce[i] + c_pow(w, i) * co[i];
        cvec[i+n/2] = ce[i] - c_pow(w, i) * co[i];
    }
    return cvec;
}

/// inverse FFT
/// reverts a complex spectrum to a real vector
/// conversion from complex to real is not done
/// @param cvec complex spectrum
cvector vml::ifft(const cvector& cvec)
{
    int n{ static_cast<int>(cvec.size()) };
    
    // break recursion
    if (n==1) return { cvec[0] };
    
    Complex w{ 1.f, -2.f * pi / n };
    
    cvector fe{ ifft(_split_even(cvec)) };
    cvector fo{ ifft(_split_odd (cvec)) };
    
    cvector fvec (n);
    for (int i{0}; i<n/2; i++)
    {
        fvec[i    ] = .5f*(fe[i] + c_pow(w, i) * fo[i]);
        fvec[i+n/2] = .5f*(fe[i] - c_pow(w, i) * fo[i]);
    }
    return fvec;
}
