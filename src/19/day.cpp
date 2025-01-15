#include "day.hpp"


namespace day19 {


void Day::parse(ifstream& file) {
  this->tm.clear();
  this->ts.clear();

  string line;
  bool first = true;
  while (getline(file, line)) {
    if (line.empty()) continue;
    if (first) {
      stringstream ss(line);
      int pos = 0;
      string sep = ", ";
      string towel;
      while ((pos = line.find(sep)) != string::npos) {
        towel = line.substr(0, pos);
        line.erase(0, pos + sep.length());
        this->tm.insert(towel);
      }
      this->tm.insert(line);
      first = false;
    }
    else this->ts.push_back(line);
  }
  if (this->log_level>1) for (auto t:tm) cout << t << ",";
  if (this->log_level>1) cout << endl;

}

string Day::part1() {
  int i = 0;
  int j = 0;
  int res1 = 0;
  long long res2 = 0;
  long long ways;
  int DEBUG = this->log_level;

  Count tc;
  for (auto t: this->ts) {
    ways = 0;
    // keep a set of subtowels two check
    set<string> q = {};
    q.insert(t);
    // count in how many way given subtowel can be reached
    tc = {{t,1}};
    if (DEBUG) cout << "on: "<< t << endl;
    //
    // --- Loop over work set
    //
    while (!q.empty()){
      // fetch longest element from the set of subtowels
      auto longest = max_element(q.begin(), q.end(),[](const string& a, const string& b) {
        return a.length() < b.length();
      });
      string p = *longest;
      q.erase(longest);
      if (DEBUG>1) cout << "on: "<< p << ",len:" << p.length() << ",queue:"<< q.size() << endl;
      //
      // --- Loop over possible steps
      //
      for (j=1; j <= p.size(); j++){
        // if match add to set
        string match = p.substr(0,j);
        // check if match_towel is available
        if (this->tm.count(match)) {
          if (DEBUG>1) cout << "on: "<< p << ",m:" << match << endl;
          // compute remaining towel
          string st = p.substr(j,p.size());
          //
          // -- current subtowel can be solved
          if (j==p.size()){
            ways += tc[p];
            if (DEBUG>1) cout << "end with:" << match << ",nr:" << ways << endl;
            if (DEBUG>1) cout << "on: "<< p << ",m:"<< match<< ",end" << endl;
          //
          // --add remaining subtowel to work set
          } else {
            if (DEBUG>1) cout << "on: "<< p << ",m:"<< match<< ",q+:" << st << endl;
            if (tc.count(st)) {
              tc[st] += tc[p];
              if (DEBUG>1) cout << "merge_on:" << st << ":from:" << p << ", " << tc[p] <<"->"<< tc[st] << endl;
            } else {
              q.insert(st);
              tc[st] = tc[p];
            }
            if (DEBUG>1) for (auto qi: q) cout << qi << ','; 
            if (DEBUG>1) cout << endl;
          }
        }
      }
    }
    if (DEBUG) cout << t << ": " << ways << endl;
    res2+=ways;
    if (ways) res1+=1;
  }
  this->sol = {to_string(res1), to_string(res2)};
  return this->sol.first;
}

string Day::part2() {
  return this->sol.second;
}

}

