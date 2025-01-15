#ifndef DAY12_H
#define DAY12_H

#include "aoc.hpp"
#include "print.hpp"
#include "grid2d.hpp"


namespace day12 {

typedef vector<string> Map;
typedef map<char,pair<int,int>> Geometries;
typedef set<Point> Region;
typedef vector<Region> Regions;

class Day : public aoc::DayAPI {
 protected:
  Map map;
  Regions regions;
 public:
  constexpr int day() override { return 12; };
  void parse(ifstream&) override;
  string part1() override;
  string part2() override;
};

}

#endif
