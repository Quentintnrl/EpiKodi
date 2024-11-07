# target_sources(EpiKodiLib
#   PRIVATE
#   Box.cpp
#   Box.hpp
#   Button.cpp
#   Button.hpp
#   Image.cpp
#   Image.hpp
#   Text.cpp
#   Text.hpp
# )

target_sources(Graphic
  PRIVATE
  Box.cpp
  Box.hpp
  Button.cpp
  Button.hpp
  Image.cpp
  Image.hpp
  Text.cpp
  Text.hpp
)


target_include_directories(EpiKodiLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(Graphic PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
