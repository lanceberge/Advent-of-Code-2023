// line-by-line
// for each number, add to sum if there's an adjacent symbol

#include <cctype>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>

using namespace std;
bool isSymbol(char c) { return c != '.' && !isdigit(c); }

bool hasAdjacentSymbol(const vector<string> &grid, int row, int startPos,
                       int endPos) {

  int m = grid.size(), n = grid[0].size();
  int rowStart = max(0, row - 1);
  int rowEnd = min(m - 1, row + 1);
  int colStart = max(0, startPos - 1);
  int colEnd = min(n - 1, endPos + 1);

  for (int i = rowStart; i <= rowEnd; ++i) {
    for (int j = colStart; j <= colEnd; ++j) {
      if (isSymbol(grid[i][j])) {
        return true;
      }
    }
  }
  return false;
}

int sumAdjacentNumbers(const vector<string> &grid) {
  int sum = 0;
  regex numberRegex("\\d+");
  for (int j = 0; j < grid.size(); ++j) {
    const string &line = grid[j];

    auto rit = sregex_iterator(line.begin(), line.end(), numberRegex);

    for (auto it = rit; it != sregex_iterator(); ++it) {
      auto match = *it;
      int startPos = match.position();
      int endPos = startPos + match.length() - 1;

      if (hasAdjacentSymbol(grid, j, startPos, endPos)) {
        sum += stoi(match.str());
      }
    }
  }

  return sum;
}

int main() {
  vector<string> grid;

  string filename = "input.txt";

  ifstream file(filename);

  string line;
  while (getline(file, line)) {
    if (!line.empty()) {
      grid.push_back(line);
    }
  }

  file.close();

  int result = sumAdjacentNumbers(grid);

  cout << result << endl;

  return 0;
}
