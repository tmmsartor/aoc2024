#include "day.hpp"


//template<>
//int DayAPI<day08::Day>::day = 8;

namespace day08{

void Day::parse(ifstream& file) {
  int i,j; 
  string line;
  char ant;
  Antennas& ants =  this->antennas;
  MapData& data = this->grid_data;
  data = {};
  ants = {};

  i = 0;
  while (getline(file, line)) {
    // search start and end
    for(j=0;j<line.length();j++)
      if ((ant = line[j]) !='.') {
        if (!ants.contains(ant)) ants[ant] = {};
        ants[ant].emplace_back(Point(i,j));
      }
    data.emplace_back(vector<char>(line.begin(), line.end()));
    i++;
  }

  if (this->log_level) cout << grid << endl;
  if (this->log_level) for (auto [a,v]: ants) cout << a << ": " << v << endl;

  this->grid.init(move(data));
}

Points get_all_collinears(const Map& grid, Point p1, Point p2){
  Points ps;
  Point diff = p2-p1;
  int i = 0;
  Point p = p1;
  while(grid.is_valid(p)) {
    ps.emplace_back(p);
    p = p + diff;
  }
  p = p2;
  while(grid.is_valid(p)) {
    ps.emplace_back(p);
    p = p - diff;
  }
  return ps;
}

void solve(bool part, const Map& grid, Antennas& atns, Antipodes& atps){
  for (auto [atn, v]: atns){
    for(auto it1 = v.begin(); it1 != v.end(); ++it1)
      for(auto it2 = next(it1); it2 != v.end(); ++it2) {
        if (!part) {
          Point diff = *it2-*it1;
          if (grid.is_valid(*it2+diff)) atps.insert(*it2+diff);
          if (grid.is_valid(*it1-diff)) atps.insert(*it1-diff);
        } else {
          for (auto p: get_all_collinears(grid,*it1,*it2)) atps.insert(p);
        }
      }
  }
}


string Day::part1() {
  // Sol1
  Antipodes antipodes;
  solve(0, this->grid, this->antennas, antipodes);
  return to_string(antipodes.size());
}

string Day::part2() {
  // Sol2
  Antipodes antipodes;
  solve(1, this->grid, this->antennas, antipodes);
  return to_string(antipodes.size());

  // Debug
  if (this->log_level){ 
    Map debug = grid;
    for (auto a: antipodes) debug.set(a,'#');
    cout << debug << endl;
  }
}

}

