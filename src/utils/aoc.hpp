#ifndef AOC_H
#define AOC_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <iomanip>

#include <cmath>
#include <cassert>

#include <bitset>
#include <vector>
#include <list>
#include <queue>
#include <set>
#include <map>

#include <functional>
#include <memory>
#include <numeric>
#include <limits>
#include <algorithm>

// C++11
#include <tuple>
#include <unordered_set>
#include <unordered_map>
#include <type_traits>
#include <regex>

// C++17
#include <string_view>

// C++20
#include <concepts>
#include <format>
#include <ranges>

// C++23
#include <print>

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
