SET(VML_SOURCE_FILES
   src/Vec2.cpp
   src/Vec3.cpp
   src/Vec4.cpp
   src/mat4.cpp
   src/Arc.cpp
   src/arcshape.cpp
   src/cashew.cpp
   src/complex.cpp
   src/polynomial.cpp
   src/fft.cpp
   src/parse.cpp
   src/interval.cpp
   src/base.cpp
   src/cardgame.cpp
)

SET(VML_HEADER_FILES
   basics.h
   Vec2.h
   Vec3.h
   Vec4.h
   mat4.h
   Arc.h
   arcshape.h
   cashew.h
   graph.h
   complex.h
   polynomial.h
   fft.h
   parse.h
   interval.h
   base.h
   cardgame.h
)

add_library(vml ${VML_SOURCE_FILES} ${VML_HEADER_FILES})
target_include_directories(vml PUBLIC ..)

set_target_properties(vml PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
)
