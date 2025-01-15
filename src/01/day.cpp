#include "day.hpp"


namespace day01 {

void InputData::clear() {
  this->s.clear();
  this->f.clear();
}

void InputData::print() {
  for (int i=0; i< this->f.size(); i++)
    cout << this->f[i] << " " << this->s[i] << endl;
}

void Day::parse(ifstream& file) {
  this->data.clear();
  string line;
  vector<int> nums = {};

  while (getline(file, line)){
    if (line.empty()) continue;
    stringstream ss(line);
    string num;
    while (getline(ss, num, ' ')) {
      if (!num.size()) continue;
      nums.push_back(stol(num));
    }
    if (nums.size() == 2) {
      this->data.f.push_back(nums[0]);
      this->data.s.push_back(nums[1]);
    }
    nums.clear();
  }
  
}

string Day::part1() {
  int sol1 = 0;
  InputData& d = this->data;

  sort(d.f.begin(), d.f.end());
  sort(d.s.begin(), d.s.end());

  for (int i=0; i< d.f.size();i++)
    sol1 += abs(d.f[i]-d.s[i]);

  return to_string(sol1);
}

string Day::part2() {
  int sol2 = 0;
  InputData& d = this->data;
  map<int, int> occurrences;

  for(int num : d.s) occurrences[num]++;
  for (int fi:d.f) 
    sol2 += occurrences[fi]*fi;

  return to_string(sol2);
}

}

