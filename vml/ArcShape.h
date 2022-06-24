#pragma once

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
    void transform(Float, Vec2);
    std::vector<Vec2> lowestPoints() const;
    void discretize(std::vector<Vec2>& points, Float res=.3) const;
    void discretize(std::vector<Vec2>& points, int numberOfPoints) const;
    std::string TikZ(const char* optionals = "") const;
    
    // Debugging
    friend std::ostream& operator<< (std::ostream&, const ArcShape&);
};

} /* vml */
