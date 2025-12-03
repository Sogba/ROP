find_package(SFML 3.0 COMPONENTS Graphics Window System REQUIRED)

add_subdirectory(sfml)

add_executable(
    ROP
    main.cpp
    terminalOutput.cpp

)

target_include_directories(ROP PUBLIC 
  sfml
)

target_link_libraries(ROP PUBLIC
  sfml
  SFML::Graphics 
  SFML::Window 
  SFML::System 
)

