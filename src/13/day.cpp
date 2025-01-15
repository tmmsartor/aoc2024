#include "day.hpp"


namespace day13{

Button parse_button(string& str){
  size_t x_pos = str.find("X");
  size_t y_pos = str.find("Y");
  size_t comma = str.find(",");

  int x = std::stol(str.substr(x_pos + 2, comma - (x_pos + 2)));
  int y = std::stol(str.substr(y_pos + 2));

  return {x,y};
}

void Day::parse(ifstream& file) {
  this->games = {};
  string line;
  while (true){
    getline(file,line);
    Button v1 = parse_button(line);
    getline(file,line);
    Button v2 = parse_button(line);
    getline(file,line);
    Button v3 = parse_button(line);
    Game g = {v1,v2,v3};
    this->games.emplace_back(g);
    if(!std::getline(file, line)) break;
  }
}

string Day::part1() {
  size_t sol1=0;
  long an,bn,num,den;

  for (auto g:games){
    // part1
    // compute linear equations numerator and denumerator
    num = (g.p.second* g.a.first) - (g.p.first*g.a.second);
    den = (g.b.second* g.a.first) - (g.b.first*g.a.second);
    // check if solution is integer
    if (!(num % den)) {
      bn = (num/den);
      an = (g.p.first - bn*g.b.first)/g.a.first;
      sol1+=(an*3)+bn;
    }
  }
  return to_string(sol1);
}

string Day::part2() {
  size_t sol2=0;
  long an,bn,num,den;
  double an2,bn2,num2,den2;
  for (auto g: this->games){
    g.p.first +=10000000000000;
    g.p.second+=10000000000000;
    // use double
    num2 = (g.p.second* g.a.first) - (g.p.first*g.a.second);
    den2 = (g.b.second* g.a.first) - (g.b.first*g.a.second);
    bn2 = num2/den2;
    an2 = (g.p.first - bn2*g.b.first)/g.a.first;
    // convert to long
    bn = (long) bn2;
    an = (long) an2;
    if ((bn == bn2) && (an == an2)) {
      sol2+=((an*3)+bn);
    }
  }
  return to_string(sol2);
}
}
