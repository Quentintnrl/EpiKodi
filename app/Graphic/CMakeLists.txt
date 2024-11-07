target_sources(Graphic PRIVATE
  Graphic.cpp
  Graphic.hpp
)

add_subdirectory(Elements)

link_libraries(GraphicLib PUBLIC Graphic)