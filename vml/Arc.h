#pragma once

#include "basics.h"
#include "Vec2.h"

#include <array>
#include <vector>

namespace vml {

/**
 * @brief Kreisbogen, ein kontinuierlicher Abschnitt einer Kreislinie.
 *
 * [Kreisbögen](https://de.wikipedia.org/wiki/Kreisbogen) eignen sich, um Formen mit runden Konturen und nur wenigen Parametern zu definieren.
 * Sie sind die Verbindung zwischen zwei Punkten eines Kreises durch die Kreislinie.
 * Die Implementierung erfolgt über 5 Parameter: die x- und y-Koordinaten das Startpunktes, die Startrichtung, die Krümmung und die Bogenlänge.
 */
struct Arc
{
    
    /**
     * @brief Startposition (start position)
     *
     * Die Sartposition des Kreisbogens ist ein zweidimensionaler Vektor. Der korrespondierende Kreis geht immer durch diesen Punkt.
     */
    Vec2 srt;
    
    /**
     * @brief Startwinkel (start angle)
     *
     * Der Sartwinkel oder die Startrichtung (`ang`) gibt an mit welchem Winkel die Tangente des Bogens am Startpunkt anliegt.
     */
    float ang;
    
    /**
     * @brief Krümmung (curvature)
     *
     * Der Betrag der Krümmung ist gleich dem Kehrwert des Radius.
     * Die Krümmung kann selber Vorzeichenbehaftet sein, wobei positiv eine Links- und negative eine Rechstkrümmung kodiert.
     * Eine Krümmung von 0 bedeutet aus dem Bogen wird eine ungekrümmte Strecke.
     */
    float crv;
    
    /**
     * @brief Bogenlänge (arc length)
     *
     * Die Bogenlänge ist die Länge zwischen dem Startpunkt (`str`) und dem Endpunkt (`end`) entlang der Kreislinie.
     */
    float lng;
    
    
    // ----------------------------------------------
    // Konstruktoren
    Arc(float, float, float, float, float);
    Arc(const std::array<float, 5>&);
    Arc();
    
    // Eigenschaften
    bool  is_straight() const;
    float radius() const;
    float central_angle() const;
    Vec2  center() const;
    bool reaches(float) const;
    
    // Punkte auf dem Bogen
    Vec2 at_angle(float) const;
    Vec2 at_length(float) const;
    Vec2 end() const;

    // Methoden
    void transfrom(float, Vec2);
    void discretize(std::vector<Vec2>& output, float res = .3) const;
    std::string tikz() const;
    
    // Debugging
    friend std::ostream& operator<< (std::ostream&, const Arc&);
};

} /* vml */
