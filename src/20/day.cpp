#include "day.hpp"


namespace day20 {

int min_path(const Maze& m, CostToGo& dp, Run& r, const Point& s, const Point& e, int DEBUG) {
  int size = m.size();

  Point n;
  dp[e.x][e.y] = 0;
  queue<Point> q;
  q.push(e);

  int len = INT_MAX;
  r.emplace_back(e);

  while (!q.empty()) {
    auto p = q.front();
    q.pop();
    for (auto dir: GRID2D_DIRS) {
      n = p+dir;
      if (n.x < 0 || n.x >= size || n.y < 0 || n.y >= size) continue;
      if ((m[n.x][n.y]=='.' || m[n.x][n.y]=='S') && (dp[n.x][n.y] > dp[p.x][p.y] + 1)) {
        dp[n.x][n.y] = dp[p.x][p.y] + 1;
        q.push(n);
        r.emplace_back(n);
        if (DEBUG>1) cout << n << ": " << dp[n.x][n.y] << endl;
      }
    }
  }
  for (auto dir: GRID2D_DIRS) {
    n = s+dir;
    if (n.x < 0 || n.x >= size || n.y < 0 || n.y >= size || m[n.x][n.y]=='#') continue;
    len = min(len,dp[n.x][n.y]);
  }
  len++;
  if (len > size*size) len=0;

  return len;
}

int count_speedups(Maze& m, Run& r, CostToGo& dp, int speedup, int cheatsn, int DEBUG) {
  int sol=0;
  int s,t,l,d;
  Point ce,dist;
  // loop over possible cheat starting points
  for (auto cs:r) {
    s = dp[cs.x][cs.y];
    // loop over possible target re-entry points
    for (t=s+speedup+2; t<r.size(); t++){
      ce = r[t];
      dist = ce-cs;
      d = abs(dist.x)+abs(dist.y);
      if (d > cheatsn) continue;
      if ((t-s-d)>=speedup){
        if (DEBUG>1) cout << s << "->" << t << ",l:" << (t-s-d) << endl;
        sol++;
      }
    }
  }
  return sol;
}

void show(CostToGo& dp){
  int size = dp.size();
  for (auto row: dp){
    for (auto ni: row)
       if (ni < size*size) {cout << setw(2) << setfill('0') << ni << ".";}
       else {cout << "...";}
    cout <<endl;
  }
}

void Day::parse(ifstream& file) {
  this->maze = {};
  string line;
  int i = 0;
  int j = 0;
  this->run = {};
  this->start = GRID2D_ZERO;
  this->start = GRID2D_ZERO;
  while (getline(file,line)) {
    // find start and end
    for (j=0;j<line.length();j++){
      if (line[j] == 'S') this->start={i,j};
      if (line[j] == 'E') this->end={i,j};
    }
    this->maze.emplace_back(line);
    i++;
  }
  size_t size = this->maze.size();
  if (size < 20){
    this->is_test = true;
    this->min_speedup = MIN_SPEEDUP_TEST;
  } else {
    this->is_test = false;
    this->min_speedup = MIN_SPEEDUP;
  }
  this->grid_cost = CostToGo(size, vector<int>(size, INT_MAX));
  this->grid_size = size;
}

string Day::part1() {
  int nsteps_best;
  int cheats = 2;

  nsteps_best = min_path(this->maze, this->grid_cost, this->run,
                         this->start, this->end, this->log_level);

  if (this->log_level) cout << nsteps_best << endl;
  if (this->log_level) show(this->grid_cost);

  int sol1 = count_speedups(this->maze, this->run, this->grid_cost,
                            this->min_speedup, cheats, this->log_level);
  return to_string(sol1);
}

string Day::part2() {
  int cheats = 20;
  int sol2 = count_speedups(this->maze, this->run, this->grid_cost,
                            this->min_speedup, cheats, this->log_level);
  return to_string(sol2);
}

}
