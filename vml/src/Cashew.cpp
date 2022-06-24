#include "vml/Cashew.h"

using namespace vml;

// ----------------------------------------------
// Konsturktoren

/**
 * @brief Standard Konstruktor.
 *
 * Initialisiert explizit die vier Parameter der Cashewform.
 */
Cashew::Cashew(Float _d, Float _r1, Float _r2, Float _g) :
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
void Cashew::construct(ArcShape& shape) const
{
    const int num_of_arcs{4};
    
    // varialbes for initializing arcs
    Vec2  srt {};
    Float ang {};
    std::array<Float, num_of_arcs> crvs {};
    std::array<Float, num_of_arcs> lngs {};
    
    // warings
    if (d < (r1+r2)) std::cerr << "Cashew Warning: d is too short." << std::endl;
    
    // -------------
    if ( abs(g) < .01f ) // small g snap to zero
    {
        /* STRAIGHT CHASHEW */
        const Float alf{ acos((r1 - r2) / d) };
        const Float bet{ pi - alf };
        const Float dlt{ (Vec2(d,0) + (r2-r1)*polar(alf)).norm() };

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
        const Float sg{ sign(g) };
        
        // apply pq-equation to find radii
        const Float p{ r1 + r2 };
        const Float q{ (r1*r1 + r2*r2 - 2.f * cos(g) * r1 * r2 - d*d) / (2.f - 2.f * cos(g)) };
        
        // find radii of connection circles
        const Float R3{ -p / 2.f + sg * sqrt(p * p / 4.f - q) };
        const Float R4{ R3+p };
        
        // center of circle R3
        const Float x{ (d*d + (R3+r1)*(R3+r1) - (R3+r2)*(R3+r2)) / (2.f * d) };
        const Float sy { -sign( mod2pi(g) - pi) };
        const Float y { sy * sqrt((R3+r1)*(R3+r1) - x*x) };

        const Float adj{ (sg < 0.f && 0.f < sy) ? 2.f*pi : 0.f };
        const Float alf{ atan2(sg * y, sg * x) + adj };
        const Float bet{ pi - g - alf };
        
        
        // position and angle of first arc
        srt = r1 * polar(alf);
        ang = alf + .5f*pi;
        
        // remainging arc setting
        crvs = {1/r1, 1/R4, 1/r2, -1/R3};
        lngs = {(g+2*bet)*r1, g*R4, (g+2*alf)*r2, g*R3};
    }
    // -------------
    
    // create an arc shape pointer
    shape.resize(num_of_arcs);
    for (int i{0}; i<num_of_arcs; i++)
    {
        // set arc data
        shape[i].srt = srt;
        shape[i].ang = ang;
        shape[i].crv = crvs[i];
        shape[i].lng = lngs[i];
        
        // update srt and ang
        srt = shape[i].end();
        ang += shape[i].centralAngle();
    }
}

// ----------------------------------------------
// Parsing

/**
 * @brief Konvertiere String zu Chasew.
 *
 * Ließt den String als einen Float Vector.
 * Schriebt dann die Einträge des Vektors der Reihe nach zu den Parametern: d, r1, r2, g.
 * Falls die Convertierung nicht klappt oder die Float-Vector nicht die richtige Größe (4) hat, wird false zurrückgegeben.
 * @param c Referenz zu einer Cashew Struktur, deren Parameter überschrieben werden
 * @param s der String, der geparst werden soll
 */
bool vml::parse::stoCashew(Cashew& c, const String& s)
{
    // extract parameters as Float vector
    std::vector<Float> v;
    if (!stofv(v, s)) return false;
    if (v.size() != 4) return false;
    // save parameters to cashew struct
    c.d = v[0]; c.r1 = v[1]; c.r2 = v[2]; c.g = v[3];
    return true;
}

/**
 * @brief Konvertiere Chashew zu einem String.
 *
 * Schriebt die vier Parameter der Chasew-Struktur in einem Float-Vector.
 * Dieser wird dann an toString(std::vector) weitergereicht und zu einem string konvertiert.
 */
std::string vml::parse::toString(const Cashew& c)
{
    std::vector<Float> v{ c.d, c.r1, c.r2, c.g };
    return toString(v);
}
