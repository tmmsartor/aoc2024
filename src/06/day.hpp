#ifndef DAY06_H
#define DAY06_H

#include "aoc.hpp"
#include "print.hpp"
#include "grid2d.hpp"

namespace day06 {

// Types
struct Passage {
  int step;
  Point dir;
};

struct Cell {
  int s;  // -2: guard start, -1: obstacle, 0: free
  vector<Passage> p;  // passages through this cell

  Cell() : s(0) {}
  Cell(int state) : s(state) {}
};

typedef Grid2D<Cell> GuardMap;

// Free functions
Point rotate_clockwise(const Point& dir);
set<Point> simulate_guard_path(const GuardMap& grid, Point start_pos, Point start_dir);
bool creates_loop(const GuardMap& grid, Point start_pos, Point start_dir, const Point& obstacle_pos);

class Day : public aoc::DayAPI {
  GuardMap grid;
  Point guard_start;
  int rows, cols;

 public:
  constexpr int day() override { return 6; }
  void parse(ifstream&) override;
  string part1() override;
  string part2() override;
};

}

#endif
