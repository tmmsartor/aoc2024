add_subdirectory(utils)

add_executable(main main.cpp)
target_include_directories(main PRIVATE ${CMAKE_SOURCE_DIR}/src/utils/)
target_include_directories(main PRIVATE ${CMAKE_SOURCE_DIR}/src/)

function(add_day day_nr)
  string(LENGTH "${day_nr}" len)
  string(SUBSTRING "00${day_nr}" ${len} 2 nn)
  add_subdirectory(${nn})
  target_link_libraries(main PRIVATE day${nn})
  target_compile_definitions(main PRIVATE DAY${nn}=1)
endfunction()

foreach(i RANGE 0 25)
  add_day(${i})
endforeach()
