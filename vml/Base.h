#pragma once

#include "basics.h"
#include "parse.h"

#include <vector>

namespace vml {

typedef unsigned Base;
typedef unsigned Digit;
typedef unsigned long Value;

/**
 * @brief Ziffern-Struktur.
 *
 * Die Ziffern-Struktur ist ein Vektor aus mehreren Ziffern, und erbt alle std::vector Funktionalitäten. Dadurch können die einzelnen Ziffern mit verschiedenen Basen betrachten werden
 */
class Digits : public std::vector<Digit>
{
public:
    // Inherit Constructors
    using std::vector<Digit>::vector;
};

// Operator Overloads
bool operator== (const Digits& a, const Digits& b);

/**
 * @brief Basen-Struktur.
 *
 * Die Base Struktur ist eine Vektor, bei dem jeder Eiintrag einer Basis entspricht.
 * Die mit der ihr kann eine Ziffernstruktur in das Dezimalsystem übersetzt/interpretiert werden.
 */
class Bases : public std::vector<Base>
{
public:
    // Inherit Constructors
    using std::vector<Base>::vector;
    
    // Methods
    Value possibilities() const;
    Digit stride(int) const;
    Value evaluate(const Digits&, bool use_overflow=true) const;
    Digits digitize(Value) const;
    bool step(Digits&,int,int,bool use_overflow=true) const;
};

// Parsing
namespace parse {

bool stoDigits(Digits&, const String&);
bool stoBases(Bases&, const String&);

String to_string(const Digits&);
// no need for to_string(const Bases&) as it Bases can use the to_string(const std::vector<Base>&) template in parse.h

} /* namespace parse */

} /* namespace vml */
