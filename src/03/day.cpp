#include "day.hpp"

namespace day03 {

void Day::parse(ifstream& file) {
  this->input_line.clear();
  string line;
  line.clear();
  while (getline(file, line)) {
    this->input_line += line;
  }
}


ulong solve(int part, Pairs& pairs, string line, int DEBUG) {
  int res = 0;
  bool active = true;

  pairs.clear();
  pair<int, int> p;

  // create regex pattern
  regex pattern(R"(mul\((\d{1,3}),(\d{1,3})\)|(do\(\))|(don't\(\)))");

  // Use std::sregex_iterator to find all matches
  for (sregex_iterator i = sregex_iterator(line.begin(), line.end(), pattern); 
      i != sregex_iterator(); ++i) {
      smatch match = *i;

      if ((active || !part) && match[1].matched && match[2].matched) {
        p = {stoi(match[1].str()), stoi(match[2].str())};
        if (DEBUG>1) cout << p << endl;
        pairs.push_back(p);
      } else if (match[3].matched) {
        if (DEBUG>1) cout << match[3].str() << endl;
        active = true;
      } else if (match[4].matched) {
        if (DEBUG>1) cout << match[4].str() << endl;
        active = false;
      }
  }

  for (auto p: pairs) res += p.first * p.second;

  if (DEBUG) cout << res << endl;
  return res;
}

string Day::part1() {
  return to_string(solve(0, this->pairs, this->input_line, this->log_level));}

string Day::part2() {
  return to_string(solve(1, this->pairs, this->input_line, this->log_level));}

}
