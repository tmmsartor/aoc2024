#ifndef GRAPHS_H
#define GRAPHS_H

#include "aoc.hpp"

struct Node {
  int v;
  vector<shared_ptr<Node>> childs;
  int parents;
};
typedef unordered_map<int,shared_ptr<Node>> Graph;

string toD3Json(Graph&);
string toDot(Graph&);

#endif
