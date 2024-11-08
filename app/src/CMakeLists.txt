target_sources(EpiKodiLib
  PRIVATE
  App.cpp
  App.hpp
)

add_subdirectory(appElements)

target_include_directories(EpiKodiLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
