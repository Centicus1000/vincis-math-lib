#ifndef vml_shape_h
#define vml_shape_h

#include "Arc.h"

namespace vml {

/**
 * @brief Kreisbogenform, Aneinandereihung von mehreren Kreisbögen
 *
 * Eine Kreisbogenform ist eine geschlossen Form aus tangential ineinander übergehenden Kreisbögen (`Arc`s).
 * Der Kontainer dafür ist ein `std::vector`, von welcher alle Eigenschaften geerbt werden
 */
class ArcShape : public std::vector< Arc >
{
public:
    // erbe alle Funktionalitäten von std::vector
    using std::vector<Arc>::vector;

    // Methoden
    void transfrom(float, Vec2);
    std::vector<Vec2> lowest_points() const;
    std::vector<Vec2>* discretize(float res=.3) const;
    std::vector<Vec2>* discretize(int requested_size) const;
    std::string tikz(const char* optionals = "") const;
    
    // Debugging
    friend std::ostream& operator<< (std::ostream&, const ArcShape&);
};

} /* vml */
#endif /* vml_shape_h */
