#include "vml/cashew.h"

using namespace vml;

// ----------------------------------------------
// Konsturktoren

/**
 * @brief Standard Konstruktor.
 *
 * Initialisiert explizit die vier Parameter der Cashewform.
 */
Cashew::Cashew(float _d, float _r1, float _r2, float _g) :
d(_d), r1(_r1), r2(_r2), g(_g)
{}

/**
 * @brief Default Konstruktor.
 *
 * Erstellt eine Dummy-Form: Die Radien sind auf 1, der Abstand auf 5 und die Krümmung gleich 0.
 * Das entspricht der Beinform des klassischen Tablebots.
 */
Cashew::Cashew() : Cashew(5.f, 1.f, 1.f, 0.f)
{}

// ----------------------------------------------
// Methoden

/**
 * @brief Form konstuieren.
 *
 * Mit dieser Funktion wird die eigentliche Kreisbogenform aus den vier Cashew-Parametern erstellt. Die Mathematik dahinter kann im Anhang meiner Bachelorarbeit nachgelesen werden (Rist V., 2022, Algorithmische Morphologien für autonome Roboter).
 */
ArcShape* Cashew::construct() const
{
    const int num_of_arcs{4};
    
    // varialbes for initializing arcs
    vec2  srt {};
    float ang {};
    std::array<float, num_of_arcs> crvs {};
    std::array<float, num_of_arcs> lngs {};
    
    // warings
    if (d < (r1+r2)) std::cerr << "Cashew Warning: d is too short." << std::endl;
    
    // -------------
    if ( abs(g) < .01f ) // small g snap to zero
    {
        /* STRAIGHT CHASHEW */
        const float alf{ acos((r1 - r2) / d) };
        const float bet{ pi - alf };
        const float dlt{ (vec2(d,0) + (r2-r1)*polar(alf)).norm() };

        // position and angle of first arc
        srt = r1 * polar(alf);
        ang = alf + .5f*pi;
        
        // remainging arc setting
        crvs = {1/r1, 0, 1/r2, 0};
        lngs = {2*bet*r1, dlt, 2*alf*r2, dlt};
    }
    // -------------
    else // g ≠ 0
    {
        /* CURVED CHASHEW */
        // get sign of gamma
        const float sg{ sign(g) };
        
        // apply pq-equation to find radii
        const float p{ r1 + r2 };
        const float q{ (r1*r1 + r2*r2 - 2.f * cos(g) * r1 * r2 - d*d) / (2.f - 2.f * cos(g)) };
        
        // find radii of connection circles
        const float R3{ -p / 2.f + sg * sqrt(p * p / 4.f - q) };
        const float R4{ R3+p };
        
        // center of circle R3
        const float x{ (d*d + (R3+r1)*(R3+r1) - (R3+r2)*(R3+r2)) / (2.f * d) };
        const float sy { -sign( mod2pi(g) - pi) };
        const float y { sy * sqrt((R3+r1)*(R3+r1) - x*x) };

        const float adj{ (sg < 0.f && 0.f < sy) ? 2.f*pi : 0.f };
        const float alf{ atan2(sg * y, sg * x) + adj };
        const float bet{ pi - g - alf };
        
        
        // position and angle of first arc
        srt = r1 * polar(alf);
        ang = alf + .5f*pi;
        
        // remainging arc setting
        crvs = {1/r1, 1/R4, 1/r2, -1/R3};
        lngs = {(g+2*bet)*r1, g*R4, (g+2*alf)*r2, g*R3};
    }
    // -------------
    
    // create an arc shape pointer
    ArcShape* as { new ArcShape(num_of_arcs) };
    for (int i{0}; i<num_of_arcs; i++)
    {
        // set arc data
        (*as)[i].srt = srt;
        (*as)[i].ang = ang;
        (*as)[i].crv = crvs[i];
        (*as)[i].lng = lngs[i];
        
        // update srt and ang
        srt = (*as)[i].end();
        ang += (*as)[i].central_angle();
    }
    
    return as;
}
