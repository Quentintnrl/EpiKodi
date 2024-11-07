target_sources(EpiKodiLib
  PRIVATE
  App.cpp
  App.hpp
)

add_library(Debug STATIC
  Debug.cpp
  Debug.hpp
)

target_include_directories(EpiKodiLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(GraphicLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(ParserLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(UuidLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(Graphic PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
