target_sources(EpiKodiLib
  PRIVATE
  Graphic.cpp
  Graphic.hpp
)

target_sources(Graphic PRIVATE
  Graphic.cpp
  Graphic.hpp
)

add_subdirectory(Elements)

target_include_directories(EpiKodiLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

link_libraries(GraphicLib PUBLIC Graphic)
