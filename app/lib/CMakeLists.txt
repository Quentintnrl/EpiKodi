add_subdirectory(dlLoader)
add_subdirectory(Graphic)
add_subdirectory(Parser)
add_subdirectory(Uuid)
add_subdirectory(Debug)

target_include_directories(EpiKodiLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
