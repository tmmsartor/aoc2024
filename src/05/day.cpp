#include "day.hpp"

using namespace std::literals::string_view_literals;
namespace day05 {


void Day::parse(ifstream& file) {
  string line = "";
  char comma=',';
  stringstream ss;
  string val_str;
  char delim;
  int val1,val2;
  this->books.clear();
  this->rulesmap.clear();

  while (getline(file,line) && line.size())  {
    //cout << line << endl;
    ss.clear();
    ss.str(line);
    if ((ss >> val1 >> delim >> val2) && (delim == '|')) {
      //cout << val1 << delim << val2 << endl;
      if (!this->rulesmap.contains(val1)) {
        Deps deps;
        this->rulesmap[val1] = deps;
      } 
      this->rulesmap[val1].insert(val2);
    }
  }

  while (getline(file,line)) {
    Book book = {};
    ss.clear();
    ss.str(line);
    while (getline(ss, val_str, comma))
        book.push_back(stoi(val_str));
    this->books.push_back(book);
  }

  if (this->log_level) for (auto r: this->rulesmap) cout << r << endl;
  if (this->log_level) cout << this->books << endl;
}


pair<int,int> solve(RulesMap& rules, Books& books, int DEBUG) {
  int sum1 = 0;
  int sum2 = 0;
  bool valid = true;
  Book book1 = {};
  for (auto book: books) {
    valid = true;
    book1 = book;
    int prev_page = 0;
    int first_page = book[0];
    int page_i;

    // loop over pages of current book to be checked
    for (auto it=book.begin(); it!=book.end(); it++){
      // loop over already committed page
      for (auto it2=book.begin(); it2!=it; it2++)
        // check if current,previous pair violate any rules
        if (rules[*it].contains(*it2)) {
          valid = false;
          if (DEBUG) cout<< *it << ", "<< *it2 << endl;
          swap(*it, *it2);
        }
    }

    if (valid) sum1 += book1[(book1.size()+1)/2-1];
    else {
      if (DEBUG) cout << book1 << endl;
      if (DEBUG) cout << book << endl;
      sum2 += book[(book.size()+1)/2-1];
    }
  }

  return make_pair(sum1,sum2);
}

string Day::part1() {
  auto [sol1,sol2] = solve(this->rulesmap, this->books, this->log_level);
  this->sol2 = sol2;
  return to_string(sol1);
}

string Day::part2() {
  return to_string(this->sol2);
}

}
