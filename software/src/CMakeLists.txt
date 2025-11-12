add_executable(ROP main.cpp)

find_package(SFML 3.0 COMPONENTS graphics window system REQUIRED)
target_link_libraries(ROP PRIVATE sfml-graphics sfml-window sfml-system)