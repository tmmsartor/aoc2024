#ifndef PRINT_H
#define PRINT_H

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <bitset>
#include <unordered_map>
#include <unordered_set>


// Concept
//
using namespace std;
//
template<typename T>
concept Rangeable = requires(T container) {
    // Requires either member or ADL begin
    begin(container);
    // Requires either member or ADL end
    end(container);
    // Must have iterator type
    typename iterator_traits<typename T::iterator>;
};

template<typename T>
concept isString = requires(T container) {
  requires derived_from<T, string> ||
  derived_from<T, ostream> ||
  derived_from<T, bitset<T::_Nb>> ||
  derived_from<T, basic_ostream<char>> ||
  derived_from<T, basic_ostream<wchar_t>>;
};

// ostream
template<typename Container> requires(Rangeable<Container> && !isString<Container>)
ostream& operator<<(ostream& os, const Container& v){
  if (v.empty()) return os;
  auto it = v.begin();
  os << "(" << *(it++);
  for (; it != v.end();it++) os << "," << *it;
  os << ")";
  return os;
}

template<typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1,T2>& p) {
  os << "(" << p.first << ": " << p.second << ")";
  return os;
}

template<typename T1, typename T2>
ostream& operator<<(ostream& os, const map<T1, T2>& v) {
  for (auto it = v.begin(); it != v.end();it++) os << it->first << ":" << it->second;
  return os;
}

template<typename T>
ostream& operator<<(ostream& os, const vector<vector<T>>& v) {
  for (auto vi:v) os << vi << endl;
  return os;
}

ostream& operator<<(ostream& os, const vector<char>& v);


#endif
