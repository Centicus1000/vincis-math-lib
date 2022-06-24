#include "vml/Arc.h"

#include <sstream>

using namespace vml;

// ----------------------------------------------
// Konstruktoren

/**
 * @brief Standard Konstruktor.
 *
 * Initialisiert die fünf Parameter des Kreisbogenes explizit
 *
 * @param _srx x-Koordinate von `srt`
 * @param _sry y-Koordinate von `srt`
 * @param _ang Starwinkel
 * @param _crv Krümmung
 * @param _lng Bogenlänge
 */
Arc::Arc
(
    Float _srx,
    Float _sry,
    Float _ang,
    Float _crv,
    Float _lng
) :
    srt{ _srx, _sry },
    ang{ _ang },
    crv{ _crv },
    lng{ _lng }
{}

/**
 * @brief Array Konstruktor.
 *
 * Ruft den Standard Konstruktor auf und übergibt die ersten 5 Einträge von fdata als Parameter.
 *
 * @param fdata die Parameter des Kreigens, gespeichert als std::array
 */
Arc::Arc(const std::array<Float, 5>& fdata) :
Arc(fdata[0], fdata[1], fdata[2], fdata[3], fdata[4])
{}

/// Default Konstruktor
/**
 * @brief Default Konstruktor.
 *
 * Ruft den Standart Konstruktor mit Default-Parameter Werten.
 */
Arc::Arc() :
Arc{ 0.f, 0.f, 0.f, 0.f, 1.f }
{}



// ----------------------------------------------
// Eigenschaften

/**
 * @brief Ist der Bogen gerade bzw. eine Strecke?
 *
 * Wenn die Krümmung gleich 0 ist, handelt es sich bei diesem Bogen eigentlich um eine gerade, ungekrümmte Strecke.
 * Start- und End- punkt sind als auf kürzestem Weg verbunden.
 */
bool Arc::isStraight() const
{
    return crv == 0.f;
}

/**
 * @brief Radius des korrespondierenden Kreises.
 *
 * Der Radius entspricht dem positiven Kehrwert der Krümmung.
 * Negative Krümmungen erzeugen dieselben Radien wie ihre positiven Partner.
 * ACHTUNG: bei geraden Bögen existiert kein Radius und hier wird durch 0 geteilt.
 */
Float Arc::radius() const
{
    return 1.f / abs(crv);
}

/**
 * @brief Mittelpunktswinkel.
 *
 * Der Mittelpunktswinkel ist der Winkel, der ausgehend vom Mittelpunkt des korrespondierenden Kreises zwischen Start- und Endposition aufgespannt wird.
 * Der Mittelpunktswinkel kann vorzeichenbehaftet sein und wird in Radiant angegeben.
 * Gerade Strecke oder Bögen mit eine Länge von 0, erzeugen einen Mittelpunktswinkel von 0 rad.
 * Er berechnet sich aus dem Produkt von Kümmung und Bogenlänge.
 */
Float Arc::centralAngle() const
{
    return crv * lng;
}

/**
 * @brief Mittelpunkt des korrespondierenden Kreises.
 *
 * Der Mittelpunkt befindet sich rechtwinklig zum Startwinkel um den Radius entfernt von der Startposition.
 * ACHTUNG: bei geraden Bögen existiert kein MIttelpunkt und hier wird durch 0 geteilt.
 */
Vec2 Arc::center() const
{
    return srt + polar(ang + pi/2.f) / crv;
}

/**
 * @brief Erreicht der Bogen einen absoluten Winkel?
 *
 * In manchen Fällen ist es nützlich, zu wissen ob der Bogen einen absoluten Winkel `psi` auf dem korrespondierenden Kreis erreicht.
 * Das bedeutet konkret:
 *  Geht man ausgehend vom Mittelpunkt um den Radius in Richtung von `psi`, liegt dieser Punkt auf dem Bogen oder nicht?
 *
 *  @param psi ein absoluter Winkel in Radiant
 */
bool Arc::reaches(Float psi) const
{
    return abs(centralAngle()) >= mod2pi( sign(crv) * (psi - ang) + .5f*pi );
}


// ----------------------------------------------
// Punkte auf dem Bogen

/**
 * @brief Punkt @ Länge.
 *
 * Gibt den Punkt auf dem Bogen zurück, welcher sind um eine Länge `l` entlang des Bogens vom Startpunkt entfernt liegt.
 * Für Strecken liegt dieser Punkt auf der Tangenten.
 * Sowohl positve als auf negative Eingänge sind erlaubt. Allerdings liegt für 0 < `l`< `lng`, der Punkt nicht mehr auf dem Bogen.
 *
 * @param l eine (Bogen-)Länge
 */
Vec2 Arc::atLength(Float l) const
{
    // für gerade Bögen (Strecken, crv==0)
    if (isStraight()) return srt + l * vml::polar(ang);
    // für gekrümmte Bögen (crv != 0)
    return center() + vml::polar(ang - pi/2.f + l * crv)/crv;
}

