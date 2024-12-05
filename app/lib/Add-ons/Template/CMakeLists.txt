add_library(Template SHARED
  Template.cpp
  Template.hpp
)

target_link_libraries(Template PRIVATE Add-ons)
set_target_properties(Template PROPERTIES POSITION_INDEPENDENT_CODE ON)
