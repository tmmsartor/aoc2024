#ifndef DAY25_H
#define DAY25_H

#include "aoc.hpp"
#include "print.hpp"

namespace day25 {

typedef tuple<int,int,int,int,int> Key;
typedef vector<Key> Keys;

class Day : public aoc::DayAPI {
  Keys keys;
  Keys locks;
 public:
  constexpr int day() override { return 25; };
  void parse(ifstream&) override;
  string part1() override;
  string part2() override;
};

}

ostream& operator<<(ostream&, const day25::Keys&);
ostream& operator<<(ostream&, const day25::Key&);


#endif
