#include "vml/interval.h"

using namespace vml;

// ----------------------------------------------
// Constructor

/**
 * @brief Standard Konstuktor.
 *
 * Initialisiert die Grenzen explizit über Parameter.
 * @param _lo Wert der Unteren Grenze (erster Parameter)
 * @param _hi Wert der Oberen Granze (zweiter Parameter)
 */
Interval::Interval(float _lo, float _hi) : lo(_lo), hi(_hi)
{}

// ----------------------------------------------
// Methods

/**
 * @brief Intervalllänge.
 *
 * Berechnet die Länge des Intervall.
 * Achtung wenn hi kleiner als lo, dann ist die Länge negativ.
 */
float Interval::size() const
{
    return hi - lo;
}

/**
 * @brief Ist innerhalb des Intervalls.
 *
 * Überprüft ob ein Eingangswert auf dem gegebenen Intervall liegt.
 * Hier wird die Halboffenheit Implementiert.
 * Bei float-Wert macht das allerdings nur wenig aus.
 */
bool Interval::contains(float x) const
{
    return (lo <= x) && (x < hi);
}

// ----------------------------------------------
// Namespace Methods

///@{
/**
 * @brief Intervall Vergleich.
 *
 * Überprürft zwei Intervalle auf Gleichheit.
 */
bool ::vml::operator == (const Interval& a, const Interval& b)
{
    float d{ ((a.lo - b.lo)*(a.lo - b.lo) + (a.hi - b.hi)*(a.hi - b.hi)) };
    return d < 1e-5f;
}
bool ::vml::operator != (const Interval& a, const Interval& b)
{
    float d{ ((a.lo - b.lo)*(a.lo - b.lo) + (a.hi - b.hi)*(a.hi - b.hi)) };
    return d > 1e-5f;
}
///@}

/**
 * @brief Intervall Interpolation.
 *
 * Wrapped die lerp-Function aus basic.h mit Intervallen.
 * @param x Eingangswert, der vom inval nach outval gemappt wird
 * @param inval Eingangsintervall
 * @param outval Ausgangsintervall
 */
float ::vml::lerp(float x, const Interval& inval, const Interval& outval)
{
    return lerp(x, inval.lo, inval.hi, outval.lo, outval.hi);
}

// ----------------------------------------------
// Parsing
#include <sstream>

/**
 * @brief Konvertiere String zu einen Intervall.
 *
 * Konvertiert einen String mit dem Format: "lo...hi" in eine Intervall-Struktur.
 * Dabei wird nicht die klassische Intervalnotation "[lo,hi]" verwendet, da sie syntaktisch nicht bzw. schwieriger von der Array-Notation zu unterscheiden ist.
 */
bool vml::parse::stoInterval(Interval& I, const String& s)
{
    // split s into left and right side at seperator '...'
    String left, right;
    if (!separate(s, left, right, "...")) return false;
    // convert left to lower bound and right to higher bound of interval
    if (!stof(I.lo, left)) return false;
    if (!stof(I.hi, right)) return false;
    return true;
}

/**
 * @brief Konvertiere Intervall zu einem String.
 *
 * Konvertiert die Intervall-Struktur zu einem String. Dabei wird die Notation "lo...hi" verwendet
 */
std::string vml::parse::to_string(const Interval& I)
{
    std::stringstream ss;
    ss << std::to_string(I.lo) << "..." << std::to_string(I.hi);
    return ss.str();
}


std::ostream& ::vml::operator << (std::ostream& os, const Interval& I)
{
    os << parse::to_string(I);
    return os;
}
