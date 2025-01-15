#ifndef DAY21_H
#define DAY21_H

#include "aoc.hpp"
#include "print.hpp"
#include "grid2d.hpp"

namespace day21 {

typedef vector<string> Codes;
typedef map<char,Point> Pad;
typedef map<Point,char> Lookup;
typedef unsigned long ulong;

// Constants
static const Pad NUMPAD = {
  {'7',{0,0}},{'8',{0,1}},{'9',{0,2}},
  {'4',{1,0}},{'5',{1,1}},{'6',{1,2}},
  {'1',{2,0}},{'2',{2,1}},{'3',{2,2}},
  {'X',{3,0}},{'0',{3,1}},{'A',{3,2}},
};

static const Pad DIRPAD = {
  {'X',{0,0}},{'^',{0,1}},{'A',{0,2}},
  {'<',{1,0}},{'v',{1,1}},{'>',{1,2}},
};


class Day : public aoc::DayAPI {
  Codes codes;
  aoc::Solution sol;
 public:
  constexpr int day() override { return 21; };
  void parse(ifstream&) override;
  string part1() override;
  string part2() override;
};

}

#endif
