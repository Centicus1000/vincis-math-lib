#ifndef vml_basics_h
#define vml_basics_h

#include <iostream> // printing
#include <cmath> // to use math every where
#include <array> // array sytle data handling

namespace vml {

/**
 * @brief Kreiszahl.
 *
 * Die Kreiszahl PI als ein float.
 */
const float pi{ 3.141592653589793238f };

///@{
/**
 * @brief Konvertierung von Grad und Radiant.
 *
 * Diese Funktion konvertieren Winkelangaben von Grad zu Radiant und wieder zurück.
 */
inline float radians(float degree)
{
    return degree * pi / 180.f;
}
inline float degree(float radians)
{
    return radians * 180.f / pi;
}
///@}

/**
 * @brief Korrekter Modulo.
 *
 * Die cmath Funktion `fmod` behält das Vorzeichen, vom Eingang bei.
 * In vielen Fällen ist das unerwünscht, z.B. bei Umgang mit Winkeln.
 * Hier wird diese Eigenschaft konpemsiert.
 */
float mod(float x, float y)
{
    return fmod(fmod(x, y) + y, y);
}

/**
 * @brief Modulo von 2PI (360).
 *
 * Modulo von 2pi. Wird häufig bei Umgang mit Winkeln und Kreisbögen verwendet.
 */
float mod2pi(float x)
{
    return mod(x, 2.f * pi);
}

/**
 * @brief Vorzeichen-Funktion.
 *
 * Die Vorzeichen-Funktion (Signum) ergibt -1 bei negativen und +1 beim positiven Eingängen.
 * Bei einem Input von 0, wird 0 zurückgegeben.
 */
float sign(float x)
{
    return (x==0.f) ? 0.f : x / abs(x);
}

} /* vml namspace */
#endif /* vml_basics_h */
