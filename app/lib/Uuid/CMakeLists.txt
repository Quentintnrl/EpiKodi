# target_sources(EpiKodiLib
#   PRIVATE
#   IUuid.hpp
#   Uuid.cpp
#   Uuid.hpp
# )

add_library(UuidLib STATIC
  IUuid.hpp
  Uuid.cpp
  Uuid.hpp
)

target_include_directories(EpiKodiLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(GraphicLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(Graphic PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
