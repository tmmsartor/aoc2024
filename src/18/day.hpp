#ifndef DAY18_H
#define DAY18_H

#include "aoc.hpp"
#include "print.hpp"
#include "grid2d.hpp"

namespace day18 {

inline static size_t GRID_SIZE=71;
inline static size_t NBYTES=1024;

inline static size_t GRID_SIZE_TEST=7;
inline static size_t NBYTES_TEST=12;

class Day : public aoc::DayAPI {
  Points coords;
  aoc::Solution sol;
  aoc::InputData lines;
  bool is_test = false;
  size_t grid_size = GRID_SIZE;
  size_t n_bytes = NBYTES;
 public:
  constexpr int day() override { return 18; };
  void parse(ifstream&) override;
  string part1() override;
  string part2() override;
};

}

#endif
