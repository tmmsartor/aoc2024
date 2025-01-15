#include "day.hpp"

namespace day12{

void grow_region(const Point& p, Region& r, const Map& m) {
  char code = m[p.x][p.y];
  int size = m.size();
  Point n;
  r.insert(p);
  // loop over cartesian neighbours
  for (auto dir : GRID2D_DIRS) {
    n = p+dir;
    // filter for map edges and same code
    if (n.x >=0 && n.y >=0 && n.y < size && n.x < size &&  m[n.x][n.y]==code && !(r.count(n)))
      // recurse on valid neighbour of same region
      grow_region(n,r,m);
  }
}

Regions solve(const Map& map_start, int DEBUG){
  Map map = map_start;
  Geometries g = {};
  int sol1= 0; 
  int sol2= 0; 
  int i = 0;
  int j = 0;
  int size = map.size();
  char c = '.';
  Regions regions;

  // define field in list of region
  // each region is a list of points
  for (i=0;i<size;i++) {
    for (j=0;j<size;j++) {
      if ((c=map[i][j])=='.') continue;
      Region r = {};
      Point p = {i,j};
      grow_region(p,r,map);
      // mark region as registered
      for (auto p:r) map[p.x][p.y]='.';
      regions.emplace_back(r);
    }
  }
  if (DEBUG) cout << map_start << endl;
  if (DEBUG) cout << map << endl;
  return regions;
}


void Day::parse(ifstream& file) {
  string line;
  this->map = {};
  this->regions = {};
  while (getline(file,line)) this->map.emplace_back(line);
}

string Day::part1() {
  // Copy-elision C++17
  this->regions = solve(this->map, this->log_level);
  size_t sol1=0;
  int perim=0;
  int area=0;
  Point n;

  for (auto r:this->regions) {
    area = 0;
    perim = 0;
    for (auto p:r) {
      area += 1;
      for (auto dir : GRID2D_DIRS) {
        n = p+dir;
        if (!r.count(n)) perim+=1;
      }
    }
    sol1 += (area * perim);
  }
  return to_string(sol1);
}

string Day::part2() {
  if (this->regions.empty())
    this->regions = solve(this->map, this->log_level);

  Point up = {-1,0};
  Point left = {0,-1};
  Point down = {1,0};
  Point right = {0,1};
  Point dr = {1,1};
  Point dl = {1,-1};
  Point ur = {-1,1};
  Point ul = {-1,-1};
  int sides = 0;
  int area=0;
  size_t sol2=0;

  for (auto r:this->regions) {
    area = 0;
    sides = 0;
    for (auto p:r) {
      area += 1;
      if (!r.count(p+up) && !r.count(p+left)) sides+=1;
      if (!r.count(p+up) && !r.count(p+right)) sides+=1;
      if (!r.count(p+down) && !r.count(p+left)) sides+=1;
      if (!r.count(p+down) && !r.count(p+right)) sides+=1;

      if (r.count(p+down) && r.count(p+right) && !r.count(p+dr)) sides+=1;
      if (r.count(p+down) && r.count(p+left) && !r.count(p+dl)) sides+=1;
      if (r.count(p+up) && r.count(p+right) && !r.count(p+ur)) sides+=1;
      if (r.count(p+up) && r.count(p+left) && !r.count(p+ul)) sides+=1;
    }
    sol2 += (area * sides);
  }
  return to_string(sol2);
}

}

