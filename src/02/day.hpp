#ifndef DAY02_H
#define DAY02_H

#include "aoc.hpp"
#include "print.hpp"


namespace day02 {

// Types
typedef vector<int> Level;
typedef vector<Level> Levels;

class Day : public aoc::DayAPI {
  Levels levels;
 public:
  constexpr int day() override { return 2; }
  void parse(ifstream&) override;
  string part1() override;
  string part2() override;
};

}

#endif
