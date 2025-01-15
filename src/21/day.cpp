#include "day.hpp"


namespace day21 {

Codes get_all_paths(Point& s, Point& t, const Pad& pad){

  Point m = t-s;
  // vector of steps
  vector<Point> ds = {};
  if (m.y > 0) {
    vector<Point> ns(abs(m.y),{0,1});
    ds.insert(ds.end(), ns.begin(), ns.end());}
  if (m.x > 0) {
    vector<Point> ns(abs(m.x),{1,0});
    ds.insert(ds.end(), ns.begin(), ns.end());}
  if (m.y < 0) {
    vector<Point> ns(abs(m.y),{0,-1});
    ds.insert(ds.end(), ns.begin(), ns.end());}
  if (m.x < 0) {
    vector<Point> ns(abs(m.x),{-1,0});
    ds.insert(ds.end(), ns.begin(), ns.end());}

  sort(ds.begin(), ds.end());
  //for (auto d: ds) cout << d;
  //cout << endl;
  Codes cmds = {};
  bool good;
  string cmd;
  Point n;
  // check all permutations of path from two key
  do {
    good = true;
    cmd = "";
    n = s;
    for (auto d: ds){
      n = n+d;
      if (pad.at('X')==n) good = false;
      char c= GRID2D_DIRS_MAP.at(d);
      cmd += c;
    }
    if (good) {
      cmd += "A";
      cmds.emplace_back(cmd);
    }
  } while (next_permutation(ds.begin(), ds.end()));

  return cmds;
}

ulong fix_min_length(const string& seq, int depth, int max_depth, map<pair<string,int>,ulong>& cache){

  if (depth==max_depth) return seq.length();

  // check if pair seq,depth is already in cache cache
  const auto iter = cache.find({seq, depth});
  if (iter != cache.end()) return iter->second;

  ulong total_min_length = 0;
  ulong length_i,min_length;
  // sequences in next indirection level
  Codes seqsn;
  Point s,t;

  s = DIRPAD.at('A');
  for (char c: seq) {
    t = DIRPAD.at(c);
    // compute vector of all possible path between s and t in a directs pad
    seqsn = get_all_paths(s,t,DIRPAD);
    s = t;

    // find minium length after going through all level of indirection
    min_length = numeric_limits<ulong>::max();

    for (const auto& seqn: seqsn) {
      length_i = fix_min_length(seqn, depth + 1, max_depth, cache);
      //cache[{seqn, depth}] = length_i;
      min_length = min(min_length, length_i);
    }

    total_min_length += min_length;
  }

  cache[{seq, depth}] = total_min_length;

  return total_min_length;
}

void print(Codes& v){
  // print codes
  for (auto e:v) cout << e << endl;
  cout << v.size() << endl;
}

void Day::parse(ifstream& file) {
  string line;
  this->codes.clear();
  while (getline(file, line)) this->codes.emplace_back(line);
}

string Day::part1() {
  // Parsing
  int sol1 = 0;
  ulong sol2 = 0;
  int n;
  ulong min_l1, li1, l1;
  ulong min_l2, li2, l2;
  map<pair<string, int>, ulong> cache1, cache2;
  string min_path, min_path_i;
  // DirectionalCode vector
  Codes dircodes;
  // Keypad Point start, target, current
  Point s,t,c;

  // loop over codes to compute
  for (auto code: this->codes) {
    if (this->log_level) cout << code << endl;

    min_path = "";
    l1 = 0;
    l2 = 0;
    s = NUMPAD.at('A');
    // loop over single entry of numeric pad sequences
    for (auto c:code) {
      t = NUMPAD.at(c);
      dircodes = get_all_paths(s,t, NUMPAD);
      s = t;

      min_l1 = numeric_limits<ulong>::max();
      min_l2 = numeric_limits<ulong>::max();
      // loop over possible sequences from s to t
      // and find which have shortest sequence at the end of indirection stack
      for (const auto& path: dircodes)
      {
        li1 = fix_min_length(path, 0, 2, cache1);
        li2 = fix_min_length(path, 0, 25, cache2);
        if (li2 < min_l2) min_l2 = li2;
        if (li1 < min_l1) {
          min_l1 = li1;
          if (this->log_level) min_path_i = path;
        }
      }
      if (this->log_level) min_path += min_path_i;
      l1 += min_l1;
      l2 += min_l2;
    }

    n = stoi(code.substr(0,code.size()-1));
    if (this->log_level) cout << min_path <<": "<< l1 << "," << n << endl;
    sol1 += l1 * n;
    sol2 += l2 * n;
  }
  this->sol = {to_string(sol1),to_string(sol2)};
  return this->sol.first;
}

string Day::part2() {
  return this->sol.second;
}

}

