target_sources(Graphic
  PRIVATE
  GraphicBox.cpp
  GraphicBox.hpp
  GraphicButton.cpp
  GraphicButton.hpp
  GraphicImage.cpp
  GraphicImage.hpp
  GraphicPage.cpp
  GraphicPage.hpp
  GraphicProgressBar.cpp
  GraphicProgressBar.hpp
  GraphicText.cpp
  GraphicText.hpp
)

target_include_directories(Graphic PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(EpiKodiLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})