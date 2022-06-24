#include "vml/Mat4.h"

using namespace vml;

// ----------------------------------------------
// Konstruktoren

/**
 * @brief Vektor Konstruktor.
 *
 * Initialisiert die Matrix über vier Zeilenvektoren, damit folgende Schreibweise möglich wird:
 *  `Mat4{
 *      Vec4(d, 0, 0, 0),
 *      Vec4(0, d, 0, 0),
 *      Vec4(0, 0, d, 0),
 *      Vec4(0, 0, 0, d) };
 *  `
 */
Mat4::Mat4(const Vec4& ex, const Vec4& ey, const Vec4& ez, const Vec4& ew) :
M{
    ex.x, ex.y, ex.z, ex.w,
    ey.x, ey.y, ey.z, ey.w,
    ez.x, ez.y, ez.z, ez.w,
    ew.x, ew.y, ew.z, ew.w,
}{}

/**
 * @brief Diagonal Konstruktor.
 *
 * Erzeugt vier Spaltenvektoren, sodass der Parameter `d` auf der Hauptdiagonalen zu finden ist und alle andern Werte auf 0 gesetzt werden.
 * Damit wird der Vektor Konstruktor aufgerufen.
 *
 * @param d der Wert auf der Hauptdiagonalen.
 */
Mat4::Mat4(Float d) :
Mat4(Vec4(d, 0, 0, 0),
     Vec4(0, d, 0, 0),
     Vec4(0, 0, d, 0),
     Vec4(0, 0, 0, d))
{}

/**
 * @brief Einheitsmatrix (Default Konstructor).
 *
 * Ruft den Diagonal Konstruktor mit dem Parameter 1 auf, wodruch eine Einheitsmatrix erschaffen wird.
 */
Mat4::Mat4() : Mat4(1.f)
{}

// ----------------------------------------------
// Zugang zu Einträgen

/**
 * @brief Datenpointer.
 *
 * Gibt den Pointer zum ersten Eintrag zurück.
 * Diese Funktion wird häufig in OpenGL verwendet, um Matrizen in Shader zu laden.
 */
Float* Mat4::data()
{
    return &M[0];
}

///@{
/**
 * @brief Indizierung.
 *
 * Übergibt den Index an den internen Datenspeicher `M`, wodurch alle 16 Einträge direkt zugänglich sind.
 */
Float& Mat4::operator[] (int i)
{
    return M[i];
}
const Float& Mat4::operator[] (int i) const
{
    return M[i];
}
///@}

///@{
/**
 * @brief Zeile- und Spaltenzugang.
 *
 * Berechnet den korrekten Index im internen Datenspeicher. Und gibt den wert an der Richtigen Stelle zurück.
 *
 * @param row Index der Zeile
 * @param col Index der Spalte
 */
Float& Mat4::at(int row, int col)
{
    return M[row * vSize + col];
}
Float Mat4::at(int row, int col) const
{
    return M[col * vSize + row];
}
///@}

/**
 * @brief Zeilen Zugang.
 *
 * Erstellt einen Vec4 auf den Einträgen in der Zeile und gibt diesen zurück. Die Referenz zu den Daten geht dabei verloren
 */
Vec4 Mat4::row(int i) const
{
    return Vec4(at(i,0), at(i,0), at(i,0), at(i,0));
}

/**
 * @brief Spalten Zugang.
 *
 * Erstellt einen Vec4 auf den Einträgen in der Spalten und gibt diesen zurück. Die Referenz zu den Daten geht dabei verloren
 */
Vec4 Mat4::col(int i) const
{
    return Vec4(at(0,i), at(1,i), at(2,i), at(3,i));
}

// ----------------------------------------------
// Methods

//Mat4 Mat4::transposed() const
//{
//    Vec4 ex{ Vec4(at(0, 0), at(1, 0), at(2, 0), at(3, 0)) };
//    Vec4 ey{ Vec4(at(0, 1), at(1, 1), at(2, 1), at(3, 1))  };
//    Vec4 ez{ Vec4(at(0, 2), at(1, 2), at(2, 2), at(3, 2)) };
//    Vec4 ew{ Vec4(at(0, 3), at(1, 3), at(2, 3), at(3, 3)) };
//    return Mat4(ex, ey, ez, ew);
//}

//Float Mat4::det() const
//{
//
//}

// ----------------------------------------------
// Operators

std::ostream& vml::operator << (std::ostream& os, const Mat4& m)
{
    return os << parse::toString(m);
}


// ----------------------------------------------
// Namespace Methoden

/**
 * @brief Look-At-Matrix.
 *
 * Implementierung von https://stackoverflow.com/a/6802424/5416171.
 * creates a viewing matrix derived from an eye point, a reference point indicating the center of the scene, and an UP vector.
 *
 * @param eye Specifies the position of the eye (camera) point
 * @param center Specifies the position of the reference point
 * @param up Specifies the direction of the up vector
 */
Mat4 vml::lookAt(const Vec3& from, const Vec3& to, const Vec3& up = Vec3(0, 1, 0))
{
    Vec3 f{ (from-to).normalized() };
    Vec3 s{ cross(f,up).normalized() };
    Vec3 u{ cross(s,f).normalized() };
    
    Vec4 ex {s.x, u.x, f.x, 0};
    Vec4 ey {s.y, u.y, f.y, 0};
    Vec4 ez {s.z, u.z, f.z, 0};
    Vec4 ew {  0,   0,   0, 1};
    return Mat4(ex, ey, ez, ew);
}

/**
 * @brief Orthogonale Projectionsmatrix.
 *
 * Implementierung von https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glOrtho.xml
 * Beschreibe eine Transformation, die eine parallele Projektion produziert.
 *
 * @param left gibt die Koordinate der linken vertikalen Clipping-Ebene an.
 * @param right gibt die Koordinate der rechten vertikalen Clipping-Ebene an.
 * @param top gibt die Koordinate der oberen horizontalen Clipping-Ebene an.
 * @param bottom gibt die Koordinate der unteren horizontalen Clipping-Ebene an.
 * @param near gibt den Abstand zur nahen Clipping-Ebene in der Tiefe an. Wenn diese Ebenen hinter dem Betrachter ist, ist dieser Wert negativ
 * @param far gibt den Abstand zu fernen Clipping-Ebene in der Tiefe an.
 */
Mat4 vml::ortho(Float left, Float right, Float bottom, Float top, Float near, Float far)
{
    return {
        Vec4{ 2.f/(right-left), 0, 0, -(right+left)/(right-left) },
        Vec4{ 0, 2.f/(top-bottom), 0, -(top+bottom)/(top-bottom) },
        Vec4{ 0, 0, -2.f/(far-near), -(far+near)/(far-near)},
        Vec4{ 0, 0, 0, 1}
    };
}

// ----------------------------------------------
// Debugging

/**
 * @brief Print Overload.
 *
 * Printet die 16 Einträgt formatiert in die Konsole.
 *
 * @param os Outstream (cout)
 * @param m eine Mat4
 */
std::string vml::parse::toString(const Mat4& m)
{
    std::stringstream ss;
    ss << "(";
    for (int row{0}; row < Mat4::vSize; row++) {
        ss << "\t";
        for (int col{0}; col < Mat4::vSize; col++) {
            ss << m.at(row, col);
            ss << ((col < Mat4::vSize-1) ? "," : "");
        }
        ss << ((row < Mat4::vSize-1) ? "" : "\t)") << "\n";
    }
    ss << std::endl;
    return ss.str();
}
