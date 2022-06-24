#include "vml/parse.h"

#include <algorithm>

using namespace vml::parse;

/**
 * @brief Enthält der String einen Character.
 *
 * true, wenn c in s zu finden ist.
 */
bool ::vml::parse::contains(const String& s, const String& c)
{
    return s.find_first_of(c) != String::npos;
}

/**
 * @brief Ist String Whitespace?
 *
 * Wenn ein Character im String nicht Whitespace ist, wird false zurückgegeben.
 */
bool ::vml::parse::isWhitespace(const String& s)
{
    return std::find_if(s.begin(), s.end(), [](unsigned char c){ return !std::isspace(c); }) == s.end();
}


/**
 * @brief Entferne Whitespace von String.
 *
 * Entfernt alle Whitespace charaters von der übergebenen String Referenz.
 * Vor C++20 muss die umständliche Methode mit remove_if und erase verwendet werden.
 * @param s Sting als Refernz, dessen Whitspace entfert werden soll.
 */
void ::vml::parse::removeWhitespace(String& s)
{
//    s.erase_if(s.begin(), s.end(), std::isspace); <- work olny for c++20
    
    // remove whitespace from string
    // remove_if only rearanges the string
    auto new_end{ std::remove_if(s.begin(), s.end(), [](unsigned char c){ return std::isspace(c); }) };
    // use erase to actually shrink the srings size
    s.erase(new_end, s.end());
}

/**
 * @brief String Trennen.
 *
 * Trennt einen String in eine linke und Recht Hälfte. Dabei wird zur trennung ein speziellen Delimiter-String verwendet. Der Delimiter default ist "=", für eine Key-Value zerlegung.
 * Die Funktion gibt true oder false zurück, je nachdem ob die zerlegung erfolgreich war.
 * @param line zu zerlegende String
 * @param left Referenz zur Linken Seite, wird von der Funktion verändert
 * @param right Refernz zur rechten Seite, wird von der Funktion verändert
 * @param delimiter Trennungszeichen, Default ist "="
 */
bool ::vml::parse::separate(const String& line, String& left, String& right, const String& delimiter)
{
    // fing indey of seperator in line
    const auto i{ line.find(delimiter) };
    // return flase if none was foung
    if (i==String::npos) return false;
    // split line into left and right hand side
    left = line.substr( 0, i);
    right= line.substr(i + delimiter.size(),
                       line.size());
    // remove whitespaces
    removeWhitespace(left);
    removeWhitespace(right);
    return true;
}


#include <limits> // std::numeric_limits
///@{
/**
 * @brief String Konvertierung Int, Float und Unsigned.
 *
 * Wrapped die std-Konvertierungen zu einer eigenen Syntax, um keine Exceptions zu vermeiden.
 */
bool ::vml::parse::stoi(int& i, const String& s)
{
    try         { i = std::stoi(s);}
    catch (...) { return false;}
    return true;
}
bool ::vml::parse::stof(Float& f, const String& s)
{
    try         { f = std::stof(s);}
    catch (...) { return false;}
    return true;
}
bool ::vml::parse::stoul(unsigned long& ul, const String& s)
{
    try         { ul = std::stoul(s);}
    catch (...) { return false;}
    return true;
}
bool ::vml::parse::stou(unsigned& u, const String& s)
{
    // no std version of stou exsits so use stol: https://stackoverflow.com/a/8715855/5416171
    unsigned long ul;
    if (!stoul(ul, s)) return false;
    // check limits before casting
    if (ul > std::numeric_limits<unsigned>::max()) return false;
    // if limits save, downcast to unsigned int
    u = static_cast<unsigned>(ul);
    return true;
}
///@}


///@{
/**
 * @brief String zu Vektor Konvertieren.
 *
 * Einige Instanzierungen der stov Funktion
 */
bool ::vml::parse::stofv(std::vector<Float>& fv, const String& s)
{
    std::function< bool(Float&, const String&)> convert { stof };
    return stov(fv, s, convert);
}
bool ::vml::parse::stoiv(std::vector<int>& iv, const String& s)
{
    std::function< bool(int&, const String&)> convert { stoi };
    return stov(iv, s, convert);
}
///@}

