#ifndef DAY23_H
#define DAY23_H

#include "aoc.hpp"
#include "print.hpp"

namespace day23 {

typedef pair<string,string> Link;
typedef vector<Link> Links;
typedef set<string> Set;
typedef set<Set> Sets;
typedef map<string,set<string>> Graph;

class Day : public aoc::DayAPI {
  Links links;
  Graph graph;
 public:
  constexpr int day() override { return 23; };
  void parse(ifstream&) override;
  string part1() override;
  string part2() override;
};

}

#endif
