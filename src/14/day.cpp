#include "day.hpp"


namespace day14 {

State parse_state(string& line){
  State s;
  size_t p_pos = line.find("p=");
  size_t v_pos = line.find(" v=");
  size_t c1 = line.find(",");
  size_t c2 = line.find(",",c1+1);

  int px = std::stoi(line.substr(p_pos+2,c1-(p_pos+2)));
  int py = std::stoi(line.substr(c1+1,v_pos-(c1+1)));
  int vx = std::stoi(line.substr(v_pos+3,c2-(v_pos+3)));
  int vy = std::stoi(line.substr(c2+1));

  s.p = {px,py};
  s.v = {vx,vy};

  return s;
}

void show(const Space& space, States& states){
  Space m2 = space;
  for (auto s:states) {
    m2[s.p.second][s.p.first]++;
  }
  for (auto row: m2){
    for (auto e: row) if (e) cout << 'X'; else cout << ' ';
    cout << endl;
  }
}

bool check_pattern(const Space& mat) {
  // serch for a line of robot 
  vector<int> m1(21,1);
  bool found=false;
  for (auto row: mat) {
    if (search(row.begin(), row.end(), m1.begin(), m1.end()) != row.end()){
      found=true;
      break;
    }
  }

  return found;
}


void Day::parse(ifstream& file) {
  string line;
  this->states = {};
  this->space = {};

  while (getline(file,line)){
    this->states.emplace_back(parse_state(line));
  }

  // detect test cases
  if (this->states.size() <30) {
    this->m = 7;
    this->n = 11;
    this->is_test=true;
  } else {
    this->m = 103;
    this->n = 101;
    this->is_test=false;
  }

  this->space = move(Space(this->m,vector<int>(this->n,0)));
}

string Day::part1() {
  int i,j;
  int ul=0;
  int ur=0;
  int dl=0;
  int dr=0;
  int steps = 100;
  Space m2;
  States states1 = this->states;
  for (int i=0;i<steps;i++){

    if (this->log_level>1) m2 = this->space;

    for (auto& s:states1) {
      s.p.first = (n+s.p.first+s.v.first)%n;
      s.p.second = (m+s.p.second+s.v.second)%m;
      if (this->log_level>1) m2[s.p.second][s.p.first]=1;
    }
  }

  for (auto s:states1) {
    //cout << s << endl;
    //mat[s.p.second][s.p.first]++;
    if (((s.p.second) < m/2) && ((s.p.first) < n/2)) ul++;
    if (((s.p.second) < m/2) && ((s.p.first) > n/2)) ur++;
    if (((s.p.second) > m/2) && ((s.p.first) < n/2)) dl++;
    if (((s.p.second) > m/2) && ((s.p.first) > n/2)) dr++;
  }

  if (this->log_level>1) {
    for (auto row: this->space){
      for (auto e: row){
        if (e) cout << e;
        else cout << '.';
      }
      cout << endl;
    }
  }

  size_t sol1 = ul * ur * dl * dr;
  return to_string(sol1);  
}

string Day::part2() {
  size_t sol2=0; 
  int i = 0;
  Space m2;
  States states2 = this->states;
  if (this->is_test) return to_string(sol2);
  while(!sol2){
    i++;
    m2 = this->space;
    for (auto& s:states2) {
      s.p.first = (n+s.p.first+s.v.first)%n;
      s.p.second = (m+s.p.second+s.v.second)%m;
      // TODO skip redrawing
      m2[s.p.second][s.p.first]=1;
    }
    //std::this_thread::sleep_for(std::chrono::milliseconds(300));
    if (check_pattern(m2)) sol2=i;

    if (this->log_level && sol2) show(this->space, states2);
    if (this->log_level>1) cout << "iteration: " << i << endl;
  }
  return to_string(sol2);
}

}

ostream& operator<<(std::ostream& os, const day14::State& s) {
  return os << "(" << s.p.first << "," << s.p.second << ")";
}
