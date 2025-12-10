find_package(SFML 3.0 COMPONENTS Graphics Window System REQUIRED)

add_subdirectory(sfml)
add_subdirectory(qol)

add_executable(
    ROP WIN32
    main.cpp
)

if (WIN32)
    target_sources(ROP PRIVATE winmain.cpp)
endif()

target_include_directories(ROP PUBLIC 
  sfml
  qol
)

target_link_libraries(ROP PUBLIC
  sfml
  qol
  SFML::Graphics 
  SFML::Window 
  SFML::System 
)

