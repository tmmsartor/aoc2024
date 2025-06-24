#include "day.hpp"

namespace day06 {

Point rotate_clockwise(const Point& dir) {
  // Rotate 90 degrees clockwise:
  // (-1,0) -> (0,1) -> (1,0) -> (0,-1) -> (-1,0)
  return {dir.y, -dir.x};
}

set<Point> simulate_guard_path(const GuardMap& grid, Point start_pos, Point start_dir) {
  set<Point> visited;
  Point guard_pos = start_pos;
  Point dir = start_dir;

  visited.insert(guard_pos);

  while (true) {
    Point next_pos = guard_pos + dir;

    // Check if outside bounds
    if (!grid.is_valid(next_pos)) {
      break;  // walked off the grid
    }

    Cell next_cell = grid.at(next_pos);
    if (next_cell.s == -1) {  // obstacle
      // Rotate and try again
      dir = rotate_clockwise(dir);
    } else {
      // Move to next position
      guard_pos = next_pos;
      visited.insert(guard_pos);
    }
  }

  return visited;
}

bool creates_loop(const GuardMap& grid, Point start_pos, Point start_dir, const Point& obstacle_pos) {
  // Track position and direction pairs to detect loops
  set<pair<Point, Point>> state_history;
  Point guard_pos = start_pos;
  Point dir = start_dir;

  while (true) {
    // Check if we've been in this state before (same position and direction)
    pair<Point, Point> current_state = {guard_pos, dir};
    if (state_history.count(current_state)) {
      return true;  // Found a loop
    }
    state_history.insert(current_state);

    Point next_pos = guard_pos + dir;

    // Check if outside bounds
    if (!grid.is_valid(next_pos)) {
      return false;  // walked off the grid, no loop
    }

    Cell next_cell = grid.at(next_pos);
    if (next_cell.s == -1 || next_pos == obstacle_pos) {  // obstacle or new obstruction
      // Rotate and try again
      dir = rotate_clockwise(dir);
    } else {
      // Move to next position
      guard_pos = next_pos;
    }
  }
}

void Day::parse(ifstream& file) {
  vector<string> lines;
  string line;

  while (getline(file, line)) {
    lines.push_back(line);
  }

  if (lines.empty()) return;

  rows = lines.size();
  cols = lines[0].size();

  // Initialize grid
  Mat<Cell> grid_data(rows, vector<Cell>(cols));

  // Parse the grid and find guard starting position
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      char c = lines[i][j];
      // guard start position
      if (c == '^') {
        guard_start = {i, j};
        grid_data[i][j] = Cell(-2);
      // obstacle
      } else if (c == '#') {
        grid_data[i][j] = Cell(-1);
      // free space
      } else {
        grid_data[i][j] = Cell(0);

      }
    }
  }

  this->grid.init(std::move(grid_data));
}

string Day::part1() {
  // initially facing up
  Point dir = {-1, 0};
  set<Point> visited = simulate_guard_path(grid, guard_start, dir);
  return to_string(visited.size());
}

string Day::part2() {
  // initially facing up
  Point dir = {-1, 0};

  // First, get the original path
  set<Point> original_path = simulate_guard_path(grid, guard_start, dir);

  int loop_positions = 0;

  // Try placing an obstacle at each position in the original path
  // (except the starting position)
  for (const Point& pos : original_path) {
    // Can't place obstacle at guard's starting position
    if (pos == guard_start) continue;

    Cell cell = grid.at(pos);
    // Already an obstacle
    if (cell.s == -1) continue;

    // Check if placing an obstacle here creates a loop
    if (creates_loop(grid, guard_start, dir, pos)) {
      loop_positions++;
    }
  }

  return to_string(loop_positions);
}

}
