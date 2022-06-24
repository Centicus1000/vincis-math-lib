#pragma once

#include "Basics.h"
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
    Float ang;
    
    /**
     * @brief Krümmung (curvature)
     *
     * Der Betrag der Krümmung ist gleich dem Kehrwert des Radius.
     * Die Krümmung kann selber Vorzeichenbehaftet sein, wobei positiv eine Links- und negative eine Rechstkrümmung kodiert.
     * Eine Krümmung von 0 bedeutet aus dem Bogen wird eine ungekrümmte Strecke.
     */
    Float crv;
    
    /**
     * @brief Bogenlänge (arc length)
     *
     * Die Bogenlänge ist die Länge zwischen dem Startpunkt (`str`) und dem Endpunkt (`end`) entlang der Kreislinie.
     */
    Float lng;
    
    
    // ----------------------------------------------
    // Konstruktoren
    Arc(Float, Float, Float, Float, Float);
    Arc(const std::array<Float, 5>&);
    Arc();
    
    // Eigenschaften
    bool  isStraight() const;
    Float radius() const;
    Float centralAngle() const;
    Vec2  center() const;
    bool reaches(Float) const;
    
    // Punkte auf dem Bogen
    Vec2 atAngle(Float) const;
    Vec2 atLength(Float) const;
    Vec2 end() const;

    // Methoden
    void transform(Float, Vec2);
    void discretize(std::vector<Vec2>& output, Float res = .3) const;
    std::string TikZ() const;
    
    // Debugging
    friend std::ostream& operator<< (std::ostream&, const Arc&);
};

} /* vml */
