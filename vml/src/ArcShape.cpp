#include "vml/ArcShape.h"

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
void ArcShape::transform(Float rot, Vec2 off)
{
    for (Arc& a : (*this)) a.transform(rot, off);
}

/**
 * @brief Die tiefsten Punkte einer Form.
 *
 * Bestimmt welche Punkte der Form am tiefsten liegen, also die kleinste y-Koordinate haben.
 * Es wird eine Liste möglicher Kandidaten bestimmt und zurückgegeben.
 * Jeder Bogen der List darf einen Kandidaten liefern.
 */
std::vector<Vec2> ArcShape::lowestPoints() const
{
    // erstelle eine leere Punkte liste
    std::vector<Vec2> points{};
    
    for (const Arc& a : (*this))
    {
        // gekrümmte Bögen, die den Winkel -90° erreichen liefern einen Kandidaten.
        if (!a.isStraight() && a.reaches(-.5f*pi))
            points.push_back( a.atAngle(-.5f*pi) );
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
void ArcShape::discretize(std::vector<Vec2>& points, Float res) const
{
    // lass jeden Bogen die List befüllen
    for (const Arc& a : (*this))
        a.discretize(points, res);
}

/**
 * @brief Discretization. Turns an ArcShape into a Polygon with a requested number of points
 *
 * The Polygon is a discrete, sampled version of the ArcShape. The higher the numberOfPoints requested in the parameter input, the more accurate the representation is going to be put the longer the sampling algorithm is going to take.
 * The number of samples per Arc in the ArcShape is determined by its central angle. Straight Arcs with a central angle of 0, receive 0 samples, which makes sense because point along the straight line would be redundant in a polygon.
 * Stronger curved Arcs will receive more samples per arc length because they describe more detail. But shape with strongly curved arc will seem to have a worse resolution.
 * @param points reference to a vector of Vec2, this vector is going to receive the outline point of the polygon
 * @param numberOfPoints the number of outline points, the polygon is supposed to have
 */
void ArcShape::discretize(std::vector<Vec2>& points, int numberOfPoints) const
{
    /// Sum up the absolute value of the central angles of the arcs in the shape
    Float totalCentralAngle{ 0.f };
    for (const Arc& a : (*this)) totalCentralAngle += abs(a.centralAngle());
    /// the angularIncrement is the difference in angle between two adjacent samples
    const Float angularIncrement{ totalCentralAngle/numberOfPoints };
    
    /// set up inout vector parameter for the algorithm: remove any data, reserve enough space
    points.clear();
    points.resize(numberOfPoints);
    
    /// set up algorithm variables
    size_t arcIndex  { 0   }; ///< index of the arc that is currently sampled, counts to ArcShape.size()
    size_t pointIndex{ 0   }; ///< index polygon point to be sampled, counts to numberOfPoints
    Float angleOffset{ 0.f }; ///< tracks how much central angle has been used so far, is used and an offset for the next sample
    
    /// iterate through number of points of the polygon to ensure its size
    for(; pointIndex < numberOfPoints; pointIndex++)
    {
        /// get  pointer to the (const) current arc as a short cut
        const Arc* arc{ &at(arcIndex) };
        
        /// if the angleOffset exceeds the central_angle of the current Arc:
        /// 1. reduce angleOffset by this amount, which remains for the next arc
        /// 2. jump to the next arc by incrementing arcIndex and pointing to the new arc
        /// Straight Arc with central_angle = 0, are automatically skip, so the curvature (crv) is never 0
        while (abs(arc -> centralAngle()) <= angleOffset)
        {
            angleOffset -= abs(arc -> centralAngle());
            arc = &at( ++arcIndex );
        }
        
        /// calculate the length at which the current arc is sampled, the angleOffset is scale by the curvature to receive the arc length
        Float sampleLength{ angleOffset / abs(arc -> crv) };
        /// sample the arc at the determined length and save this point in the polygon
        points[ pointIndex ] = arc -> atLength(sampleLength);
        
        /// after sampling increase angleOffset by the angularIncrement for the next iteration
        angleOffset += angularIncrement;
    }
    /// every point in polygon is now set
}

/// TikZ string
/// @param optionals Optionaler Tikz style, default = "" (schwarzer Strich)
std::string ArcShape::TikZ(const char* optionals) const
{
    std::stringstream ss{};
    ss << "\\draw[" << optionals << "] " << (*this)[0].srt << " ";
    for (const Arc& a : (*this)) ss << a.TikZ();
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
