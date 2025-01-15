#include "day.hpp"


namespace day15 {

int DEBUG=0;

map<char,Point> DIRS = {
  {'^',{-1,0}},
  {'>',{0,1}},
  {'v',{1,0}},
  {'<',{0,-1}}
};

bool is_valid(const Point& p, const State& mat){
  if ( p.x >= 0 && p.y >= 0 && 
       p.x < mat.size() && p.y < mat[0].size()
  ) return true;
  else return false;
}

char get_cell(Point& p, const State& mat){
  if (!is_valid(p,mat)) return '#';
  return mat[p.x][p.y];
}

Item get_item(Point& p, const State& mat){
  Item i = {p,p,"#",0};
  if (!is_valid(p,mat)) return i;
  // default '.'
  char c = mat[p.x][p.y];
  i.t = c;
  if (c==']') { 
    i.s = p + DIRS['<'];
    i.t = "[]";
  }
  if (c=='[') {
    i.e = p + DIRS['>'];
    i.t = "[]";
  }
  return i;
}

Point move_obj(Point& pos, char obj, char cmd, State& mat){
  // pos_n position
  Point pos_n = pos+DIRS[cmd];
  Point fish_n;
  if (!is_valid(pos_n,mat)) return pos;
  if (DEBUG>1) cout << obj << ","<<  cmd << endl;

  char obj_n = get_cell(pos_n, mat);
  if (obj_n=='#') return pos;
  // move fish
  if (obj_n=='O') {
    fish_n = move_obj(pos_n, obj_n, cmd, mat);
    obj_n = get_cell(pos_n, mat);
  }

  // look again next to first
  if (obj_n=='.') {
    mat[pos.x][pos.y] = obj_n;
    mat[pos_n.x][pos_n.y] = obj;
  } else {
    pos_n = pos;
  }
  return pos_n;
}

Items next_items(Item obj, char cmd, State& state){
  if (DEBUG>1) cout << "get items: " << obj << ","<<  cmd << endl;

  vector<Item> objs_n = {};
  // if wall nothing happen

  Point pos_n;
  if (obj.t[0]=='#') {}
  else if (obj.t[0]=='.') {}
  else if (obj.t=="@") {
    pos_n = obj.s+DIRS[cmd];
    objs_n.emplace_back(get_item(pos_n, state));
  } else if (obj.t=="[]" && (cmd=='>')) {
    pos_n = obj.e+DIRS[cmd];
    objs_n.emplace_back(get_item(pos_n, state));

  } else if (obj.t=="[]" && (cmd=='<')) {
    pos_n = obj.s+DIRS[cmd];
    objs_n.emplace_back(get_item(pos_n, state));

  } else if (obj.t=="[]" && (cmd=='^' || cmd=='v')) {
    pos_n = obj.s+DIRS[cmd];
    Item i1 = get_item(pos_n, state);
    objs_n.emplace_back(i1);
    pos_n = obj.e+DIRS[cmd];
    Item i2 = get_item(pos_n, state);
    if (i1.t[0]=='.' && i2.t[0]=='.') {
      objs_n[0].t="..";
      objs_n[0].e=objs_n[0].s+DIRS['>'];
    } else if (i1.s != i2.s) objs_n.emplace_back(i2);
  }
  if (DEBUG>1) cout << "got items: ";
  if (DEBUG>1) for (auto o: objs_n) cout << o; 
  if (DEBUG>1) cout << endl;
  return objs_n;
}

void collect_movable(Item obj, char cmd, State& state, Items& to_move, bool& movable, int depth){
  // pos_n position
  Items objs_n = next_items(obj, cmd, state);

  Items objs_nn = objs_n;

  // wall
  //for (auto obj_n: objs_n)
    //if (obj_n.t[0]=='#') return force;

  // movable
  // recurse until list of neighbours is empty
  for (auto obj_n: objs_n){
    if (!movable) return;
    if (obj_n.t[0]=='#') movable = false;
    else if (obj_n.t=="[]") {
      obj_n.depth = depth;
      to_move.emplace_back(obj_n);
      collect_movable(obj_n, cmd, state,to_move,movable, depth+1);
    }
  }
}

void move_box(Item obj, char cmd, State& state){
  if (DEBUG>1) cout << "Updatin env: " << obj << cmd << endl;
  Point d = DIRS[cmd];
  Item obj_n = {obj.s+d, obj.e+d, "..", 0};
  
  if (cmd=='>') {
    state[obj.s.x][obj.s.y] = obj_n.t[0];
    state[obj_n.s.x][obj_n.s.y] = obj.t[0];
    state[obj_n.e.x][obj_n.e.y] = obj.t[1];

  } else if (cmd=='<') {
    state[obj_n.s.x][obj_n.s.y] = obj.t[0];
    state[obj.s.x][obj.s.y] = obj.t[1];
    state[obj.e.x][obj.e.y] = obj_n.t[0];

  } else {
    state[obj.s.x][obj.s.y] = obj_n.t[0];
    state[obj.e.x][obj.e.y] = obj_n.t[1];
    state[obj_n.s.x][obj_n.s.y] = obj.t[0];
    state[obj_n.e.x][obj_n.e.y] = obj.t[1];
  }
  // update env state and robot
  //
  //if (obj_n.t=="..") {
    //state[obj.s.x][obj.s.y] = obj_n.t[0];
    //state[obj.e.x][obj.e.y] = obj_n.t[1];
    //state[obj_n.s.x][obj_n.s.y] = obj.t[0];
    //state[obj_n.e.x][obj_n.e.y] = obj.t[1];

  //} else if (obj.t=="@") {
    //// obj: "@" next: '.'
    //// update env
    //state[obj.s.x][obj.s.y] = obj_n.t[0];
    //state[obj_n.s.x][obj_n.s.y] = obj.t[0];
    //// update obj
    //obj.s =  obj.s + DIRS[cmd];

  //} else if (cmd=='>' ) {
    //// obj: "[]" next: '.'
    //state[obj.s.x][obj.s.y] = obj.t[0];
    //state[obj.e.x][obj.e.y] = obj_n.t[0];
    //state[obj_n.s.x][obj_n.s.y] = obj_n.t[1];

  //} else if (cmd=='<' ) {
    //// obj: "[]" next: '.'
    //state[obj_n.s.x][obj_n.s.y] = obj.t[0];
    //state[obj.s.x][obj.s.y] = obj.t[1];
    //state[obj.e.x][obj.e.y] = obj_n.t[0];

  //}
}


void Day::parse(ifstream& file) {
  // reset state
  this->state = {};
  this->rob = {0,0};
  this->input_seq = "";

  string line;
  int i,j;

  getline(file, line);
  int N = line.length()-2;

  // Parse initial state
  i = 0;
  while (getline(file, line)){
    line = line.substr(1,N);
    if (line==string(N,'#')) break;
    for (j=0;j<N;j++)
      if (line[j]=='@')
        this->rob = {i,j};
    i++;
    this->state.emplace_back(line);
  }
  int M = this->state.size();
  // get empty line
  getline(file, line);
  // Parse input commands sequence
  while (getline(file, line))
    this->input_seq+=line;

  if (this->log_level) cout << "start:" << endl << this->state << endl;
}

string Day::part1() {
  ulong sol1 = 0;
  int i,j;

  State map1 = this->state;
  Point rob1 = this->rob;

  for (auto c: this->input_seq) {
    if (this->log_level>1) cout << c << endl;
    rob1 = move_obj(rob1,'@',c,map1);
    if (this->log_level>1) cout << map1 << endl;
  }

  // end state
  if (this->log_level>1) cout << "end:" << endl << map1;

  // sum gps
  for (i=0;i<map1.size();i++)
    for (j=0;j<map1.size();j++) 
      if (map1[i][j] == 'O')  sol1+= 100*(i+1)+(j+1);

  return to_string(sol1);
}

string Day::part2() {
  ulong sol2 = 0;
  State map2 = {}; 
  Point rob2 = this->rob;
  int nb=0;
  int i,j;
  string line;

  // Transform map
  for (auto l: this->state) {
    line = "";
    for (auto c: l){
      if (c=='.') line+="..";
      else if (c=='@') line+="@.";
      else if (c=='#') line+="##";
      else if (c=='O') {
        line+="[]";
        nb++;
      } 
    }
    map2.emplace_back(line);
  }

  if (this->log_level>1) cout << "part2" << endl << map2 << endl;

  rob2.y *= 2;
  bool movable;
  Items to_move = {};
  Item r = {rob2,rob2,"@", 0};
  for (auto c: this->input_seq) {
    to_move.clear();
    movable = true;
    if (this->log_level>1) cout << c << endl;
    collect_movable(r,c,map2,to_move,movable, 0);
    if (!movable) continue;
    // reverse move boxes
    sort(to_move.begin(),to_move.end(),compareByDepth);
    for (auto it=to_move.rbegin(); it!=to_move.rend();it++){
      if (this->log_level>1) cout << "Moving: " << *it << endl;
      move_box(*it,c,map2);
    }
    
    // move robot
    map2[r.s.x][r.s.y] = '.';
    r.s = r.s+DIRS[c];
    r.e = r.s;
    map2[r.s.x][r.s.y] = '@';
    if (this->log_level) cout << c << endl << map2;
  }

  if (this->log_level) cout << "end" << endl << map2 << endl;

  // sum gps
  int no = 0;
  int nc = 0;
  for (i=0;i<map2.size();i++)
    for (j=0;j<map2[0].size();j++){
      if (map2[i][j] == '[') {
        sol2 += 100*(i+1)+(j+2);
        no++;
      }
      if (map2[i][j] == ']') nc++;
    }

  // Number of boxes consistency
  assert(nb==no && "Number of boxes not constant!");
  assert(no==nc && "Broken Boxes!");
  return to_string(sol2);
}

}

bool compareByDepth(const day15::Item& a, const day15::Item& b) {
    return a.depth < b.depth;
}
