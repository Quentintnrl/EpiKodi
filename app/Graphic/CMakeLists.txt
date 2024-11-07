# Find SFML (make sure to specify the correct version)
find_package(SFML 2.5 REQUIRED graphics window system)

target_sources(Graphic PRIVATE
  Graphic.cpp
  Graphic.hpp
)

set_target_properties(Graphic PROPERTIES POSITION_INDEPENDENT_CODE ON)

add_subdirectory(Elements)

target_link_libraries(Graphic GraphicLib)
target_link_libraries(Graphic sfml-graphics sfml-window sfml-system)
