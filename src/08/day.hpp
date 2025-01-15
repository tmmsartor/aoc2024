#ifndef DAY08_H
#define DAY08_H

#include "aoc.hpp"
#include "print.hpp"
#include "grid2d.hpp"

namespace day08{

typedef Grid2D<char> Map;
typedef Mat<char> MapData;
typedef map<char,Points> Antennas;
typedef set<Point> Antipodes;


class Day : public aoc::DayAPI {
  MapData grid_data;
  Antennas antennas;
  Map grid;
 public:
  constexpr int day() override { return 8;}
  void parse(ifstream&) override;
  string part1() override;
  string part2() override;
};

}

#endif
