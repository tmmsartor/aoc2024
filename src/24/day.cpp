#include "day.hpp"

string to_string(const day24::Op& o) {
  return format("{} {} {} -> {}",o.in1,o.op,o.in2,o.out);
}
ostream& operator<<(ostream& os, const day24::Op& o) {
  return os << "(" << to_string(o) << ")";
}
string to_string(const day24::Node* n) {
  string out = "";
  if (!n->in1 || !n->in2) out = format("{} -> {}",n->op,n->out);
  out = format("{} {} {} -> {}",n->in1->out,n->op,n->in2->out,n->out);
  return out;
}
ostream& operator<<(ostream& os, const day24::Node* n) {
  return os << "(" << to_string(n) << ") ";
}


namespace day24 {

//ostream& operator<<(ostream& os, const vector<Node*>& v) {
  //auto it = v.begin();
  //os << "(";
  //for (; it != v.end()-1;it++) os << to_string(*it) << ", ";
  //os << to_string(*it) << ")";
  //return os;
//}

Node* add_node(string out, Graph& graph, RevMap& ops) {
  // Add point based node
  // return node if exist
  if (graph.contains(out))
    return graph[out];

  Op o = ops[out];

  // create node for dependencies
  Node* in1;
  Node* in2;
  if (o.in1[0]=='x' || o.in1[0]=='y')
    in1 = new Node(o.in1,"IN");
  else in1 = add_node(o.in1, graph, ops);
  graph[o.in1] = in1;

  if (o.in2[0]=='x' || o.in2[0]=='y')
    in2 = new Node(o.in2,"IN");
  else in2 = add_node(o.in2, graph, ops);
  graph[o.in2] = in2;

  // create current node
  Node* node = new Node(out,o.op, in1, in2);
  in1->nexts.emplace_back(node);
  in2->nexts.emplace_back(node);
  graph[out] = node;
  return node;
}

bool both_inputs(const Node* n){
  if ((n->in1->out[0]=='x' && n->in2->out[0]=='y') ||
      (n->in1->out[0]=='y' && n->in2->out[0]=='x')) return true;
  return false;
}

bool check_node(Node* n, int DEBUG) {
  if (!n->in1 || !n->in2) return true;
  if (n->op=="XOR") {
    // XOR1 first digit
    if (n->out=="z00" && n->in1->out=="y00" && n->in2->out=="x00") return true;
    if (n->out=="z00" && n->in2->out=="y00" && n->in1->out=="x00") return true;
    // XOR1
    if (n->out[0]=='z') return true;

    // XOR2
    if (n->nexts.size()==2 &&
        set<string>({n->nexts[0]->op,n->nexts[1]->op}) == set<string>({"XOR","AND"}) &&
        both_inputs(n)) return true;

  } else if (n->op=="OR") {
    // most significant digit
    if (n->out=="z45") return true;
    // all others
    if (n->nexts.size()==2 &&
        set<string>({n->nexts[0]->op,n->nexts[1]->op}) == set<string>({"XOR","AND"})
        ) return true;

  } else if (n->op=="AND") {
    // least digit 0
    if ((n->in1->out=="y00" && n->in2->out=="x00") ||
       (n->in2->out=="y00" && n->in1->out=="x00"))
      if (n->nexts.size()==2 &&
          set<string>({n->nexts[0]->op,n->nexts[1]->op}) == set<string>({"XOR","AND"})
         ) return true;
    // all other cases
    if (n->nexts.size()==1 && n->nexts[0]->op=="OR") return true;
  }
  if (DEBUG) cout << "missmatch: " << n << " ";
  if (DEBUG) if ((n->nexts).size()>0) cout << n->nexts[0] << " ";
  if (DEBUG) if ((n->nexts).size()>1) cout << n->nexts[1] << " ";
  if (DEBUG) cout << endl;
  return false;
}

void execute_next(Op& o, Mem& mem, Queue1& q1, Queue2& q2) {
  if (mem.contains(o.in1) && mem.contains(o.in2)) {
    // compute current operation
    bool& o1 = mem[o.out];
    bool i1 = mem[o.in1];
    bool i2 = mem[o.in2];
    if      (o.op=="AND") o1 = i1 && i2;
    else if (o.op=="OR")  o1 = i1 || i2;
    else if (o.op=="XOR") o1 = i1 ^ i2;

    // move element from miss2_list to miss1_list
    Op on;
    for (auto& [k, l]: q2) {
      //Ops vt = v;
      if (k.first == o.out)  {
        if (!q1.contains(k.second)) q1[k.second] = {};
        for (auto it = l.begin(); it != l.end();) {
          on = *it;
          it = l.erase(it);
          q1[k.second].emplace_back(on);
        }
      }
      else if (k.second == o.out)  {
        if (!q1.contains(k.first)) q1[k.first] = {};
        for (auto it = l.begin(); it != l.end();) {
          on = *it;
          it = l.erase(it);
          q1[k.first].emplace_back(on);
        }
      }
    }
    // execute all miss1_list element depending on o.out
    if (!q1.contains(o.out)) return;
    Ops& l = q1[o.out];
    for (auto it = l.begin(); it != l.end();) {
      on = *it;
      it = l.erase(it);
      execute_next(on, mem, q1, q2);
    }
  }
  else if (!mem.contains(o.in1) && !mem.contains(o.in2)) {
    if (!q2.contains({o.in1,o.in2})) q2[{o.in1,o.in2}] = {};
    q2[{o.in1,o.in2}].emplace_back(o);
  } else if (!mem.contains(o.in1) && mem.contains(o.in2)) {
    if (!q1.contains(o.in1)) q1[o.in1] = {};
    q1[o.in1].emplace_back(o);
  } else if (mem.contains(o.in1) && !mem.contains(o.in2)) {
    if (!q1.contains(o.in2)) q1[o.in2] = {};
    q1[o.in2].emplace_back(o);
  }
}


void Day::parse(ifstream& file) {

  string line,gate,var1,var2,var3;
  Op op;

  this->mem.clear();
  this->out2in.clear();
  this->ops.clear();

  while (getline(file, line)) {
    if (line.empty()) break;
    var1 = line.substr(0,3);
    this->mem[var1] = stoi(line.substr(5));
  }

  while (getline(file, line)) {
    if (line.empty()) continue;
    var1 = line.substr(0,3);
    int pos  = line.find(' ',4);
    gate = line.substr(4,pos-4);
    var2 = line.substr(pos+1,3);
    var3 = line.substr(pos+8,3);
    Op op = {var1,gate,var2,var3};
    this->ops.emplace_back(op);
    this->out2in[var3] = op;
  }

  if (this->mem.size() < 15)
    this->is_test = true;
  else
    this->is_test = false;

  if ( this->log_level > 1 ) for (auto o: ops) cout << o << endl;
}

string Day::part1() {

  Queue1 q1;
  Queue2 q2;
  ulong sol1 = 0;
  for (auto o: ops) execute_next(o,this->mem,q1,q2);

  // write output on bitset
  std::bitset<64> sol1_bits;
  for (auto [k,v]: this->mem)
    if (k[0] == 'z' && v) sol1_bits.set(stoi(k.substr(1)));

  if (this->log_level) cout << "Number of register: " << this->mem.size() << endl;
  if (this->log_level) cout << sol1_bits << endl;

  sol1 = sol1_bits.to_ulong();

  return to_string(sol1);
}

string Day::part2() {

  if (this->is_test) return "0";

  stringstream sol2;
  Graph graph = {};
  string outi;
  set<string> outputs = {};
  vector<string> inputs = {};
  set<string> swaps = {};

  for (int i=0; i<46; i++)
    if (this->out2in.contains((outi = format("z{:02}",i)))) outputs.insert(outi);

  // Build pointer graph
  for (auto outi: outputs)
    add_node(outi, graph, this->out2in);

  for (auto [out, node]: graph)
    if (!check_node(node,this->log_level))
      swaps.insert(out);

  if (this->log_level > 1) {for (auto [out, node]: graph)
    if (outputs.contains(out)) {continue;}
    else {cout << node->op << ": " << node->nexts << endl;}}

  sol2 << *swaps.begin();
  for_each(next(swaps.begin()), swaps.end(), [&sol2](const string& el) {sol2 << "," << el;});

  for (auto [out, node]: graph)  delete node;

  return sol2.str();
}

}
