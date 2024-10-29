target_sources(EpiKodiLib
  PRIVATE
  AImage.hpp
  AImage.cpp
  IImage.hpp
)

target_include_directories(EpiKodiLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
