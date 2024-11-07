target_sources(Parser PRIVATE
  Parser.cpp
  Parser.hpp
)

set_target_properties(Parser PROPERTIES POSITION_INDEPENDENT_CODE ON)
add_subdirectory(Json)


target_include_directories(EpiKodiLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(Graphic PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Parser PUBLIC ParserLib Debug)
