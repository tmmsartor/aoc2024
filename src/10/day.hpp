#ifndef DAY10_H
#define DAY10_H

#include "aoc.hpp"
#include "print.hpp"

namespace day10{

typedef vector<vector<int>> TrailMap;
struct Cell {
  int i;
  int j;
  int v;
};
typedef queue<Cell> CellQueue;


void show(CellQueue&);
pair<int,int> compute_score(TrailMap&, int, int);


class Day : public aoc::DayAPI {
  TrailMap tmap;
 public:
  constexpr int day() override { return 10; }
  void parse(ifstream&) override;
  string part1() override;
  string part2() override;
};

}

#endif


