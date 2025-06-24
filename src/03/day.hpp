#ifndef DAY03_H
#define DAY03_H

#include "aoc.hpp"
#include "print.hpp"


namespace day03 {

// Types
typedef vector<pair<int, int>> Pairs;

class Day : public aoc::DayAPI {
  Pairs pairs;
  string input_line;
 public:
  constexpr int day() override { return 3; }
  void parse(ifstream&) override;
  string part1() override;
  string part2() override;
};

}

#endif
