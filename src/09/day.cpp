#include "day.hpp"

namespace day09{

int DEBUG = 0;


void DiskCompactor::parseInput(const string& input) {
  int fileId = 0;
  int position = 0;
  spaces = {};
  files = {};
  disk = {};

  for (size_t i = 0; i < input.length(); i++) {
    int length = input[i] - '0';

    if (i % 2 == 0) {
      files.push_back(File(fileId, length, disk.size()));
      for (int j = 0; j < length; j++) {
        disk.emplace_back(fileId);
      }
      fileId++;
    } else {
      spaces.push_back({length, disk.size()});

      for (int j = 0; j < length; j++) {
        disk.emplace_back(-1);
      }
    }
    position += length;
  }
}

vector<int> DiskCompactor::compact2() {
  vector<int> disk1(this->disk);
  while (files.size()>0) {
    File fl = files.back();
    bool moved = false;
    int idx = 0;
    for (int i=0; i<spaces.size(); i++) {
      if (moved) break;
      if (spaces[i].first < fl.size) continue;
      idx = spaces[i].second;
      if (idx > fl.position) break;

      spaces[i].first -= fl.size;
      spaces[i].second += fl.size;

      for (int j = 0; j < fl.size; j++) {
        disk1[idx+j] = fl.id;
        disk1[fl.position+j] = -1;
      }
      moved = true;
    }
    files.pop_back();
  }
  return disk1;
}

  vector<int> DiskCompactor::compact1() {
    vector<int> disk1(this->disk);
    int back=disk1.size()-1;
    int front=0;
    while  (back > front){
      if (disk1[front] >= 0) {
        front++;
        continue;
      }
      if (disk1[back] < 0) {
        back--;
        continue;
      }
      //cout << front << "<-" << back << ":" << disk1[back] << endl;
      disk1[front] = disk1[back];
      disk1[back] = -1; 
    }
    return disk1;
  }

void DiskCompactor::show(vector<int>& disk) {
  for (auto di: disk) {
    if  (di ==-1) cout<<".";
    else cout<<di;
  }
  cout << endl;
}

ulong DiskCompactor::checksum(vector<int>& disk) {
  if (DEBUG) show(this->disk);
  if (DEBUG) show(disk);
  long long sum = 0;
  int i = 0;
  for (i=0;i<disk.size();i++) {
    if (disk[i] == -1) continue;
    sum += i * disk[i];
  }
  return sum;
}


void Day::parse(ifstream& file) {
  string input;
  getline(file, input);
  this->disk_compactor.parseInput(input);
}

string Day::part1() {
  vector<int> disk1 = this->disk_compactor.compact1();
  return to_string(this->disk_compactor.checksum(disk1));
}

string Day::part2() {
  vector<int> disk2 = this->disk_compactor.compact2();
  return to_string(this->disk_compactor.checksum(disk2));
}

}

