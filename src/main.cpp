#include "aoc_utils.hpp"
#include "days.hpp"

int main(int argc, char* argv[]) {

  vector<unique_ptr<aoc::DayAPI>> solvers = {};
  if constexpr (!is_abstract_v<day00::Day>) solvers.push_back(make_unique<day00::Day>());
  if constexpr (!is_abstract_v<day01::Day>) solvers.push_back(make_unique<day01::Day>());
  if constexpr (!is_abstract_v<day02::Day>) solvers.push_back(make_unique<day02::Day>());
  if constexpr (!is_abstract_v<day03::Day>) solvers.push_back(make_unique<day03::Day>());
  if constexpr (!is_abstract_v<day04::Day>) solvers.push_back(make_unique<day04::Day>());
  if constexpr (!is_abstract_v<day05::Day>) solvers.push_back(make_unique<day05::Day>());
  if constexpr (!is_abstract_v<day06::Day>) solvers.push_back(make_unique<day06::Day>());
  if constexpr (!is_abstract_v<day07::Day>) solvers.push_back(make_unique<day07::Day>());
  if constexpr (!is_abstract_v<day08::Day>) solvers.push_back(make_unique<day08::Day>());
  if constexpr (!is_abstract_v<day09::Day>) solvers.push_back(make_unique<day09::Day>());
  if constexpr (!is_abstract_v<day10::Day>) solvers.push_back(make_unique<day10::Day>());
  if constexpr (!is_abstract_v<day11::Day>) solvers.push_back(make_unique<day11::Day>());
  if constexpr (!is_abstract_v<day12::Day>) solvers.push_back(make_unique<day12::Day>());
  if constexpr (!is_abstract_v<day13::Day>) solvers.push_back(make_unique<day13::Day>());
  if constexpr (!is_abstract_v<day14::Day>) solvers.push_back(make_unique<day14::Day>());
  if constexpr (!is_abstract_v<day15::Day>) solvers.push_back(make_unique<day15::Day>());
  if constexpr (!is_abstract_v<day16::Day>) solvers.push_back(make_unique<day16::Day>());
  if constexpr (!is_abstract_v<day17::Day>) solvers.push_back(make_unique<day17::Day>());
  if constexpr (!is_abstract_v<day18::Day>) solvers.push_back(make_unique<day18::Day>());
  if constexpr (!is_abstract_v<day19::Day>) solvers.push_back(make_unique<day19::Day>());
  if constexpr (!is_abstract_v<day20::Day>) solvers.push_back(make_unique<day20::Day>());
  if constexpr (!is_abstract_v<day21::Day>) solvers.push_back(make_unique<day21::Day>());
  if constexpr (!is_abstract_v<day22::Day>) solvers.push_back(make_unique<day22::Day>());
  if constexpr (!is_abstract_v<day23::Day>) solvers.push_back(make_unique<day23::Day>());
  if constexpr (!is_abstract_v<day24::Day>) solvers.push_back(make_unique<day24::Day>());
  if constexpr (!is_abstract_v<day25::Day>) solvers.push_back(make_unique<day25::Day>());

  if (argc!=2) {
    cout << "Usage: main <data_path>" << endl;
    return 1;
  }
  fs::path data_path(argv[1]);
  if (!fs::is_directory(data_path)) {
    cout << data_path.string() << " is not a valid folder" << endl;
    return 1;
  }
  string day_s;
  set<int> errors = {};

  for(auto& solver : solvers) {

    day_s = format("{:02}",solver->day());
    cout << format("Solving Day {}", day_s) << endl;

    vector<string> cases = {
      "test",
      "user1"
    };
    for (auto case_s: cases) {

      string case_msg = format("Solving Day {}, Case {}", day_s, case_s);
      cout << case_msg << endl;

      fs::path case_path  = data_path /  day_s / case_s ;

      fs::path sol_path  = case_path / "sol";
      fs::path input_path  = case_path / "input";

      ifstream file(input_path);
      solver->parse(file);
      aoc::Solution sol = {
        solver->part1(),
        solver->part2()
      };
      file.close();

      cout << case_msg << " ";
      if (!aoc::check_solutions(sol_path, sol))
          errors.insert(solver->day());
    }

    cout << endl;
  }

  if (!errors.size()) cout << endl << "--- All Solved" << endl;
  else {
      cout << "--- Failing cases: ";
      for (auto failing_day: errors) cout << failing_day << " ";
      cout << endl;
  }
}
