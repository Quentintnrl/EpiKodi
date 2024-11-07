# target_sources(EpiKodiLib
#   PRIVATE
#   AParser.cpp
#   AParser.hpp
#   IParser.hpp
# )

add_library(ParserLib STATIC
  AParser.cpp
  AParser.hpp
  IParser.hpp
)

set_target_properties(ParserLib PROPERTIES POSITION_INDEPENDENT_CODE ON)

target_include_directories(EpiKodiLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(Graphic PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(Parser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
