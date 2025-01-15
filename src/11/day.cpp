#include "day.hpp"
#include "print.hpp"


namespace day11{

aoc::Solution solve(const Stones& stones, int DEBUG){
  int n = 75;
  string sstr;
  long h,l;
  Stones stonesi = stones;

  size_t i = 0;
  size_t s;
  size_t c;
  size_t count = 0;
  size_t count1 = 0;
  size_t count2 = 0;

  for(i=0;i<n;i++){
    Stones tmp;
    for (auto pair : stonesi) {
      s = pair.first;
      c = pair.second;
      if (s == 0) tmp[1] += c;
      else if (!((l=(sstr = to_string(s)).length()) % 2)) {
        h = l/2;
        tmp[stoul(sstr.substr(0,h))] += c;
        tmp[stoul(sstr.substr(h))] += c;
      } else {
        tmp[s * 2024] += c;
      }
    }
    stonesi = tmp;

    if (DEBUG>1){
      for (auto pair : stonesi) count += pair.second;
      cout << i+1 << ": " << count << endl;
    }
    if (i==24) for (auto pair : stonesi) count1 += pair.second;
    if (i==74) for (auto pair : stonesi) count2 += pair.second;
  }

  return {to_string(count1),to_string(count2)};
}

void Day::parse(ifstream& file) {
  this->stones = {};
  size_t i = 0;
  string line;
  getline(file, line);
  while ((i = line.find(' ')) != std::string::npos) {
    stones[stol(line.substr(0, i))] = 1;
    line.erase(0, i + 1);
  }
  stones[stol(line)] = 1;
}

string Day::part1() {
  this->sol = solve(this->stones, this->log_level);
  return this->sol.first;
}

string Day::part2() {
  if (this->sol.second.empty()) this->sol = solve(this->stones, this->log_level);
  return this->sol.second;
}

}

