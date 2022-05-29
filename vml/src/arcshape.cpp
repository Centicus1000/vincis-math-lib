#include "vml/arcshape.h"

#include <sstream>
#include <numeric> // std::accumulate

using namespace vml;

/**
 * @brief Affine Transformation (Rotation und Verschiebung).
 *
 * Tranformiert die gesammte Kreisbogenform, indem [transform](@name Arc.transfrom) für jeden Bogen aufgeführt wird.
 *
 * @param rot Rotationswinkel
 * @param off Versatz (Offset)
 */
void ArcShape::transfrom(float rot, Vec2 off)
{
    for (Arc& a : (*this)) a.transfrom(rot, off);
}

/**
 * @brief Die tiefsten Punkte einer Form.
 *
 * Bestimmt welche Punkte der Form am tiefsten liegen, also die kleinste y-Koordinate haben.
 * Es wird eine Liste möglicher Kandidaten bestimmt und zurückgegeben.
 * Jeder Bogen der List darf einen Kandidaten liefern.
 */
std::vector<Vec2> ArcShape::lowest_points() const
{
    // erstelle eine leere Punkte liste
    std::vector<Vec2> points{};
    
    for (const Arc& a : (*this))
    {
        // gekrümmte Bögen, die den Winkel -90° erreichen liefern einen Kandidaten.
        if (!a.is_straight() && a.reaches(-.5f*pi))
            points.push_back( a.at_angle(-.5f*pi) );
    }
    
    return points;
}

/**
 * @brief Diskretisierung (zu einem Polygon).
 *
 * Erstellt eine Punkteliste (`std::vector<Vec2>`), welche durch das Aufrufen von [discretize](@name Arc.discretize) für jeden Bogen gefüll wird.
 * ACHTUNG: Die List wird als Pointer zurückgegeben, vergiss nicht die Daten nach dem Bnutzen wieder zu löschen.
 *
 * @param res Winkelauflüsung. Wird an [discretize](@name Arc.discretize()) weitergereicht.
 */
std::vector<Vec2>* ArcShape::discretize(float res) const
{
    // erstelle einen Pointer zu einer leeren Punktliste
    std::vector<Vec2>* points{ new std::vector<Vec2>() };
    // lass jeden Bogen die List befüllen
    for (const Arc& a : (*this))
        a.discretize(*points, res);
    // gib pointer zurück (ohne Pointer hätte point nur local scpoe, und müsste aufwendig kopiert werden)
    return points;
}
/// discretize with requested output size
/// calls discretize() but tries to figuer out the correct angular resolution so output vector matches requested size
/// @param requested_size size of output vector
std::vector<Vec2>* ArcShape::discretize(int requested_size) const
{
    // if requested size smaller than number of arcs, retun just staring positions
    if (requested_size < size())
        return discretize(2*pi);
    
    // find sum of central angles (=0 for straigh arcs)
    float tot_angle{0.f};
    for (const Arc& a : (*this))
        tot_angle += abs(a.central_angle());
    
    // find good resoluion
    float res{ tot_angle / (requested_size - size())};
    return discretize(res);
}

/// tikz string
/// @param optionals Optionaler Tikz style, default = "" (schwarzer Strich)
std::string ArcShape::tikz(const char* optionals) const
{
    std::stringstream ss{};
    ss << "\\draw[" << optionals << "] " << (*this)[0].srt << " ";
    for (const Arc& a : (*this)) ss << a.tikz();
    ss << ";";
    return ss.str();
}

/// debugging PRINT (friend function)
std::ostream& ::vml::operator<< (std::ostream& os, const ArcShape& S) {
    int i{0};
    for (const Arc& a : S)
        os << "\t\t" << ++i << ".: " << a;
    return os;
}
