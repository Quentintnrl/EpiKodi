target_sources(EpiKodiLib
  PRIVATE
  Parser.cpp
  Parser.hpp
)

add_subdirectory(Json)

target_include_directories(EpiKodiLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
