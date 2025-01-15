#include "print.hpp"

// Non templates


ostream& operator<<(ostream& os, const vector<char>& v) {
  os.write(v.data(), v.size());
  return os;
}
