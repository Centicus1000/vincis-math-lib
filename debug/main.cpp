#include "vml/Polynomial.h"

int main() {
    using namespace vml;
    
    Polynomial p({1.f, 2.f, 3.f, 4.f});
    std::cout << p << std::endl;

    
    auto s{ parse::toString(p) };
    Polynomial q;
    if (parse::stoPolynomial(q, s)) std::cout << q << std::endl;
    else std::cout << "nope" << std::endl;
}

