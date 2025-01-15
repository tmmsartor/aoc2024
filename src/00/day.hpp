#ifndef DAY00_H
#define DAY00_H

#include "aoc.hpp"
#include "print.hpp"

namespace day00{

typedef vector<int> Something;

class Day : public aoc::DayAPI {
  Something something;
 public:
  constexpr int day() override { return 0; };
  void parse(ifstream&) override;
  string part1() override;
  string part2() override;
};

}

#endif
