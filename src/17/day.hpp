#ifndef DAY17_H
#define DAY17_H

#include "aoc.hpp"
#include "print.hpp"

namespace day17 {

typedef vector<ulong> Mem;

struct BitArray {
  bitset<64> data;
  bitset<64> mask;
  BitArray() : data(0) , mask(0) {};
  BitArray(bitset<64> data) : data(data) , mask(0) {};
  BitArray(bitset<64> data, bitset<64> mask) : data(data) , mask(mask) {};
  BitArray(const BitArray& other) : data(other.data), mask(other.mask) {};
  bool set(size_t, bitset<3>);
};


class Day : public aoc::DayAPI {
  Mem regs;
  Mem code;
  bool is_test;
 public:
  constexpr int day() override { return 17; };
  void parse(ifstream&) override;
  string part1() override;
  string part2() override;
};

}

ostream& operator<<(ostream&, const day17::BitArray&);

#endif
