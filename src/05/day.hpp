#ifndef DAY05_H
#define DAY05_H

#include "aoc.hpp"
#include "graphs.hpp"
#include "print.hpp"


namespace day05 {

// Types
//
typedef unordered_set<int> Deps;
typedef unordered_map<int,Deps> RulesMap;
//typedef vector<pair<int,int>> Rules;
typedef vector<int> Book;
typedef vector<Book> Books;

class Day : public aoc::DayAPI {
  //Rules rules;
  RulesMap rulesmap;
  Books books;
  int sol2;
 public:
  constexpr int day() override { return 5; }
  void parse(ifstream&) override;
  string part1() override;
  string part2() override;
};

}

#endif
