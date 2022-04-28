SET(VML_SOURCE_FILES
   src/vec2.cpp
   src/vec3.cpp
   src/vec4.cpp
   src/mat4.cpp
   src/arc.cpp
   src/arcshape.cpp
   src/cashew.cpp
   src/complex.cpp
   src/polynomial.cpp
   src/fft.cpp
   src/cardgame.cpp
)

SET(VML_HEADER_FILES
   basics.h
   vec2.h
   vec3.h
   vec4.h
   mat4.h
   arc.h
   arcshape.h
   cashew.h
   graph.h
   complex.h
   polynomial.h
   fft.h
   cardgame.h
)

add_library(vml ${VML_SOURCE_FILES} ${VML_HEADER_FILES})
target_include_directories(vml PUBLIC ..)

set_target_properties(vml PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
)
