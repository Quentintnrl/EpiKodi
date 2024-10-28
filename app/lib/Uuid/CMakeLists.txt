target_sources(EpiKodiLib
  PRIVATE
  IUuid.hpp
  Uuid.cpp
  Uuid.hpp
)

target_include_directories(EpiKodiLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
