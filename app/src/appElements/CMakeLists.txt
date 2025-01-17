target_sources(EpiKodiLib
  PRIVATE
  appElement.cpp
  appElement.hpp
  Box.cpp
  Box.hpp
  Button.cpp
  Button.hpp
  Image.cpp
  Image.hpp
  Page.cpp
  Page.hpp
  PopUp.cpp
  PopUp.hpp
  Text.cpp
  Text.hpp
)

target_include_directories(EpiKodiLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
