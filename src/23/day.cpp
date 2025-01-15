#include "day.hpp"


namespace day23 {

void recurse_network(string& node, Set& network, Graph& m2){
  if (network.contains(node)) return;
  bool is_connected = true;
  for (auto other: network) if (!m2[other].contains(node)) {is_connected = false; break;};
  if (is_connected){
    network.insert(node);
    for (auto neighbour: m2[node]) recurse_network(neighbour, network, m2);
  }
}

Set dept_first_search(Graph& graph, int DEBUG){
  string res = "";
  Set largest_network = {};
  for (auto [n,ns]: graph) {
    Set network = {};
    string node = n;
    recurse_network(node, network, graph);
    if (network.size() > largest_network.size())
      largest_network = network;
  }
  if (DEBUG) cout << "Size of largest clique: " << largest_network.size()  << endl;
  return largest_network;
}


void Day::parse(ifstream& file) {
  string l;
  int pos;
  this->links.clear();
  this->graph.clear();

  while (getline(file, l)) {
    pos = l.find('-');
    Link link = {l.substr(0, pos),l.substr(pos+1)};
    this->links.emplace_back(link);
  }
}

string Day::part1() {
  ulong sol1 = 0;
  Sets clusters3;

  for (auto link: links){
    if (link.first == link.second) continue;
    if (this->graph.count(link.first)) this->graph[link.first].insert(link.second);
    else this->graph[link.first] = {link.second};
    if (this->graph.count(link.second)) this->graph[link.second].insert(link.first);
    else this->graph[link.second] = {link.first};
  }

  if (this->log_level>1) for (auto p: this->graph) cout << p.first << ":" << p.second << endl;
  // Find all cluster of size 3
  for (auto [node,childs]: this->graph){
    for (auto child1: childs){
      if (this->graph.contains(child1)) for (auto child2: this->graph[child1]){
        if (this->graph.contains(child2)) for (auto child3: this->graph[child2]){
          if (child3 == node) clusters3.insert({node,child1,child2});
        }
      }
    }
  }

  if (this->log_level) cout << "Number of nodes: " << this->graph.size() << endl;
  if (this->log_level) cout << "Number of clique of size 3: " << clusters3.size() << endl;

  // count clique3 starting with t
  for (auto triple: clusters3){
    if (this->log_level>2) cout << triple << endl;
    bool has_t = false;
    for (auto code: triple) if (code[0] == 't') has_t=true;
    if (has_t) sol1++;
  }
  return to_string(sol1);
}

string Day::part2() {
  Set network = dept_first_search(this->graph, this->log_level);

  string sol2 = "";
  for (const auto& si : network) sol2 += si + (si != *network.rbegin() ? "," : "");

  return sol2;
}

}
