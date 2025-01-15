#ifndef DAY09_H
#define DAY09_H

#include "aoc.hpp"
#include "print.hpp"

namespace day09{

struct File {
  int id;
  int size;
  int position;
  File(int id,int size,int position) : id(id), size(size), position(position) {};
};

class DiskCompactor {
 private:
  vector<int> disk;
  vector<pair<int,int>> spaces;
  deque<File> files;
 public:
  void show(vector<int>&);
  void parseInput(const std::string&);
  vector<int> compact1();
  vector<int> compact2();
  ulong checksum(vector<int>&);
};

class Day : public aoc::DayAPI {
  DiskCompactor disk_compactor;
 public:
  constexpr int day() override { return 9; }
  void parse(ifstream&) override;
  string part1() override;
  string part2() override;
};

}

#endif
