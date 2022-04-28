#include "vml/base.h"

#include <numeric> // accumulate, multiplies

using namespace vml;

// ----------------------------------------------
// Local Functions

/**
 * @brief Korrekter Int-Modulo.
 *
 * Implementiert den Integer Modulo mit korektem negativem Wrapparound.
 */
inline Digit _dmod(int x, Base y) { return static_cast<Digit>( (x % static_cast<int>(y) ) + y ) % y; }


// ----------------------------------------------
// Bases

/**
 * @brief Anzahl der Möglichkeiten.
 *
 * Berechnet die Anzahl der möglicheen Zahlen, die Mit dieser Basis dargestellt werden können.
 * Es handelt sich badei um das Produkt aus allen Basen.
 * @Todo: dont recalculate everytime.
 */
Value Bases::possibilities() const
{
    return std::accumulate(begin(), end(), 1, std::multiplies<Base>());
}

/**
 * @brief Wertigkeit der Ziffer i.
 *
 * Die Wertigkeit bzw. der Factor einer Ziffer berechnet sich aus dem Produkt aller vorhergehenden Basen.
 */
Digit Bases::stride(int i) const
{
    if (i == 0) return 1;
    return std::accumulate(begin(), std::next(begin(), i), 1, std::multiplies<Base>());
}

/**
 * @brief Interpretiere Ziffer in bestimmter Basis.
 *
 * Berechnet den Wert einer Digits-Struktur als Element des Basenraumes. Das Ergebnis wird dabei ins Dezimal system umberechnet.
 * @param digits Referenz zu einer Ziffern-Struktur mit der selber Anzahl an Dimensionen
 * @param overflow Overflow-Flag, Wenn true wird der Overflow mit berechnet, andernfalls werden zu große Ziffern mit einem Wraparround wieder in den erlaubten Bereich gemappt.
 */
Value Bases::evaluate(const Digits& digits, bool use_overflow) const
{
    // check if dimensions match
    if (digits.size() != size())
    {
        std::cerr << "Bases Error: dimension dont match." << std::endl;
        return 0;
    }
    // initialize vars for algorithms
    Digit factor{ 1 }, overflow{ 0 };
    Value value{ 0 };
    // iterate through bases and digits and accumulate value
    for (int i{0}; i < digits.size(); i++)
    {
        // find acutal digits value: add overflow from last round and add modulo
        Digit d { (digits[i]+overflow) % (*this)[i] };
        // add digit multiplies by its weight to the value
        value += factor * d;
        // calc next overflow, if flag deactivated -> overflow is alway 0
        if (use_overflow) overflow = (digits[i]+overflow) / (*this)[i];
        // calc next factor
        factor *= (*this)[i];
    }
    // return value and last overflow
    return value + factor * overflow;
}


Digits Bases::digitize(Value v) const
{
    Digits D;
    for (Base b : (*this))
    {
        // modulo with base to get digit
        Digit d{ static_cast<Digit>(v % b) };
        D.push_back(d);
        // divide by base to receive remider, which is the value of next iteration
        v /= b;
    }
    return D;
}

/**
 * @brief Ziffern anpassen mit Rücksicht auf die Basis.
 *
 * Passt die Ziffer der Dimension i um den Betrag amount an. Dabei wird geprüft, dass die Ziffer innerhalb der Basis bleibt.
 * Über- oder unterschreitet sie den Gültigen bereich wird gemodulot. Aus negative amounts sind erlaubt.
 * Der use_overflow-Flag entscheiden ob bei einem Over- oder Underflow die anderen Digits rekursiv angepasst werden.
 */
bool Bases::step(Digits& digits, int i, int amount, bool use_overflow) const
{
    // zero amount -> no action needed, breaks some recursion
    if(amount == 0) return true;
    // break recursion, indicate overflow by returning false
    if (i>=digits.size()) return false;
    // use int, because negative is possible
    int d{ static_cast<int>(digits[i]) + amount };
    // modulate with correct base
    digits[i] = _dmod(d, (*this)[i]);
    // check if step moved outside of base bounds (true if div != 0)
    int div{ (d-static_cast<int>(digits[i])) / static_cast<int>((*this)[i]) };
    if (div==0) return true;
    // if overflow is wanted start recursion and update next digit
    else if (use_overflow) return step(digits, i + 1, div);
    // else: no overflow, so the digit gets a wrapparound to stay in bounds
    // return false to indicated the step went outside base bounds
    return false;
}

// ----------------------------------------------
// Operator Overloads

/**
 * @brief Vergleiche zwei Ziffern-Strukturen.
 *
 * Um zu entscheiden, ob zwei Ziffern-Strukturen gleich sind, müssen all ihre Eintrage übereinstimmen.
 */
bool ::vml::operator== (const Digits& a, const Digits& b)
{
    if (a.size() != b.size()) return false;
    Value v{ 0 };
    for (Digits::size_type i{ 0 }; i < a.size(); i++)
    {
        v += a[i] - b[i];
    }
    return v == 0;
}

// ----------------------------------------------
// Parsing

/**
 * @brief Konvertiert einen String zu einer Ziffern-Struktur
 *
 * der String hat das Format: "d1:d2:d3:...:d4". Die einzelnen Ziffern sind mit ':' getrennt.
 */
bool vml::parse::stoDigits(Digits& digits, const String& s)
{
    // delete old data
    digits.clear();
    // create string buffers
    String left, right{ s };
    // split right into left and right at first ':'
    while (separate(right, left, right, ":"))
    {
        // try to convert left to valid digit and push to vector
        Digit d;
        if (!stou(d, left)) return false;
        digits.push_back(d);
    }
    // no more ':', so evaluate the last digit
    Digit d;
    if (!stou(d, right)) return false;
    digits.push_back(d);
    // no conversion error -> parsing successful
    digits.shrink_to_fit();
    return true;
}

/**
 * @brief Konvertiert String zu Basen-Struktur.
 *
 * Instatiert eine Version der stov-Funktion aus vml/parse.h und verwendet die stou zur Konvertierung der einzelnen Elemente.
 */
bool vml::parse::stoBases(Bases& bases, const String& s)
{
    std::function<bool(Base&,const String&)> convert{ stou };
    return stov(bases, s, convert);
}

#include <sstream>
/**
 * @brief Digits-Vektor als ein String.
 *
 * Konvertiert den Digits-Vektor in einen String. Dafür werden die einzelnen Ziffern der Reihe nach in einen STring convertiert und durch eine ':' getrennt. Format: 'd1:d2:...:dn'
 */
std::string vml::parse::to_string(const Digits& d)
{
    std::stringstream ss;
    for (int i{0}; i<d.size(); i++)
        ss << d[i] << ( (i<d.size()-1) ? ":" : "");
    return ss.str();
}
