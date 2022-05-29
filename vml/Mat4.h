#pragma once

#include "Basics.h"
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
    static const int v_size {  4 };
    /// Anzahl der float-Einträge in der Matrix =  4*4
    static const int f_size { 16 };
    
    /// Interner Datenspeicher der Matrix: c-Style array
    float M[f_size];
    
    // Konstruktoren
    Mat4(const Vec4&, const Vec4&, const Vec4&, const Vec4&);
    Mat4(float);
    Mat4();
    
    // Zugang zu Einträgen
    float* data();
    float& operator[] (int i);
    const float& operator[] (int i) const;
    float& at(int, int);
    float at(int, int) const;
    Vec4 row(int i) const;
    Vec4 col(int i) const;
    
    // Methoden
    void transpose();
    float det();
    
    // printing
    friend std::ostream& operator << (std::ostream& os, const Mat4& m);
};

// ----------------------------------------------
// Namespace Methoden

Mat4 lookat(const Vec3&, const Vec3&, const Vec3&);
Mat4 ortho(float left, float right, float bottom, float top, float nearVal, float farVal);

} /* vml */
