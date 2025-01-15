#ifndef DAY01_H
#define DAY01_H

#include "aoc.hpp"
#include "print.hpp"

namespace day01 {

struct InputData {
  vector<int> f;
  vector<int> s;
  void print();
  void clear();
};


class Day : public aoc::DayAPI {
  InputData data;
 public:
  constexpr int day() override { return 1; };
  void parse(ifstream&) override;
  string part1() override;
  string part2() override;
};

}

#endif
