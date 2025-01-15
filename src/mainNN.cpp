#include "aoc_utils.hpp"
#include "day.hpp"

using namespace aoc;

int main(int argc, char* argv[]) {

  NS::Day solver;

  auto args = aoc::parse_args(argc, argv);
  ifstream input_file(args.input_path);

  solver.set_log_level(args.verbose);

  // Parsing
  solver.parse(input_file);
  // Sol1
  string sol1 = solver.part1();
  // Sol2
  string sol2 = solver.part2();

  aoc::check_solutions(args.sol_path, {sol1, sol2});

}
