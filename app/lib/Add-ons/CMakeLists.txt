add_library(Add-ons STATIC
  Add-ons.cpp
  Add-ons.hpp
)
set_target_properties(Add-ons PROPERTIES POSITION_INDEPENDENT_CODE ON)

add_subdirectory(Movie_add-on)
add_subdirectory(Music_add-on)

target_include_directories(EpiKodiLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(MovieAddOn PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(MusicAddOn PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

