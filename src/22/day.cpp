#include "day.hpp"

ostream& operator<<(ostream& os, const day22::DiffSeq& t) {
  os << "("<<get<0>(t)<<", "<<get<1>(t)<<", "<<get<2>(t)<<", "<< get<3>(t)<<")";
  return os;
}

ostream& operator<<(ostream& os, const day22::Ints& t) {
  for (auto e:t) os << e << " ";
  return os;
}


namespace day22 {

bool operator==(const Ints& v, const DiffSeq& t) {
  if ((get<0>(t) == v[0]) &&
      (get<1>(t) == v[0+1]) &&
      (get<2>(t) == v[0+2]) &&
      (get<3>(t) == v[0+3])) return true;
  return false;
}

struct DiffSeqHasher {
  std::size_t operator()(const DiffSeq& s) const noexcept {
    return ((get<0>(s) & 15) << 12) | ((get<1>(s) & 15) << 8) | ((get<2>(s) & 15) << 4) | (get<3>(s) & 15);
  }
};

typedef unordered_map<DiffSeq,int,DiffSeqHasher> DiffSeqDict;
typedef unordered_set<DiffSeq,DiffSeqHasher> DiffSeqSet;


void Day::parse(ifstream& file) {
  string line;
  this->buyers = {};

  while (getline(file, line)) {
    Buyer buyer = {stoi(line),{},{}};
    this->buyers.emplace_back(buyer);
  }

}

string Day::part1() {
  ulong sol1 = 0;
  ulong ni;
  int iters = 2000;
  if (this->log_level>1) iters = 10;
  int prune = 16777216;
  int price, price_prev;

  for (auto& buyer: this->buyers) {
    Ints& prices = buyer.prices;
    Ints& diffs = buyer.diffs;
    ulong n = buyer.secret;
    price_prev = n%10;
    for (int i=0;i<iters;i++){
      ni = n * 64;
      n = ni ^ n;
      n %= prune;

      ni = n / 32;
      n = ni ^ n;
      n %= prune;

      ni = n * 2048;
      n = ni ^ n;
      n %= prune;

      price = n%10;

      diffs.emplace_back(price-price_prev);
      prices.emplace_back(price);
      if (this->log_level>1) cout << n << ": " << price << "," << price-price_prev << endl;

      price_prev = price;
    }
    sol1 += n;
  }
  return to_string(sol1);
}

string Day::part2() {
  ulong sol2 = 0;
  DiffSeqDict score_dict = {};
  DiffSeqSet seq_set;
  DiffSeq s;
  int max_price = 0;
  int price_i = 0;
  Ints best_prices = {};
  Ints target = {-2,1,-1,3};

  for (auto& buyer: this->buyers){
    Ints& d = buyer.diffs;
    Ints& p = buyer.prices;
    seq_set = {};
    for (int i=0; i<d.size()-3;i++){
      s = {d[i],d[i+1],d[i+2],d[i+3]};
      if (seq_set.count(s)) continue;
      price_i = p[i+3];

      if (!score_dict.count(s)) score_dict[s] = price_i;
      else score_dict[s] += price_i;
      seq_set.insert(s);
    }
  }

  for (auto el: score_dict)
    if (el.second > sol2)
     sol2=el.second;

  return to_string(sol2);
}

}

