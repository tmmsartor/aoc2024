#ifndef DAY11_H
#define DAY11_H

#include "aoc.hpp"

namespace day11{

typedef unordered_map<unsigned long,unsigned long> Stones;

class Day : public aoc::DayAPI {
  Stones stones;
 public:
  constexpr int day() override { return 11; };
  void parse(ifstream&) override;
  string part1() override;
  string part2() override;
};

}

#endif
