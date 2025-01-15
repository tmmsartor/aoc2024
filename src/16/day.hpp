#ifndef DAY16_H
#define DAY16_H

#include "aoc.hpp"
#include "print.hpp"
#include "grid2d.hpp"

namespace day16{


typedef Mat<char> Lines;
typedef Grid2D<char> Maze;
typedef Grid2D<map<Point,int>> TracedMaze;

class Day : public aoc::DayAPI {
  Lines lines;
  Maze grid;
  TracedMaze visited;
  Point start;
  Point end;
 public:
  constexpr int day() override { return 16; };
  void parse(ifstream&) override;
  string part1() override;
  string part2() override;
};

}

#endif
