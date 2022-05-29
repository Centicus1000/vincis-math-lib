#pragma once

#include "basics.h"
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
    float lo; ///< Untere Grenze des Intervalls
    float hi; ///< Obere Grenze des Intervalls
    
    // Constructor
    Interval(float=0.f,float=1.f);
    
    // Methods
    float size() const;
    bool contains(float) const;
    
    friend std::ostream& operator << (std::ostream&, const Interval&);
};

// Namespace Methods
bool operator== (const Interval&, const Interval&);
bool operator!= (const Interval&, const Interval&);
float lerp(float, const Interval&, const Interval&);

// Parsing
namespace parse {

bool stoInterval(Interval&,const String&);
String to_string(const Interval&);

} /* namespace parse */

} /* namespace vml */
