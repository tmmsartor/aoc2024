#include "day.hpp"

ostream& operator<<(ostream& os, const day07::Equations& eqs) {
  for (auto e: eqs)  os << e << endl;
  return os;
}

//template<>
//int DayAPI<day07::Day>::day = 7;

namespace day07 {

void Day::parse(ifstream& file) {
  string line;
  size_t pos;
  ulong num0;
  string num_s;
  Equation eq;
  Nums nums;
  this->equations = {};
  while (getline(file, line)) {
    nums.clear();
    pos = line.find(':');
    num0 = stoul(line.substr(0,pos));
    istringstream num_ss(line.substr(pos+2));
    for (; std::getline(num_ss, num_s, ' ');)
      nums.emplace_back(stoul(num_s));
    this->equations.push_back({num0,nums});
  }

  if (this->log_level>1) cout << this->equations << endl;
}

ulong concat(ulong n0,ulong n1) {
  return stoul(to_string(n0)+to_string(n1)); 
}

ulong solve(bool part, const Equations& eqs) {
  ulong res = 0;
  PartialsRes partials;
  ulong nn = 0;
  for (auto [target, nums]: eqs) {

    partials = {};
    partials.push({nums[0],1});
    while(!partials.empty()){
      auto [n,idx] = partials.front();
      partials.pop();

      if (idx==nums.size() && n==target) {
        res += target;
        break;
      }
      if (idx==nums.size()) continue;

      if ((nn=n+nums[idx])<=target) partials.push({nn,idx+1});
      if ((nn=n*nums[idx])<=target) partials.push({nn,idx+1});
      if (part && (nn=concat(n,nums[idx]))<=target) partials.push({nn,idx+1});
    }
  }
  return res;
}

string Day::part1() {
  return to_string(solve(0, this->equations));}

string Day::part2() {
  return to_string(solve(1, this->equations));}

}
