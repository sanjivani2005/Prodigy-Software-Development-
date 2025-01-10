#include <iostream>
#include <vector>

using namespace std;

#define N 9 // Size of the Sudoku grid

// Function prototypes
bool solveSudoku(vector<vector<int>>& grid);
bool isSafe(vector<vector<int>>& grid, int row, int col, int num);
bool findEmptyLocation(vector<vector<int>>& grid, int& row, int& col);
void printGrid(const vector<vector<int>>& grid);

int main() {
    // Example unsolved Sudoku puzzle (0 represents empty cells)
    vector<vector<int>> grid = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    if (solveSudoku(grid)) {
        cout << "Sudoku solved successfully!\n";
        printGrid(grid);
    } else {
        cout << "No solution exists for the given Sudoku puzzle." << endl;
    }

    return 0;
}

// Function to solve the Sudoku puzzle using backtracking
bool solveSudoku(vector<vector<int>>& grid) {
    int row, col;

    // Find an empty location in the grid
    if (!findEmptyLocation(grid, row, col)) {
        return true; // No empty location, puzzle is solved
    }

    for (int num = 1; num <= 9; ++num) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num; // Make a tentative assignment

            if (solveSudoku(grid)) {
                return true;
            }

            grid[row][col] = 0; // Undo assignment (backtrack)
        }
    }

    return false; // Trigger backtracking
}

// Function to check if it is safe to assign a number to a cell
bool isSafe(vector<vector<int>>& grid, int row, int col, int num) {
    // Check row
    for (int x = 0; x < N; ++x) {
        if (grid[row][x] == num) {
            return false;
        }
    }

    // Check column
    for (int x = 0; x < N; ++x) {
        if (grid[x][col] == num) {
            return false;
        }
    }

    // Check 3x3 subgrid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (grid[startRow + i][startCol + j] == num) {
                return false;
            }
        }
    }

    return true;
}

// Function to find an empty location in the grid
bool findEmptyLocation(vector<vector<int>>& grid, int& row, int& col) {
    for (row = 0; row < N; ++row) {
        for (col = 0; col < N; ++col) {
            if (grid[row][col] == 0) {
                return true;
            }
        }
    }
    return false;
}

// Function to print the Sudoku grid
void printGrid(const vector<vector<int>>& grid) {
    for (int row = 0; row < N; ++row) {
        for (int col = 0; col < N; ++col) {
            cout << grid[row][col] << " ";
        }
        cout << endl;
    }
}
