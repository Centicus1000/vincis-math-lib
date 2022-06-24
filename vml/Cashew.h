#pragma once

#include "ArcShape.h"
#include "parse.h"

namespace vml {

/**
 * @brief Cashew-Form.
 *
 * Cashew ist eine bestimmt Art von Kreisbogenform (`ArcShape`), die sich über vier Paramter beschreiben lässt: Der Radius von zwei Kreisen (`r1` und `r2`), der Abstand dieser zwei Kreise (`d`) und die Krümmung der Verbindungsbögen, welche sich durch den Winkel gamma (`gamma`) einstellen lässt.
 * Die Datenstruktur Cashew ist allerdings noch keine fertige Kreisbogenform, sondern beinhalten nur die nötigen Paramter, um diese zu Konstruieren. Dadurch wird unnötiger Speicheraufwand vermieden.
 * Mit dem Befehl (`construct`) kann dann die Form erstellt werden.
 */
struct Cashew
{
    // Attribute
    Float d;
    Float r1;
    Float r2;
    Float g;
    
    // Konstruktoren
    Cashew();
    Cashew(Float,Float,Float,Float);
    
    // Methoden
    void construct(ArcShape&) const;
    
    // Debugging
    friend std::ostream& operator<< (std::ostream&, const Cashew&);
};

// ----------------------------------------------
// Parsing
namespace parse
{

bool stoCashew(Cashew&, const String&);
String toString(const Cashew&);

} /* namespace parse */

} /* vml */
