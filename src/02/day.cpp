#include "day.hpp"

using namespace std::literals::string_view_literals;
namespace day02 {


bool sign(int n) {
  return  (n<0)  ?  false : true;
}

void Day::parse(ifstream& file) {
  this->levels = {};

  Level level;
  string line;
  stringstream ss;

  // loop over input lines
  while (getline(file, line)) {
    level.clear();
    // using <string_view>
    for (auto word : string_view(line) | views::split(" "sv))
        level.push_back(stoi(string(word.begin(), word.end())));
    this->levels.push_back(level);
  }

  if (this->log_level>1) cout << this->levels << endl;
}

// alternative parse
void parse_iterators(ifstream& file, Levels& levels, int log_level) {
  Level level;
  string line;
  stringstream ss;

  // loop over input lines
  while (getline(file, line)) {
    level.clear();
    ss.clear();
    ss.str(line);
    // using stream_interator form <iterator>
    copy(
      istream_iterator<int>(ss),
      istream_iterator<int>(),
      back_inserter(level)
    );
    levels.push_back(level);
  }

  if (log_level>1) cout << levels << endl;
}

bool check_diff(int n, int trend) {
  return (n==0) || n<-3 || n>3 || sign(n)!=sign(trend);
}
bool check_level(auto& level){
    int trend = level[1]-level[0];
    auto diffs = level
           | views::slide(2)
           | views::transform([](auto&& p) {return p[1]-p[0];});
    return ranges::none_of(diffs,[trend](int diff) {return check_diff(diff,trend);});
}

ulong solve(bool part, Levels& levels) {
  int count=0;
  int trend=0;
  for (auto& level: levels){
    if (level.size()<2) continue;
    // part 1
    if (check_level(level)) {
      count++;
      continue;
    }
    // part 2 check subragenge missing one element
    if (part) {
      for (int i=0;i<level.size();i++) {
        auto filtered_level = level
                 | views::enumerate
                 | views::filter([i](auto p) { return get<0>(p) != i;})
                 | views::transform([](auto p) {return get<1>(p);})
                 | ranges::to<Level>();
        // TODO avoid coverting to vector  maybe

        if (check_level(filtered_level)) {
          count++;
          break;
        }
      }
    }

  }
  return count;
}

string Day::part1() {
  return to_string(solve(0, this->levels));}

string Day::part2() {
  return to_string(solve(1, this->levels));}

}
