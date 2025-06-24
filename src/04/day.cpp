#include "day.hpp"

namespace day04 {

void Day::parse(ifstream& file) {
  string line;
  Mat<char> lines;
  lines.clear();

  while (getline(file, line)) 
    lines.emplace_back(vector<char>(line.begin(), line.end()));

  this->grid.init(std::move(lines));

  if (this->log_level) cout << lines << endl;
}

ulong solve1(Grid& grid) {
  // store top-righ,bottom-left coordinated of matches to avoid double count
  int matches = 0;

  // check every 4x4 submatrix and store coordinates
  string world = "XMAS";
  string world_r(world.rbegin(), world.rend());
  string test1, test2;
  int s = world.size();
  vector<Point> diagonal1 = {{0,0},{1,1},{2,2},{3,3}};
  vector<Point> diagonal2 = {{0,3},{1,2},{2,1},{3,0}};
  vector<Point> horizontal = {{0,0},{0,1},{0,2},{0,3}};
  vector<Point> vertical   = {{0,0},{1,0},{2,0},{3,0}};

  // horizontal
  for (int i=0;i<grid.m; i++)
    for (int j=0;j<(grid.n-s+1); j++) {
      test1 = "";
      for (int k=0;k<s; k++)
        test1 += grid.at(Point(i,j)+horizontal[k]);
      if (test1 == world || test1==world_r) matches++;
    }

  // vertical
  for (int i=0;i<(grid.m-s+1); i++)
    for (int j=0;j<grid.n; j++) {
      test1 = "";
      for (int k=0;k<s; k++)
        test1 += grid.at(Point(i,j)+vertical[k]);
      if (test1 == world || test1==world_r) matches++;
    }

  // diagonal
  for (int i=0;i<(grid.m-s+1); i++)
    for (int j=0;j<(grid.n-s+1); j++) {
      test1 = "";
      test2 = "";
      for (int k=0; k<s; k++){
        test1 += grid.at(Point(i,j)+diagonal1[k]);
        test2 += grid.at(Point(i,j)+diagonal2[k]);
      }
      if (test1 == world || test1==world_r) matches++;
      if (test2 == world || test2==world_r) matches++;
    }

  return matches;
}

ulong solve2(Grid& grid) {
  int matches=0;
  vector<Point> corners = {{0,0},{0,2},{2,2},{2,0}};
  string world = "MMSS";
  string test1 = "";
  int s = world.size();

  // check corners of 3x3 submatrices
  for (int i=0;i<(grid.m-2); i++)
    for (int j=0;j<(grid.n-2); j++) {
      if (grid.at(Point(i,j)+Point(1,1)) != 'A') continue;
      test1 = "";
      for (int k=0;k<corners.size(); k++)
        test1 += grid.at(Point(i,j)+corners[k]);
      test1 += test1;
      for (int k=0;k<s; k++)
        if (!test1.compare(k,s,world)){
          matches++;
          break;
        }
    }

  return matches;
}

string Day::part1() {
  return to_string(solve1(this->grid));}

string Day::part2() {
  return to_string(solve2(this->grid));}

}
