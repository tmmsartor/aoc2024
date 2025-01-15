#include "day.hpp"

ostream& operator<<(ostream& os, const day25::Keys& ks) {
  os << endl;
  for (auto k: ks) os << k << endl;
  return os;
}
ostream& operator<<(ostream& os, const day25::Key& t) {
  return os << "("<<get<0>(t)<<","<<get<1>(t)<<","<<get<2>(t)<<","<< get<3>(t)<<","<< get<4>(t)<<")";
}

namespace day25 {

void Day::parse(ifstream& file) {
  string line;
  Keys* group;
  this->locks.clear();
  this->keys.clear();
  bool eof = false;
  Key k;

  while (getline(file, line)) {
    k = {0,0,0,0,0};

    if (line=="#####") group = &locks;
    else group = &keys;

    for (int i=0;i<5;i++) {
      getline(file, line);
      if (line[0] == '#') get<0>(k)++;
      if (line[1] == '#') get<1>(k)++;
      if (line[2] == '#') get<2>(k)++;
      if (line[3] == '#') get<3>(k)++;
      if (line[4] == '#') get<4>(k)++;
    }
    getline(file,line);
    getline(file,line);
    group->emplace_back(k);
  }

  if (this->log_level) cout << locks << endl;
  if (this->log_level) cout << keys << endl;

}

string Day::part1() {
  ulong sol1 = 0;

  for (auto k: keys)
    for (auto l: locks)
      if ((get<0>(l)+get<0>(k)<=5) &&
          (get<1>(l)+get<1>(k)<=5) &&
          (get<2>(l)+get<2>(k)<=5) &&
          (get<3>(l)+get<3>(k)<=5) &&
          (get<4>(l)+get<4>(k)<=5)) sol1++;

  return to_string(sol1);
}

string Day::part2() {
  ulong sol2 = 0;
  return to_string(sol2);
}

}

