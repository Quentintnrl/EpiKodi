add_library(Add-ons STATIC
  Add-ons.cpp
  Add-ons.hpp
)
set_target_properties(Add-ons PROPERTIES POSITION_INDEPENDENT_CODE ON)

add_subdirectory(Template)

target_include_directories(EpiKodiLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(Template PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
