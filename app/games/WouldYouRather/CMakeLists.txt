set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../games")

# Find SFML (make sure to specify the correct version)
find_package(SFML 2.5 REQUIRED graphics window system audio)
find_package(nlohmann_json 3.11.3 REQUIRED)

add_executable(WouldYouRather
    src/Card.cpp
    src/Card.hpp
    src/Game.cpp
    src/Game.hpp
    src/Graphic.cpp
    src/Graphic.hpp
    src/main.cpp
    src/Turn.cpp
    src/Turn.hpp
)

target_link_libraries(WouldYouRather nlohmann_json::nlohmann_json)
target_link_libraries(WouldYouRather sfml-graphics sfml-window sfml-system sfml-audio)
