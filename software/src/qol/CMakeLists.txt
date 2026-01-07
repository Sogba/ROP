add_library(qol STATIC
  clock.cpp
  terminalOutput.cpp
  multithread.cpp
  idkwheretoputitsoitshere.cpp
  d7.hpp
  qol.h
)

target_link_libraries(qol PUBLIC
  SFML::Graphics 
  SFML::Window 
  SFML::System 
)