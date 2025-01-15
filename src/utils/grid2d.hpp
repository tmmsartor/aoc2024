#ifndef GRID2D_H
#define GRID2D_H


#include <vector>
#include <map>
#include <set>
#include <queue>
#include <unordered_map>
#include <unordered_set>

#include "aoc.hpp"

// Namespaces
//
using namespace std;


//inline constexpr size_t ULONG_MAX = numeric_limits<size_t>::max();

// Point
//
struct Point {
  int x;
  int y;
};

ostream& operator<<(std::ostream& os, const Point& p);
bool operator<(const Point& lhs, const Point& rhs);
Point operator+(const Point& lhs, const Point& rhs);
Point operator-(const Point& lhs, const Point& rhs);
Point operator-(const Point& p);
bool operator==(const Point& lhs, const Point& rhs);
bool operator!=(const Point& lhs, const Point& rhs);

typedef vector<Point> Points;
static const Points GRID2D_DIRS = {{-1,0}, {1,0}, {0,-1}, {0,1}};
static const Point GRID2D_ZERO = {0,0};
static const map<Point,char> GRID2D_DIRS_MAP = {
  {{-1,0},'^'},
  {{0,1},'>'},
  {{1,0},'v'},
  {{0,-1},'<'}
};


// Grid2d
//
template<typename T>
using Mat = vector<vector<T>>;

template<typename T>
struct Grid2D {
  Mat<T> _data;
  int m,n;

  Grid2D();
  Grid2D(size_t r, size_t c, T default_value = T());
  Grid2D(const Mat<T>&& mat);
  void init(const Mat<T>&& mat);
  void init(size_t, size_t, T default_value = T());
  bool is_valid(const Point& p) const;
  T at(const Point& p) const;
  void set(const Point& p, const T& v);
  void set(const Point& p, const pair<Point,int>& v);
  void clear();
};


// default construct has removed because of move constructor
template<typename T>
Grid2D<T>::Grid2D(): m(), n(), _data() {}

template<typename T>
Grid2D<T>::Grid2D(size_t r, size_t c, T default_value) :
  m(r), 
  n(c),
  _data(r, vector<T>(c, default_value)) {}

template<typename T>
Grid2D<T>::Grid2D(const Mat<T>&& mat) {
  this->init(mat);
}

template<typename T>
void Grid2D<T>::init(const Mat<T>&& mat) {
  _data = mat;
  m = _data.size();
  if (m) n = _data[0].size();
  else n = 0;
}

template<typename T>
void Grid2D<T>::init(size_t m, size_t n, T default_value) {
  _data = Mat<T>(m, vector<T>(n, default_value));
  this->m = m;
  this->n = n;
}

template<typename T>
bool Grid2D<T>::is_valid(const Point& p) const {
  if (p.x>=0 && p.y>=0 && p.x<m && p.y<n ) return true;
  else return false;
}

template<typename T>
T Grid2D<T>::at(const Point& p) const {
  if (!is_valid(p)) return T();
  return _data[p.x][p.y];
}

template<typename T>
void Grid2D<T>::set(const Point& p, const T& v){
  if (!is_valid(p)) {
    //cout << p << " not valid" << endl;
    return;
  }
  _data[p.x][p.y] = v;
}

template<typename T>
void Grid2D<T>::set(const Point& p, const pair<Point,int>& v){
  if (!is_valid(p)) {
    cout << p << " not valid" << endl;
    return;
  }
  _data[p.x][p.y][v.first]= v.second;
}

template<typename T>
ostream& operator<<(ostream& os, const Grid2D<T>& g) {
  return os << g._data;
}

template<typename T>
void Grid2D<T>::clear() {
  _data.clear();
  this->m = 0;
  this->n = 0;
}

#endif
