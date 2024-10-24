target_sources(EpiKodiLib
  PRIVATE
  AbstractJsonElem.cpp
  AbstractJsonElem.hpp
  JsonApp.cpp
  JsonApp.hpp
  JsonBox.cpp
  JsonBox.hpp
  JsonButton.cpp
  JsonButton.hpp
  JsonImage.cpp
  JsonImage.hpp
  JsonPage.cpp
  JsonPage.hpp
  JsonText.cpp
  JsonText.hpp
)

target_include_directories(EpiKodiLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
