target_sources(EpiKodiLib
  PRIVATE
  App.cpp
  App.hpp
  Debug.cpp
  Debug.hpp
)

target_include_directories(EpiKodiLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
