#ifndef DAY19_H
#define DAY19_H

#include "aoc.hpp"
#include "print.hpp"

namespace day19{

typedef vector<string> Search;
typedef set<string> Towels;
typedef map<string,long long> Count;

class Day : public aoc::DayAPI {
  Towels tm;
  Search ts;
  aoc::Solution sol;
 public:
  constexpr int day() override { return 19; };
  void parse(ifstream&) override;
  string part1() override;
  string part2() override;
};

}

#endif
