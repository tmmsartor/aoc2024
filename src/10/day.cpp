#include "day.hpp"

namespace day10{

int DEBUG = 0;

void show(const CellQueue& q) {
  CellQueue temp = q;
  Cell c;
  while (!temp.empty()) {
    c = temp.front();
    cout << "q:" <<  c.i << ',' << c.j << ":" << c.v  << ' ';
    temp.pop();
  }
  cout << endl;
}

pair<int,int> compute_score(const TrailMap& tmap, int i, int j) {
  int rating = 0;
  set<int> score = {};
  int size = tmap.size();

  CellQueue q = {};
  q.push({i,j,0});

  while (!q.empty()) {
    auto p = q.front();
    int nv = p.v +1;
    q.pop();
    //show(q);

    for (auto n : {Cell{p.i-1,p.j,nv}, {p.i+1,p.j,nv}, {p.i,p.j-1,nv}, {p.i,p.j+1,nv}}) {
      if (n.i >= 0 && n.i < size && n.j >= 0 && n.j < size && tmap[n.i][n.j]==nv) {
        //cout << i << "," << j << ":" << nv << endl;
        if (nv == 9) {
          score.insert(n.i*size+n.j);
          rating++;
        }
        else q.push({n.i,n.j,nv});
      }
    }
  }

  return {score.size(), rating};
}

aoc::Solution solve(const TrailMap& tmap) {
  size_t tot_score = 0;
  size_t tot_rating = 0;
  size_t i,j;
  for (i=0;i<tmap.size();i++){
    for (j=0;j<tmap.size();j++){
        if (tmap[i][j] != 0) continue; 
        auto [score, rating] =  compute_score(tmap, i,j);
        tot_score += score;
        tot_rating += rating;
    }
  }
  return {to_string(tot_score),to_string(tot_rating)};
}


void Day::parse(ifstream& file) {
  this->tmap = {};
  string line;
  int num = 0;
  size_t j = 0;
  size_t i = 0;
  while (std::getline(file, line)) {
    this->tmap.push_back(vector<int>(line.length(),0));
    for (j = 0; j < line.length(); j++) tmap[i][j] = line[j] - '0';
    i++;
  }
}

string Day::part1() {
  this->sol = solve(this->tmap);
  return this->sol.first;
}

string Day::part2() {
  if (this->sol.second.empty())
    this->sol = solve(this->tmap);
  return this->sol.second;
}

}
