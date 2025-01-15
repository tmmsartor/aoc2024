#include "grid2d.hpp"


// Point
ostream& operator<<(std::ostream& os, const Point& p) {
  return os << "(" << p.x << "," << p.y << ")";}

bool operator<(const Point& lhs, const Point& rhs){
  return lhs.x < rhs.x || (lhs.x == rhs.x && lhs.y < rhs.y);
}
Point operator+(const Point& lhs, const Point& rhs){
  return {lhs.x + rhs.x, lhs.y + rhs.y};
}
Point operator-(const Point& lhs, const Point& rhs){
  return {lhs.x - rhs.x, lhs.y - rhs.y};
}
Point operator-(const Point& p){
  return {-p.x, -p.y};
}
bool operator==(const Point& lhs, const Point& rhs){
  return (lhs.x == rhs.x)  && (lhs.y == rhs.y);
}
bool operator!=(const Point& lhs, const Point& rhs){
  return !(lhs==rhs);
}
