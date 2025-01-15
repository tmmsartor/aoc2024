#ifndef AOC_H
#define AOC_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <format>
#include <iomanip>

#include <tuple>
#include <bitset>
#include <vector>
#include <list>
#include <queue>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <functional>

#include <memory>
#include <numeric>
#include <limits>
#include <algorithm>

#include <type_traits>
#include <concepts>

#include <cmath>
#include <cassert>

using namespace std;


typedef unsigned long ulong;

namespace aoc {

typedef pair<string,string> Solution;
typedef vector<string> InputData;

class DayAPI {
 public:
  Solution sol;
  int log_level = 0;
  void set_log_level(int n) {log_level = n;};
  virtual constexpr int day() = 0;
  virtual void parse(ifstream&) = 0;
  virtual string part1() = 0;
  virtual string part2() = 0;
};

}

#endif
