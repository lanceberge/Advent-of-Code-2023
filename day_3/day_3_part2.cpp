// line-by-line
// for each number, add to sum if there's an adjacent symbol

#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
  For each * with exactly two adjacent numbers, compute their product and
  return the sum
*/
class Day3 {

public:
  long sumAdjacentProducts(const vector<string> &grid) {
    long sum = 0;

    for (int i = 0; i < grid[0].size(); ++i) {
      for (int j = 0; j < grid.size(); ++j) {
        if (grid[i][j] == '*') {
          sum += adjacentNumberProduct(grid, i, j);
        }
      }

      return sum;
    }
  }

  int adjacentNumberProduct(const vector<string> &grid, int i, int j) {

    int m = grid.size(), n = grid[0].size();
    vector<int> adjacentNumbers = vector<int>();

    // Check left
    if (i - 1 > 0) {
      if (isdigit(grid[j][i - 1])) {
        adjacentNumbers.push_back(matchLongestNumber(grid[j], i - 1, -1));
      }
    }

    // Check right
    if (i + 1 < m) {
      if (isdigit(grid[j][i + 1])) {
        adjacentNumbers.push_back(matchLongestNumber(grid[j], i + 1, 1));
      }
    }

    // Check top
    if (j - 1 > 0) {
      vector<int> adjacentInRow = getAdjacentNumbersInRow(grid[j - 1], i);
      adjacentNumbers.insert(adjacentNumbers.end(), adjacentInRow.begin(),
                             adjacentInRow.end());
    }

    // Check bottom
    if (j + 1 < n) {
      vector<int> adjacentInRow = getAdjacentNumbersInRow(grid[j - 1], i);
      adjacentNumbers.insert(adjacentNumbers.end(), adjacentInRow.begin(),
                             adjacentInRow.end());
    }

    return adjacentNumbers.size() != 2
               ? 0
               : adjacentNumbers[0] * adjacentNumbers[1];
  }

  vector<int> getAdjacentNumbersInRow(const string &line, int i) {

    vector<int> adjacentNumbers;
    // If the top left is a number
    if (isdigit(i - 1 >= 0 && line[i - 1])) {
      int longestMatch = matchLongestNumber(line, max(0, i - 1), 1);
      adjacentNumbers.push_back(longestMatch);

      // if the match is less than two digits, the top-right could adjacent
      if (i + 1 < line.length() && i + 1 < line.length()) {
        if (isdigit(line[i + 1])) {
          adjacentNumbers.push_back(matchLongestNumber(line, i + 1, 1));
        }
      }

      // if the top left isn't a number, check top and top right
    } else if (isdigit(line[i])) {
      adjacentNumbers.push_back(matchLongestNumber(line, i, 1));
    } else if (i + 1 < line.length() && isdigit(line[i + 1])) {
      adjacentNumbers.push_back(matchLongestNumber(line, i + 1, 1));
    }

    return adjacentNumbers;
  }

  int matchLongestNumber(const string &line, int start, int direction) {
    int end = start;

    while (end >= 0 && end < line.length() && isdigit(line[end])) {
      end += direction;
    }

    int actualStart = (direction == 1) ? start : end;
    int actualEnd = (direction == 1) ? end : start;
    string numStr = line.substr(actualStart, actualEnd - actualStart + 1);
    return stoi(numStr);
  }
};

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

  long result = Day3().sumAdjacentProducts(grid);

  cout << result << endl;

  return 0;
}
