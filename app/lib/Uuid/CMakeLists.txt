add_library(UuidLib STATIC
  IUuid.hpp
  Uuid.cpp
  Uuid.hpp
)

set_target_properties(UuidLib PROPERTIES POSITION_INDEPENDENT_CODE ON)

target_include_directories(EpiKodiLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(GraphicLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(Graphic PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
