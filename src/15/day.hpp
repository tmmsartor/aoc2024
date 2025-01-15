#ifndef DAY15_H
#define DAY15_H

#include "aoc.hpp"
#include "print.hpp"
#include "grid2d.hpp"

namespace day15{

struct Item {
  Point s;
  Point e;
  string t;
  int depth;
  friend ostream& operator<<(ostream& os, const Item& i) {
    return os << "(" << i.s << ", " << i.t  << ")";
  }
};


typedef vector<string> State;
typedef vector<Item> Items;
typedef string Commands;

class Day : public aoc::DayAPI {
  State state;
  Point rob;
  Commands input_seq;
 public:
  constexpr int day() override { return 15; };
  void parse(ifstream&) override;
  string part1() override;
  string part2() override;
};

}

bool compareByDepth(const day15::Item&, const day15::Item&);

#endif
