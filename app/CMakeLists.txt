include_directories(/usr/include/uuid)
find_library(UUID_LIB uuid)
find_package(nlohmann_json 3.11.3 REQUIRED)

add_library(EpiKodiLib STATIC)

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

target_link_libraries(EpiKodi EpiKodiLib)
