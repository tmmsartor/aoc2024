#ifndef DAY24_H
#define DAY24_H

#include "aoc.hpp"
#include "print.hpp"

namespace day24 {

struct Op {
  string in1;
  string op;
  string in2;
  string out;
};

struct Node {
  string out;
  string op;
  Node* in1;
  Node* in2;
  vector<Node*> nexts;
  Node(string out, string op):out(out), op(op), in1(nullptr), in2(nullptr) {};
  Node(string out, string op, Node* in1, Node* in2):
    out(out), op(op), in1(in1), in2(in2) {};
};

typedef map<string,bool>  Mem;
typedef list<Op> Ops;
typedef map<string,Ops> Queue1;
typedef map<string,Node*> Graph;
typedef map<string,Op> RevMap;
typedef map<pair<string,string>,Ops> Queue2;

class Day : public aoc::DayAPI {
  Ops ops;
  RevMap out2in;
  Mem mem;
  bool is_test;
 public:
  constexpr int day() override { return 24; };
  void parse(ifstream&) override;
  string part1() override;
  string part2() override;
};

}

string to_string(const day24::Op& o);
ostream& operator<<(ostream& os, const day24::Op& o);
string to_string(const day24::Node* n);
ostream& operator<<(ostream& os, const day24::Node* n);

#endif
