#include "day.hpp"


namespace day16{


int min_path(const Point& s,const Point& e, TracedMaze& vis, const Maze& grid, int DEBUG) {
  // dijkstra
 
  // start direction
  Point sd = {0,1};
  vis.set(s,{{sd,0}});
  int nv = 0;

  queue<tuple<Point,Point,int>> q;
  q.push({s,sd,nv});

  Point n,p;
  vector<int> res = {};

  while (!q.empty()) {
    auto [p,pd,pv] = q.front();
    q.pop();

    for (auto [d,_]: GRID2D_DIRS_MAP) {
      // skip backward direction
      if (d==-pd) continue;
      n = p+d;
      // skip invalid
      if  (!grid.is_valid(n) || grid.at(n)=='#') continue;

      if (d==pd) nv = pv+1;
      else nv = pv+1001;

      if  (n==e) {
        vis.set(n,{d,nv});
        res.emplace_back(nv);
        break;
      }

      // add new directions update if existing dir cost is worse
      if ((vis.at(n).contains(d) && vis.at(n)[d] > nv) || 
          !vis.at(n).contains(d)) {
        vis.set(n,{d,nv});
        q.push({n,d,nv});
      }
    }
  }

  if (DEBUG) cout << "possible costs: " << res << endl;
  sort(res.begin(),res.end());
  return res[0];
}

int count_spots(const Point& s,const Point& e, TracedMaze& vis, const Maze& grid, int DEBUG) {
  // backward pass
  Point n,p,pd;
  set<Point> spots;
  spots.insert(e);

  queue<tuple<Point,Point,int>> q;
  Point start_d;
  size_t min_v = UINT_MAX;

  for (auto [d,v]: vis.at(e)) {
    if (v < min_v) {
      min_v=v;
      start_d = d;
    }
  }
  spots.insert(e);
  q.push({e,start_d,min_v+1});

  while (!q.empty()) {
    auto [p,pd,pv] = q.front();
    q.pop();
    // check first neighbour
    for (auto [d,nv]: vis.at(p)){
      if (d == -pd) continue;
      n = p-d;
      // discard position already seen
      if (spots.contains(n)) continue;
      // add start
      if (n==s) {
        spots.insert(n);
        continue;
      }
      // continue only on paths which can be previous steps for current position
      if ((d==pd && nv==pv-1) || (d!=pd && nv==pv-1001)) {
        spots.insert(n);
        q.push({n,d,nv});
      }
    }
  }

  if (DEBUG) {
    Maze grid_with_spots = grid;
    for (auto s:spots) grid_with_spots.set(s,'O');
    cout << grid_with_spots << endl;
  }

  return spots.size();
}


void Day::parse(ifstream& file) {
  // Parsing
  this->lines.clear();
  this->grid.clear();
  this->visited.clear();
  Point& s = this->start;
  Point& e = this->end;

  int i,j; 
  string line;
  i = 0;
  while (getline(file, line)) {
    // search start and end
    for(j=0;j<line.length();j++)
      if (line[j]=='S') s = {i,j};
      else if (line[j]=='E') e = {i,j};
    // add line
    this->lines.emplace_back(vector<char>(line.begin(), line.end()));
    i++;
  }
  // navigable grid
  this->grid.init(std::move(lines));
  // visited paths
  this->visited.init(grid.m,grid.n);

}

string Day::part1() {
  ulong sol1 = min_path(this->start, this->end, this->visited, this->grid, this->log_level);
  return to_string(sol1);
}

string Day::part2() {
  ulong sol2 = count_spots(this->start, this->end, this->visited, this->grid, this->log_level);
  return to_string(sol2);
}

}

