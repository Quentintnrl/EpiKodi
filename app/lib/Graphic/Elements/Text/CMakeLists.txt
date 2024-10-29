target_sources(EpiKodiLib
  PRIVATE
  AText.hpp
  AText.cpp
  IText.hpp
)

target_include_directories(EpiKodiLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
