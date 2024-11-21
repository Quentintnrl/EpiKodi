target_sources(EpiKodiLib
  PRIVATE
  App.cpp
  App.hpp
)

add_subdirectory(appElements)
add_subdirectory(GraphicEvent)
add_subdirectory(mediaPagesManager)
add_subdirectory(settingsBoxesManager)

target_include_directories(EpiKodiLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
