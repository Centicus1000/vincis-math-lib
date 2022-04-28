set(DEBUG_SOURCE_FILES
    main.cpp
)

add_executable(DebugVML ${DEBUG_SOURCE_FILES})
target_include_directories(DebugVML PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(DebugVML PUBLIC vml)
set_target_properties(DebugVML PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)