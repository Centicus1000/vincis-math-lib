#pragma once

#include <iostream> // printing
#include <cmath> // to use math every where

namespace vml {

/**
 * @brief The basic  floating point type for VML.
 *
 * The Float type is set to `double` because, according to [LearnCpp](https://www.learncpp.com/cpp-tutorial/Floating-point-numbers/ ), using double instead of Float is best practice, because Float often lead to an unwanted loss in precision.
 * If you need to save space, you can change the type to float here.
 */
using Float = /*double*/ float;

/**
 * @brief Kreiszahl.
 *
 * Die Kreiszahl PI als ein Float.
 */
const Float pi{ 3.141592653589793238 };

///@{
/**
 * @brief Konvertierung von Grad und Radiant.
 *
 * Diese Funktion konvertieren Winkelangaben von Grad zu Radiant und wieder zurück.
 */
inline Float radians(Float degree)
{
    return degree * pi / 180.f;
}
inline Float degree(Float radians)
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
 * `inline` damit in .h definiert werden kann.
 */
inline Float mod(Float x, Float y)
{
    return fmod(fmod(x, y) + y, y);
}

/**
 * @brief Modulo von 2PI (360).
 *
 * Modulo von 2pi. Wird häufig bei Umgang mit Winkeln und Kreisbögen verwendet.
 * `inline` damit in .h definiert werden kann.
 */
inline Float mod2pi(Float x)
{
    return mod(x, 2.f * pi);
}

/**
 * @brief Vorzeichen-Funktion.
 *
 * Die Vorzeichen-Funktion (Signum) ergibt -1 bei negativen und +1 beim positiven Eingängen.
 * Bei einem Input von 0, wird 0 zurückgegeben.
 * `inline` damit in .h definiert werden kann.
 */
inline Float sign(Float x)
{
    return (x==0.f) ? 0.f : x / abs(x);
}

/**
 * @brief Vorzeichen-Funktion.
 *
 * Die Vorzeichen-Funktion (Signum) ergibt -1 bei negativen und +1 beim positiven Eingängen.
 * Bei einem Input von 0, wird 0 zurückgegeben.
 * `inline` damit in .h definiert werden kann.
 */
inline int isign(int x)
{
    return (x==0) ? 0 : x / abs(x);
}

/**
 * @brief Lineare Interploation.
 *
 * Interpolition den Eingabe wert x vom Intervall [imin, imax] aus das Interval [omin, omax]
 * Achtung imax darf nicht gleich imin sein, sonst entsteht eine Polstelle.
 */
template<typename T>
inline T lerp(T x, T imin, T imax, T omin, T omax)
{
    assert((imax-imin) != 0 && "Illegal input range of width 0.");
    return (omax-omin) / (imax-imin) * (x-imin) + omin;
}

} /* vml namspace */
