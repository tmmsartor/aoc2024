#include "day.hpp"

ostream& operator<<(ostream& os, const day17::BitArray& b) {
  for (int i=63;i>=0;i--)
    if (b.mask[i]) os << b.data[i];
    else os << "_";
  return os;
}

namespace day17 {


bool BitArray::set(size_t offset, bitset<3> n){
  for (int i=0; i<3;i++){
    int idx = offset+i;
    if (mask[idx] && data[idx]!= n[i]) return false;
    data[idx]=n[i];
    mask.set(idx);
  }
  return true;
}

void parse_bitarray(ifstream& file, Mem& registers, Mem& code, int DEBUG) {

  string line;
  // interger value of combo argument
  for (int i=0;i<=3;i++) registers.push_back(i);

  getline(file, line);
  registers.emplace_back(stoul(line.substr(12)));
  getline(file, line);
  registers.emplace_back(stoul(line.substr(12)));
  getline(file, line);
  registers.emplace_back(stoul(line.substr(12)));
  getline(file, line);
  getline(file, line);
  line = line.substr(9);
  //while ((pos = line.find(',')) != std::string::npos)
  for (int i=0; i<line.length();i+=2){
    code.push_back(stoi(line.substr(i,1)));
  }

  if (DEBUG) cout << "Code: " << code << endl;
  if (DEBUG) cout << "Registers: " << registers << endl;
}

void execute(Mem& regs, const Mem& code, Mem& out, int ip, int DEBUG) {
  int opcode = code[ip++];
  ulong arg = code[ip++];
  if (DEBUG>1) cout << format("opcode:{} arg:{} new ip:{}",opcode,arg,ip) << endl;
  if (ip>code.size()) return;

  if        (opcode==0) {
    regs[4] = (ulong) regs[4]/(2 << (regs[arg]-1));
  } else if (opcode==1) {
    regs[5] = regs[5] ^ arg;
  } else if (opcode==2) {
    regs[5] = regs[arg] % 8;
  } else if (opcode==3) {
    if (!regs[4]) return;
    execute(regs, code, out, arg, DEBUG);
  } else if (opcode==4) {
    regs[5] = regs[5] ^ regs[6];
  } else if (opcode==5) {
    out.emplace_back(regs[arg] % 8);
  } else if (opcode==6) {
    regs[5] = regs[4]/(2 << (regs[arg]-1));
  } else if (opcode==7) {
    regs[6] = regs[4]/(2 << (regs[arg]-1));
  }
  execute(regs, code, out, ip, DEBUG);
}

void back_solve(BitArray& regA, const Mem& code, set<ulong>& sols, size_t ip, int DEBUG) {

  if (ip==code.size()) sols.insert(regA.data.to_ulong());

  size_t offset = ip*3;
  int ci = code[ip];
  
  for (size_t seed=0; seed<8;seed++) {
    BitArray regAi = regA;
    // try to set the seed
    if (!regAi.set(offset,bitset<3>(seed))) continue;
    if (DEBUG>1) cout << regAi << " ip: " << ip << endl;
    int shift = seed ^ 3;
    bitset<3> regA_part(ci ^ 5 ^ shift);
    ulong shifted = regA_part.to_ulong() << shift;

    if (DEBUG>2) {
      bitset<64> mask = 0;
      for (int i=0; i<3; i++) mask.set(offset+shift+i);
      cout << BitArray(shifted,mask) << endl;
      cout << regAi << endl;
    }

    if ((shift+offset+2) >= 64) continue;
    // try to set part
    if (!regAi.set(offset+shift,regA_part)) continue;
    back_solve(regAi, code, sols, ip+1, DEBUG);
  }
}

void Day::parse(ifstream& file) {
  if (this->log_level) cout << "Parse input" << endl;
  this->regs.clear();
  this->code.clear();

  parse_bitarray(file, this->regs, this->code, this->log_level);
  if (this->regs[4] < 1000)
    this->is_test = true;
  else
    this->is_test = false;
}

string Day::part1() {
  if (this->log_level) cout << "Solve part1" << endl;
  Mem regs1 = this->regs;
  Mem out;
  int ip = 0;
  execute(regs1, code, out, ip, this->log_level);

  stringstream res1;
  auto it = out.begin();
  res1 << *(it++);
  for (; it!=out.end(); it++) res1 << format(",{}",*it);
  string sol1 = res1.str();
  return sol1;
}

string Day::part2() {
  if (this->is_test) return "0";
  if (this->log_level) cout << "Solve part2" << endl;
  BitArray regA;
  Mem out;
  set<ulong> sols = {};
  back_solve(regA, code, sols, 0, this->log_level);
  // get smallest int
  ulong sol2 = *begin(sols);
  // check solution
  Mem regs2 = this->regs;
  regs2[4] = sol2;
  execute(regs2, code, out, 0, this->log_level);
  if (out!=code ) sol2=0;
  if (out!=code && this->log_level)
    cout << "Error: " << endl << out << " !=" << endl << code << endl << endl;
  if (this->log_level) cout << "End part2" << endl;
  return to_string(sol2);
}

}

