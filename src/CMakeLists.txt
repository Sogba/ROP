find_package(SFML 3.0 COMPONENTS Graphics Window System REQUIRED)

add_subdirectory(sfml)
add_subdirectory(core)

add_executable(
    ROP
    WIN32
    main.cpp
)

if (WIN32)
    target_sources(ROP PRIVATE winmain.cpp)
endif()

target_include_directories(ROP PUBLIC 
  sfml
  core
)

target_link_libraries(ROP PUBLIC
  sfml
  core
  SFML::Graphics 
  SFML::Window 
  SFML::System 
  ImGui-SFML::ImGui-SFML
)