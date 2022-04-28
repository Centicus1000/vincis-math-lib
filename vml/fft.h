#ifndef vml_fft_hpp
#define vml_fft_hpp

#include "basics.h"
#include "complex.h"

#include <vector>

namespace vml {

template <typename T> std::vector<T> _split_even(const std::vector<T>& v)
{
    const int n { static_cast<int>((v.size()+1) / 2) };
    if (n == 0) return { 0 }; // vector of one element
    std::vector<T> u(n);
    for(int i{0}; i < n; i++) u[i] = v[ 2*i ];
    return u;
}
template <typename T> std::vector<T> _split_odd(const std::vector<T>& v)
{
    const int n { static_cast<int>(v.size() / 2) };
    if (n == 0) return { 0 }; // vector of one element
    
    std::vector<T> u(n);
    for(int i{0}; i < n; i++) u[i] = v[ 2*i+1 ];
    
    return u;
}

std::vector<Complex> fft(const std::vector<float>&);
std::vector<Complex> ifft(const std::vector<Complex>&);

} /* vml */

#endif /* vml_fft_hpp */
