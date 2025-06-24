get_filename_component(DIR_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

message(DEBUG " Building ${DIR_NAME}")

#add_executable(main${DIR_NAME} main.cpp)
#target_include_directories(main${DIR_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src/include/)


# Lib
add_library(day${DIR_NAME} STATIC day.cpp)
target_include_directories(day${DIR_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src/utils)
target_link_libraries(day${DIR_NAME} PUBLIC grid2d print)

# Main
add_executable(main${DIR_NAME} ${CMAKE_SOURCE_DIR}/src/mainNN.cpp)

target_compile_definitions(main${DIR_NAME} PRIVATE NS=day${DIR_NAME})
target_include_directories(main${DIR_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src/utils/)
target_include_directories(main${DIR_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(main${DIR_NAME} PRIVATE day${DIR_NAME} grid2d graphs)
