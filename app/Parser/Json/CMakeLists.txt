target_sources(Parser
  PRIVATE
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

add_library(ParserJsonLib STATIC
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

set_target_properties(ParserJsonLib PROPERTIES POSITION_INDEPENDENT_CODE ON)

message(STATUS "CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}/../../lib/Debug")
target_include_directories(ParserJsonLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../lib/Debug)
target_link_libraries(ParserJsonLib Debug)

target_include_directories(EpiKodiLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(GraphicLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(Graphic PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(Parser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(ParserLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
