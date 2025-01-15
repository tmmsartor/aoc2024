#ifndef DAY22_H
#define DAY22_H

#include "aoc.hpp"
#include "print.hpp"

namespace day22 {

typedef unsigned long ulong;
typedef vector<int> Ints;
typedef tuple<int,int,int,int> DiffSeq;

struct Buyer {
  int secret;
  Ints diffs;
  Ints prices;
};


class Day : public aoc::DayAPI {
  vector<Buyer> buyers;
 public:
  constexpr int day() override { return 22; };
  void parse(ifstream&) override;
  string part1() override;
  string part2() override;
};

}

ostream& operator<<(ostream& os, const day22::DiffSeq& t);

ostream& operator<<(ostream& os, const day22::Ints& t);

#endif
