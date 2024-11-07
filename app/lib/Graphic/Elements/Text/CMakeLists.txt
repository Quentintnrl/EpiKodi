# target_sources(EpiKodiLib
#   PRIVATE
#   AText.hpp
#   AText.cpp
#   IText.hpp
# )

target_sources(GraphicLib
  PRIVATE
  AText.hpp
  AText.cpp
  IText.hpp
)

target_include_directories(EpiKodiLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(GraphicLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(Graphic PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
