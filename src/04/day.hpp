#ifndef DAY04_H
#define DAY04_H

#include "aoc.hpp"
#include "grid2d.hpp"
#include "print.hpp"


namespace day04 {

// Types
typedef Grid2D<char> Grid;


class Day : public aoc::DayAPI {
  Grid grid;
 public:
  constexpr int day() override { return 4; }
  void parse(ifstream&) override;
  string part1() override;
  string part2() override;
};

}

#endif
