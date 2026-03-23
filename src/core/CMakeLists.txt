add_library(core STATIC
  clock.cpp
  terminalOutput.cpp
  multithread.cpp
  args.cpp
  d7.hpp
  core.h
)

target_link_libraries(core PUBLIC
  SFML::Graphics 
  SFML::Window 
  SFML::System 
)