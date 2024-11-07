add_library(GraphicLib STATIC
  AGraphic.cpp
  AGraphic.hpp
  AGraphicElem.cpp
  AGraphicElem.hpp
  IGraphicElem.hpp
  IGraphic.hpp
)

set_target_properties(GraphicLib PROPERTIES POSITION_INDEPENDENT_CODE ON)

add_subdirectory(Elements)

target_include_directories(EpiKodiLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(GraphicLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(Graphic PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
