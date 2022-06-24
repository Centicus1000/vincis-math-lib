#pragma once

#include "Basics.h"

#include <string>
#include <sstream>
#include <vector>
#include <functional>

namespace vml
{
namespace parse
{

typedef std::string String;

bool contains(const String&, const String&);
bool isWhitespace(const String&);
void removeWhitespace(String&);
bool separate(const String&, String&, String&, const String&);

bool stoi(int&, const String&);
bool stof(Float&, const String&);
bool stoul(unsigned long&, const String&);
bool stou(unsigned&, const String&);

bool stofv(std::vector<Float>&, const String&);
bool stoiv(std::vector<int>&, const String&);

/**
 * @brief Vector to String.
 *
 * Eine Template-Funktion, die Vector von beliebigem Type zu einem String convertiert. Dafür muss der Type über einen validen string_stream operator<< overload verfügen.
 * Funktioniert für int, Float und Vec2.
 * @param v std::vector dessen einträge von template-Typen sind
 * @param convect eine std::function die einen template-Typen/einen Eintrag im Vector zu einem String konvertiert.
 */
template<typename T>
String toString(const std::vector<T>& v)
{
    std::stringstream ss;
    ss << "[";
    for (int i{ 0 }; i < v.size(); i++)
        ss << v[i] << ((i==v.size()-1) ? "" : ", ");
    ss << "]";
    return ss.str();
}

/**
 * @brief String zu Vektor Konvertieren.
 *
 * Mit dieser Funktion wird ein Float Vector gelesen. Dieser sollte die form "[a, b, c,..., n]" verwenden.
 * Die Funktion gibt true oder false zurück, je nachdem ob der Vector erfolgreich erstellt wurde.
 * Über Convert kann die String-Konvertierung der einzelen Elemente Eingestellt werden.
 */
template<typename T>
bool stov(std::vector<T>& v,
           const String& s,
           const std::function< bool(T&, const String&)>& convert)
{
    v.clear();
    // find open brace
    auto start{ s.find_first_of("[") };
    if (start==String::npos) return false;
    
    // repeadetly find commas and parse string inbetween
    auto stop{ s.find_first_of(",") };
    while (stop!=String::npos)
    {
        // pushback Float value
        T temp;
        if (!convert(temp, s.substr(start+1, stop))) return false;
        v.push_back(temp);
        // find next comma
        start = stop;
        stop = s.find_first_of(",", start+1);
    }
    
    // find closing brace
    stop = s.find_first_of("]");
    if (stop==String::npos) return false;
    // empty vector is possible
    if (s[start]=='[') return true;
    // try to parse Vec2 from string and push back
    T temp;
    if (!convert(temp, s.substr(start+1, stop))) return false;
    v.push_back(temp);
    v.shrink_to_fit();
    return true;
}


} /* namespace parse */
} /* namespace vml */
