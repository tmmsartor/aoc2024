add_library(print SHARED print.cpp)
target_include_directories(print PUBLIC ${CMAKE_SOURCE_DIR}/src/utils)
#target_include_directories(print PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(grid2d SHARED grid2d.cpp)
target_include_directories(grid2d PUBLIC ${CMAKE_SOURCE_DIR}/src/utils)
#target_include_directories(grid2d PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
