set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../games")

find_package(nlohmann_json 3.11.3 REQUIRED)

add_executable(WouldYouRather
    src/Card.cpp
    src/Card.hpp
    src/Game.cpp
    src/Game.hpp
    src/main.cpp
    src/Turn.cpp
    src/Turn.hpp
)

target_link_libraries(WouldYouRather nlohmann_json::nlohmann_json)