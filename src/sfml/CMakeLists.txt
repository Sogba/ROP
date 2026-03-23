add_library(sfml STATIC sfml.cpp sfml.h)

target_include_directories(sfml PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}  
    ${SFML_INCLUDE_DIRS}  
)

target_link_libraries(sfml PUBLIC
    SFML::Graphics
    SFML::Window
    SFML::System
)
