#pragma once

#include "Basics.h"
#include "parse.h"

namespace vml {

/**
 * @brief Intervall.
 *
 * Die VML-Implementierung eines nach oben halboffenen Intervalls: [lo, hi)
 */
struct Interval
{
    // Attributes
    Float lo; ///< Untere Grenze des Intervalls
    Float hi; ///< Obere Grenze des Intervalls
    
    // Constructor
    Interval(Float=0.f,Float=1.f);
    
    // Methods
    Float size() const;
    bool contains(Float) const;
    
    friend std::ostream& operator << (std::ostream&, const Interval&);
};

// Namespace Methods
bool operator== (const Interval&, const Interval&);
bool operator!= (const Interval&, const Interval&);
Float lerp(Float, const Interval&, const Interval&);

// Parsing
namespace parse {

bool stoInterval(Interval&,const String&);
String toString(const Interval&);

} /* namespace parse */

} /* namespace vml */
