SET(VML_SOURCE_FILES
   src/Vec2.cpp
   src/Vec3.cpp
   src/Vec4.cpp
   src/Mat4.cpp
   src/Arc.cpp
   src/ArcShape.cpp
   src/Cashew.cpp
   src/Complex.cpp
   src/Polynomial.cpp
   src/fft.cpp
   src/parse.cpp
   src/Interval.cpp
   src/Base.cpp
)

SET(VML_HEADER_FILES
   Basics.h
   Vec2.h
   Vec3.h
   Vec4.h
   Mat4.h
   Arc.h
   ArcShape.h
   Cashew.h
   Graph.h
   Complex.h
   Polynomial.h
   fft.h
   parse.h
   Interval.h
   Base.h
)

add_library(vml ${VML_SOURCE_FILES} ${VML_HEADER_FILES})
target_include_directories(vml PUBLIC ..)

set_target_properties(vml PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
)