/**
 * @brief Endpunkt des Bogens.
 *
 * Anders als `srt` muss `end` nicht mit gespeichert werden, da er sich aus den anderen Attributen ableiten lässt.
 * Der Endpunkt des Bogens lässt sich bestimmen indem man die Bogenlänge `lng` als Parameter an `at_length` übergibt.
 */
Vec2 Arc::end() const
{
    return atLength(lng);
}

/**
 * @brief Punkt @ Winkel.
 *
 * Gibt den Punkt auf dem korrespondierenden Kreis zurück, welcher beim absolkuten Winkel `psi` liegt.
 * Dieser liegt allerdings nur dann auch auf dem Bogen, wenn [`reaches(psi)`](@ref reaches) sich als `true` erweist.
 * ACHTUNG: bei geraden Bögen existiert kein korrespondierender Kreis und hier wird durch 0 geteilt.
 *
 * @param psi absoluter Winkel in Radiant
 */
Vec2 Arc::atAngle(Float psi) const
{
    return center() + vml::polar(psi) / abs(crv);
}



// ----------------------------------------------
// Methoden

/**
 * @brief Affine Transformation (Rotieren und Verschieben)
 *
 * Erst wird der Bogen um den Winkel `rot` rotiert und anschlißend um den Vektor `off` (offset) verschoben.
 * Dabei werden nur die Startposition und der Startwinkel angepasst, die Krümmung und Bogenlänge bleibt unverändert.
 *
 * @param rot Rotierungwinkel in Radiant
 * @param off Versatz (Offset), default = (0,0)
 */
void Arc::transform(Float rot, Vec2 off = Vec2(0.f))
{
    ang += rot;
    srt = srt.rotated(rot) + off;
}

/**
 * @brief Diskretisierung (zu einem Polygon)
 *
 * Wandelt den Bogen in ein Polygon (`std::vector` aus `Vec2`) in dem an diskreten Längen zwischen 0 und `lng` abgetastet wird.
 * Die Abtastung erfolgt über die Funktion [at_length](@ref at_length).
 * Die Auflösung wird in Radiant als Winkel angegeben, damit starktgekrümmte Bögen öfter und wenig gekrümmte Bögen seltener abgetastet werden und die Polygone skalierungs unabhängig sind.
 * Dadurch ist die Anzahl der Abtastungen gleich [central_angle](@ref central_angle)/´res´. Die Abtastung ist inklusive des Startpunktes aber exklusive des Endpunktes.
 * Gerade Segemente Segmente liefern dadurch nur ihren Startpunkt.
 *
 * @param [out] output Referrenz zu einem Vec2-vector, in welchem die Abtastungen gespeichert werden sollen.
 * @param res Auflösung in Radiant, Abstand zwischen zwei diskreten Abtastungen. Default = 0.3.
 */
void Arc::discretize(std::vector<Vec2> &output, Float res) const
{
    // speicher die Startposition in jedem Fall
    output.push_back(srt);

    // für gerade Bögen wird abgebrochen
    if (isStraight()) return;
    
    // berechne die Anzahl der Abtastungen
    int N{ static_cast<int>(abs(centralAngle())/res) };
    // berechne den Abstand zwischen zwei Abtastungen
    Float increment{ lng / N };
    
    // taste den Bogen mit at_length ab
    for (int i{1}; i<N; i++)
    {
        Vec2 p{ atLength(i * increment) };
        output.push_back(p);
    }
}

/**
 * @brief TikZ String
 *
 * Erstellt einen Tikz-Befehl, um den Bogen in Latex zu plotten.
 * Für gekrümmte Bögen wird der ´arc´-Befehl verwendet, für Strecken reicht die lineare Verbindung durch ´--´.
 * ACHTUNG: Der Return-Wert dieser Funktion fukntioniert alleine nicht. Verwende lieber die [TikZ-Implementierung von ArcShape](@ref ArcShape.tikz).
 */
std::string Arc::TikZ() const
{
    std::stringstream ss;
    if (isStraight())
    {
        Vec2 e{ end() };
        ss << "-- (" << e.x << "," << e.y << ") ";
    }
    else
    {
        Float sa{ degree(ang - sign(crv) * .5f*pi) };
        Float ea{ sa + degree(centralAngle()) };
        ss << "arc(" << sa << ":" << ea << ":" << radius() << ") ";
    }
    return ss.str();
}


// ----------------------------------------------
// Debugging

/**
 * @brief Print Overload
 *
 * Printet die fünf Parameter des Kreisbogens.
 *
 * @param os Outstream (cout)
 * @param a Kreisbogen
 */
std::ostream& ::vml::operator << (std::ostream& os, const Arc& a)
{
    os << "arc( srt:" << a.srt << ", ang:" << a.ang << ", crv:" << a.crv << ", lng:" << a.lng << ")";
    return os;
}
