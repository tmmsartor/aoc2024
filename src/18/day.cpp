#include "day.hpp"


namespace day18{

int min_path(const vector<Point>& coords, const int size, const int DEBUG) {

  Point n;
  vector<vector<bool>> grid(size, vector<bool>(size, true));
  for (auto p: coords) grid[p.y][p.x] = false;

  Mat<int> dp(size, vector<int>(size, INT_MAX));
  
  dp[0][0] = 0;
  queue<Point> q;
  q.push({0,0});

  while (!q.empty()) {
    auto p = q.front();
    q.pop();
    for (auto dir : GRID2D_DIRS) {
      n = p+dir;
      if (n.x >= 0 && n.x < size && n.y >= 0 && n.y < size &&
        grid[n.x][n.y] && dp[n.x][n.y] > dp[p.x][p.y] + 1) {
        dp[n.x][n.y] = dp[p.x][p.y] + 1;
        q.push({n.x,n.y});
        if (DEBUG) cout << n.x << "," << n.y << ":" << dp[n.x][n.y] << endl;
      }
    }
  }
  return dp[size-1][size-1];
}

Point parse_numbers(const string& line) {
  Point p;
  size_t comma = line.find(',');
  p.x = std::stoi(line.substr(0, comma));
  p.y = std::stoi(line.substr(comma + 1));
  return p;
}

void show(const Mat<int>& dp) {
  int size = dp.size();
  for (auto& row:dp) {
    for (auto n:row) {
      if (n > size*size) n = 0;
      cout << setw(2) << setfill('0') << n << " ";
    }
    cout << endl;
  }
}

void Day::parse(ifstream& file) {
  this->coords.clear();
  this->lines.clear();
  this->sol = {"",""};

  string line;
  while (getline(file, line))
    this->lines.emplace_back(line);

  // detect test
  if (this->lines.size() < NBYTES){
    this->is_test = true;
    this->n_bytes = NBYTES_TEST;
    this->grid_size = GRID_SIZE_TEST;
  } else {
    this->is_test = false;
    this->n_bytes = NBYTES;
    this->grid_size = GRID_SIZE;
  }
}

string Day::part1() {

  for (int i=0; i<this->n_bytes;i++)
    this->coords.emplace_back(parse_numbers(this->lines[i]));

  int min_steps = min_path(this->coords, this->grid_size, this->log_level);
  this->sol.first = to_string(min_steps);

  if (this->log_level) cout << min_steps << "," << this->coords.size() << endl;

  return this->sol.first;
}

string Day::part2() {
  Point p;
  int min_steps;
  auto it = this->lines.begin()+this->n_bytes;
  for (; it!=lines.end();it++) {
    p = parse_numbers(*it);
    this->coords.emplace_back(p);
    min_steps = min_path(this->coords, this->grid_size, this->log_level);
    if (min_steps > pow(this->grid_size,2)) {
      this->sol.second = format("{},{}",p.x,p.y);
      break;
    }
  }
  return this->sol.second;
}

}

