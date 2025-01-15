#ifndef DAY14_H
#define DAY14_H

#include "aoc.hpp"
#include "print.hpp"

namespace day14{

struct State {
  pair<int,int> p;
  pair<int,int> v;
};

typedef vector<State> States;
typedef vector<vector<int>> Space;

class Day : public aoc::DayAPI {
  States states;
  Space space;
  int m;
  int n;
  bool is_test;
 public:
  constexpr int day() override { return 14; };
  void parse(ifstream&) override;
  string part1() override;
  string part2() override;
};

}

ostream& operator<<(std::ostream&, const day14::State&);

#endif
