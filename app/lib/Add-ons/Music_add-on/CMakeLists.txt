add_library(MusicAddOn SHARED
  MusicAddOn.cpp
  MusicAddOn.hpp
)

# Find and link CPR
find_package(cpr REQUIRED CONFIG)
target_link_libraries(MusicAddOn PRIVATE cpr::cpr)

# Find and link nlohmann_json
find_package(nlohmann_json REQUIRED CONFIG)
target_link_libraries(MusicAddOn PRIVATE nlohmann_json::nlohmann_json)

target_link_libraries(MusicAddOn PRIVATE Add-ons)
set_target_properties(MusicAddOn PROPERTIES POSITION_INDEPENDENT_CODE ON)
