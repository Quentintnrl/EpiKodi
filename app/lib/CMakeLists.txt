target_sources(EpiKodiLib
  PRIVATE
  AParser.cpp
  AParser.hpp
  IParser.hpp
)

target_include_directories(EpiKodiLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
