add_library(dlLoader STATIC
  dlLoader.cpp
  dlLoader.hpp
)

target_include_directories(EpiKodiLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})