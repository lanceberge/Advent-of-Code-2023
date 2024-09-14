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
        if (grid[j][i] == '*') {
          sum += adjacentNumberProduct(grid, i, j);
        }
      }
    }

    return sum;
  }

  /*
    Find all of the adjacent numbers of grid[j][i]. Return their product
    if there are two of them
  */
  int adjacentNumberProduct(const vector<string> &grid, int i, int j) {

    int m = grid[0].size(), n = grid.size();
    vector<int> adjacentNumbers;

    // Check left
    if (i > 0 && isdigit(grid[j][i - 1])) {
      adjacentNumbers.push_back(matchLongestNumber(grid[j], i - 1));
    }

    // Check right
    if (i + 1 < m && isdigit(grid[j][i + 1])) {
      adjacentNumbers.push_back(matchLongestNumber(grid[j], i + 1));
    }

    // Check top
    if (j > 0) {
      vector<int> adjacentInRow = getAdjacentNumbersInRow(grid[j - 1], i);
      adjacentNumbers.insert(adjacentNumbers.end(), adjacentInRow.begin(),
                             adjacentInRow.end());
    }

    // Check bottom
    if (j + 1 < n) {
      vector<int> adjacentInRow = getAdjacentNumbersInRow(grid[j + 1], i);
      adjacentNumbers.insert(adjacentNumbers.end(), adjacentInRow.begin(),
                             adjacentInRow.end());
    }

    return adjacentNumbers.size() != 2
               ? 0
               : adjacentNumbers[0] * adjacentNumbers[1];
  }

  vector<int> getAdjacentNumbersInRow(const string &line, int i) {

    vector<int> adjacentNumbers;
    // If the left is a number
    if (i - 1 >= 0 && isdigit(line[i - 1])) {
      int leftMatch = matchLongestNumber(line, i - 1);
      adjacentNumbers.push_back(leftMatch);

      // if there is a match to the left, then there isn't a digit, then there
      // is, then we have two adjacent pairs, ex:
      // 856.495
      // ...*...

      if (!isdigit(line[i]) && i + 1 < line.length()) {
        if (isdigit(line[i + 1])) {
          adjacentNumbers.push_back(matchLongestNumber(line, i + 1));
        }
      }

      // if the left isn't a number, check and right
    } else if (isdigit(line[i])) {
      adjacentNumbers.push_back(matchLongestNumber(line, i));
    } else if (i + 1 < line.length() && isdigit(line[i + 1])) {
      adjacentNumbers.push_back(matchLongestNumber(line, i + 1));
    }

    return adjacentNumbers;
  }

  // Proceed both left and right to match the longest int
  int matchLongestNumber(const string &line, int start) {
    int left = start;
    while (left > 0 && isdigit(line[left - 1])) {
      left--;
    }

    int right = start;
    while (right < line.length() - 1 && isdigit(line[right + 1])) {
      right++;
    }

    string numStr = line.substr(left, right - left + 1);
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
