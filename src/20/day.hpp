#ifndef DAY20_H
#define DAY20_H

#include "aoc.hpp"
#include "print.hpp"
#include "grid2d.hpp"

namespace day20 {

typedef vector<string> Maze;
typedef Mat<int> CostToGo;
typedef vector<Point> Run;

inline static int MIN_SPEEDUP = 100;
inline static int MIN_SPEEDUP_TEST = 64;

class Day : public aoc::DayAPI {
  Maze maze;
  CostToGo grid_cost;
  size_t grid_size;
  Point start;
  Point end;
  Run run;
  int min_speedup = MIN_SPEEDUP;
  bool is_test;
 public:
  constexpr int day() override { return 20; };
  void parse(ifstream&) override;
  string part1() override;
  string part2() override;
};

}

#endif
