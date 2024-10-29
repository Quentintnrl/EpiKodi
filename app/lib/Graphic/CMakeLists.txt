target_sources(EpiKodiLib
  PRIVATE
  AGraphic.cpp
  AGraphic.hpp
  AGraphicElem.cpp
  AGraphicElem.hpp
  IGraphicElem.hpp
  IGraphic.hpp
)

add_subdirectory(Elements)

target_include_directories(EpiKodiLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
