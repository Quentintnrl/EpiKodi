add_library(Add-ons STATIC
  Add-ons.cpp
  Add-ons.hpp
)
set_target_properties(Add-ons PROPERTIES POSITION_INDEPENDENT_CODE ON)

target_include_directories(EpiKodiLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
