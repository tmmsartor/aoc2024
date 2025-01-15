#ifndef DAY07_H
#define DAY07_H

#include "aoc.hpp"
#include "print.hpp"


namespace day07 {

// Types
typedef vector<ulong> Nums;
typedef pair<ulong,Nums> Equation;
typedef vector<Equation> Equations;
typedef queue<pair<ulong,size_t>> PartialsRes;

class Day : public aoc::DayAPI {
  Equations equations;
 public:
  constexpr int day() override { return 7; }
  void parse(ifstream&) override;
  string part1() override;
  string part2() override;
};

}
ostream& operator<<(ostream&, const day07::Equations&);

#endif
