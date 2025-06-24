#include "graphs.hpp"

string toD3Json(Graph& graph) {
    stringstream ss;
    ss << "{\n";
    ss << "  \"nodes\": [\n";
    vector<int> nodes = {};
    vector<pair<int,int>> edges = {};
    for (auto [v,n]: graph) {
      nodes.push_back(v);
      for (auto c: n->childs)
        edges.push_back(make_pair(v,c->v));
    }

    for (size_t i = 0; i < nodes.size(); ++i) {
        ss << "    {\"id\": \"" << nodes[i] << "\", \"name\": \"" << nodes[i] << "\"}";
        if (i < nodes.size() - 1) {
            ss << ",";
        }
        ss << "\n";
    }
    ss << "  ],\n"; // End of nodes array

    ss << "  \"links\": [\n";
    for (size_t i = 0; i < edges.size(); ++i) {
        ss << "    {\"source\": \"" << edges[i].first << "\", \"target\": \"" << edges[i].second << "\"}";
        if (i < edges.size() - 1) {
            ss << ",";
        }
        ss << "\n";
    }
    ss << "  ]\n"; // End of links array
    ss << "}\n";

    return ss.str();
}

string toDot(Graph& graph) {
    stringstream ss;
    ss << "digraph day05 {" << endl;
    for (auto [v,n]: graph)
      for (auto c: n->childs) 
        ss << v << " -> " << c->v << ";" << endl;
    ss << "}" << endl;

    return ss.str();
}

