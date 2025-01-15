#ifndef AOC_UTILS_H
#define AOC_UTILS_H

#include <filesystem>

#include "aoc.hpp"

namespace fs = filesystem;

namespace aoc {

int DEBUG = 0;

struct Args{
  ifstream file;
  fs::path input_path;
  fs::path sol_path;
  pair<string,string> sol;
  bool has_solution;
  int verbose;
  int error;
  string message;
};

Args parse_args(int argc, char* argv[]);
void check_solutions(const Args& args, string sol1, string sol2);


Args parse_args(int argc, char* argv[]) {
  Args args;
  args.error = 1;

  if (argc < 2) {
    args.message="Not enough arguments";
    return args;
  }
  fs::path p(argv[1]);
  args.input_path  = p / "input";
  args.sol_path  = p / "sol";

  if (!fs::is_regular_file(args.input_path)) {
    args.message=format("{} is not a regular file", args.input_path.string());
    cout << args.message << endl;
    return args;
  }

  if (fs::is_regular_file(args.sol_path)) {
    ifstream file(args.sol_path);
    string sol1;
    string sol2;
    getline(file, sol1);
    getline(file, sol2);
    args.sol = {sol1,sol2};
    args.has_solution = true;
  } else {
    args.message=format("True solutions are not yet known");
    cout << args.message << endl;
    args.sol = {"",""};
  }

  if (argc == 3) DEBUG=stoi(argv[2]);

  if (DEBUG>1) cout << format("Using args: {}",p.string()) << endl;
  //if (DEBUG) cout << format("---- Day {:d}",day) << endl;

  args.error = 0;
  args.verbose = DEBUG;

  return args;
}

pair<string,string> get_solution_from_file(const fs::path& sol_path){
  pair<string,string> solutions;
  ifstream file(sol_path);
  getline(file, solutions.first);
  getline(file, solutions.second);
  return solutions;
}

bool check_solutions(const fs::path& sol_path, const Solution& sol){

  if (fs::is_regular_file(sol_path)) {
    auto true_sol = aoc::get_solution_from_file(sol_path);

    if (sol.first == true_sol.first && sol.second == true_sol.second){
      cout << "--- Solved" << endl;
      return true;
    }
    if (sol.first != true_sol.first || sol.second != true_sol.second) cout << "--- Error" << endl;
    if (sol.first != true_sol.first) cout << true_sol.first << "!=" << sol.first  << endl;
    if (sol.second != true_sol.second) cout << true_sol.second << "!=" << sol.second << endl;
  } else {
    cout << "Part1: " << sol.first << endl;
    cout << "Part2: " << sol.second << endl;
  }

  return false;
}

}

#endif
