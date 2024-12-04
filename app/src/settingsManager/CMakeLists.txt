target_sources(EpiKodiLib
  PRIVATE
  settingsManager.cpp
  settingsManager.hpp
)

target_include_directories(EpiKodiLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
