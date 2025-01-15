#ifndef DAY13_H
#define DAY13_H

#include "aoc.hpp"
#include "print.hpp"

namespace day13{

typedef pair<long,long> Button;

struct Game {
  Button a;
  Button b;
  Button p;
};
typedef vector<Game> Games;


class Day : public aoc::DayAPI {
  Games games;
 public:
  constexpr int day() override { return 13; };
  void parse(ifstream&) override;
  string part1() override;
  string part2() override;
};

}

#endif
