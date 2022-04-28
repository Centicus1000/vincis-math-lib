#ifndef vml_cashew_h
#define vml_cashew_h

#include "arcshape.h"
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
    float d;
    float r1;
    float r2;
    float g;
    
    // Konstruktoren
    Cashew();
    Cashew(float,float,float,float);
    
    // Methoden
    ArcShape* construct() const;
    
    // Debugging
    friend std::ostream& operator<< (std::ostream&, const Cashew&);
};

// Parsing
namespace parse {

bool stoCashew(Cashew&, const String&);
String to_string(const Cashew&);

} /* namespace parse */

} /* vml */
#endif /* vml_cashew_h */
