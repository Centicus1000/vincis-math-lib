#pragma once

#include "Basics.h"
#include "parse.h"
#include "Vec3.h"
#include "Vec4.h"

namespace vml {

/**
 * @brief 4x4 Matrix.
 *
 * Mat4 ist eine Implementierung einer 4x4 Matrix.
 * Die Matrix kann affine Transformationen (Rotation, Verschiebung, Skalierung, ect) im dreidimensionalen Raum beschrieben.
 * Sie eignet sich zum Verwenden mit OpenGL.
 * Intern ist sind die Einträge als eine c-Style array gespeichert.
 * @Todo: matmul, transpose, det
 */
struct Mat4
{
    /// Anzahl der Vec4-Vektor pro Matrix, bzw. Anzahl der Reihen oder Spalten
    static const int vSize {  4 };
    /// Anzahl der Float-Einträge in der Matrix =  4*4
    static const int fSize { 16 };
    
    // Konstruktoren
    Mat4(const Vec4&, const Vec4&, const Vec4&, const Vec4&);
    Mat4(Float);
    Mat4();
    
    // Zugang zu Einträgen
    Float* data();
    Float& operator[] (int i);
    const Float& operator[] (int i) const;
    Float& at(int, int);
    Float at(int, int) const;
    Vec4 row(int i) const;
    Vec4 col(int i) const;
    
    // Methoden
//    Mat4 transposed() const;
//    Float det() const;
    
private:
    /// Interner Datenspeicher der Matrix: c-Style array
    Float M[fSize];
};

// ----------------------------------------------
// Operatoren

std::ostream& operator << (std::ostream&, const Mat4&);

// ----------------------------------------------
// Namespace Methoden

Mat4 lookAt(const Vec3&, const Vec3&, const Vec3&);
Mat4 ortho(Float left, Float right, Float bottom, Float top, Float nearVal, Float farVal);

// ----------------------------------------------
// Parsing
namespace parse {

std::string toString(const Mat4&);

} /* namespace parse */

} /* vml */
