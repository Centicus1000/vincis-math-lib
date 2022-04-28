#include "vml/mat4.h"

using namespace vml;

// ----------------------------------------------
// Konstruktoren

/**
 * @brief Vektor Konstruktor.
 *
 * Initialisiert die Matrix über vier Zeilenvektoren, damit folgende Schreibweise möglich wird:
 *  `mat4{
 *      vec4(d, 0, 0, 0),
 *      vec4(0, d, 0, 0),
 *      vec4(0, 0, d, 0),
 *      vec4(0, 0, 0, d) };
 *  `
 */
mat4::mat4(const vec4& ex, const vec4& ey, const vec4& ez, const vec4& ew) :
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
mat4::mat4(float d) :
mat4(vec4(d, 0, 0, 0),
     vec4(0, d, 0, 0),
     vec4(0, 0, d, 0),
     vec4(0, 0, 0, d))
{}

/**
 * @brief Einheitsmatrix (Default Konstructor).
 *
 * Ruft den Diagonal Konstruktor mit dem Parameter 1 auf, wodruch eine Einheitsmatrix erschaffen wird.
 */
mat4::mat4() : mat4(1.f)
{}

// ----------------------------------------------
// Zugang zu Einträgen

/**
 * @brief Datenpointer.
 *
 * Gibt den Pointer zum ersten Eintrag zurück.
 * Diese Funktion wird häufig in OpenGL verwendet, um Matrizen in Shader zu laden.
 */
float* mat4::data()
{
    return &M[0];
}

///@{
/**
 * @brief Indizierung.
 *
 * Übergibt den Index an den internen Datenspeicher `M`, wodurch alle 16 Einträge direkt zugänglich sind.
 */
float& mat4::operator[] (int i)
{
    return M[i];
}
const float& mat4::operator[] (int i) const
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
float& mat4::at(int row, int col)
{
    return M[row * v_size + col];
}
float mat4::at(int row, int col) const
{
    return M[col * v_size + row];
}
///@}

/**
 * @brief Zeilen Zugang.
 *
 * Erstellt einen Vec4 auf den Einträgen in der Zeile und gibt diesen zurück. Die Referenz zu den Daten geht dabei verloren
 */
vec4 mat4::row(int i) const
{
    return vec4(at(i,0), at(i,0), at(i,0), at(i,0));
}

/**
 * @brief Spalten Zugang.
 *
 * Erstellt einen Vec4 auf den Einträgen in der Spalten und gibt diesen zurück. Die Referenz zu den Daten geht dabei verloren
 */
vec4 mat4::col(int i) const
{
    return vec4(at(0,i), at(1,i), at(2,i), at(3,i));
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
mat4 vml::lookat(const vec3& from, const vec3& to, const vec3& up = vec3(0, 1, 0))
{
    vec3 f{ (from-to).normalized() };
    vec3 s{ cross(f,up).normalized() };
    vec3 u{ cross(s,f).normalized() };
    
    vec4 ex {s.x, u.x, f.x, 0};
    vec4 ey {s.y, u.y, f.y, 0};
    vec4 ez {s.z, u.z, f.z, 0};
    vec4 ew {  0,   0,   0, 1};
    return mat4(ex, ey, ez, ew);
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
mat4 vml::ortho(float left, float right, float bottom, float top, float near, float far)
{
    return {
        vec4{ 2.f/(right-left), 0, 0, -(right+left)/(right-left) },
        vec4{ 0, 2.f/(top-bottom), 0, -(top+bottom)/(top-bottom) },
        vec4{ 0, 0, -2.f/(far-near), -(far+near)/(far-near)},
        vec4{ 0, 0, 0, 1}
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
std::ostream& ::vml::operator << (std::ostream& os, const mat4& m) {
    os << "(";
    for (int row{0}; row < mat4::v_size; row++) {
        os << "\t";
        for (int col{0}; col < mat4::v_size; col++) {
            os << m.at(row, col);
            os << ((col < mat4::v_size-1) ? "," : "");
        }
        os << ((row < mat4::v_size-1) ? "" : "\t)") << "\n";
    }
    os << std::endl;
    return os;
}
