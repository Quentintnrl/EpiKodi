add_library(MovieAddOn SHARED
  MovieAddOn.cpp
  MovieAddOn.hpp
)

# Find and link libcurl
find_package(CURL REQUIRED)
target_link_libraries(MovieAddOn PRIVATE CURL::libcurl)

# Include nlohmann/json
find_package(nlohmann_json REQUIRED)
target_link_libraries(MovieAddOn PRIVATE nlohmann_json::nlohmann_json)

target_link_libraries(MovieAddOn PRIVATE Add-ons)
set_target_properties(MovieAddOn PROPERTIES POSITION_INDEPENDENT_CODE ON)
