set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/..")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../libs")

include_directories(/usr/include/uuid)
find_library(UUID_LIB uuid)
find_package(nlohmann_json 3.11.3 REQUIRED)

# find_library(VLC_LIB libvlc REQUIRED)
# find_library(VLC_CORE_LIB libvlccore REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBVLC REQUIRED libvlc)

include_directories(${LIBVLC_INCLUDE_DIRS})
link_directories(${LIBVLC_LIBRARY_DIRS})

add_library(EpiKodiLib STATIC)
add_library(Parser SHARED)
add_library(Graphic SHARED)

target_include_directories(EpiKodiLib PUBLIC include)

if(UUID_LIB)
    target_link_libraries(EpiKodiLib ${UUID_LIB})
endif()
target_link_libraries(EpiKodiLib nlohmann_json::nlohmann_json)

add_executable(EpiKodi
    src/main.cpp
)

target_include_directories(EpiKodiLib PUBLIC
)

add_subdirectory(lib)
add_subdirectory(src)
add_subdirectory(Parser)
add_subdirectory(Graphic)
add_subdirectory(games)

target_link_libraries(EpiKodi EpiKodiLib)
target_link_libraries(EpiKodi UuidLib)
target_link_libraries(EpiKodi GraphicLib)
target_link_libraries(EpiKodi ParserLib)
target_link_libraries(EpiKodi ParserJsonLib)
target_link_libraries(EpiKodi Debug)
target_link_libraries(EpiKodi Add-ons)

target_link_libraries(Graphic Debug)
target_link_libraries(Graphic UuidLib)
target_link_libraries(Graphic ParserJsonLib)
target_link_libraries(Graphic ${LIBVLC_LIBRARIES})
