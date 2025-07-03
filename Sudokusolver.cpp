#include <iostream>
#include <fstream>
using namespace std;

int board[9][9];  // Global board

// Function to check if placing num is valid
bool isSafe(int board[9][9], int row, int col, int num) {
    for (int x = 0; x < 9; x++) {
        if (board[row][x] == num || board[x][col] == num)
            return false;
    }

    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[startRow + i][startCol + j] == num)
                return false;

    return true;
}

// Backtracking Sudoku solver
bool solveSudoku(int board[9][9]) {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (board[row][col] == 0) {
                for (int num = 1; num <= 9; num++) {
                    if (isSafe(board, row, col, num)) {
                        board[row][col] = num;
                        if (solveSudoku(board))
                            return true;
                        board[row][col] = 0; // backtrack
                    }
                }
                return false; // No number fits
            }
        }
    }
    return true;
}

// Display the board
void printBoard(int board[9][9]) {
    cout << "-------------------------\n";
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << "-------------------------\n";
}

// Load puzzle from file
void loadPuzzleFromFile(string filename) {
    ifstream file(filename);
    string line;
    int i = 0;

    while (getline(file, line) && i < 9) {
        for (int j = 0; j < 9; j++) {
            board[i][j] = line[j] - '0';
        }
        i++;
    }
    file.close();
}

// Save solved board to file
void saveSolutionToFile(string filename) {
    ofstream file(filename);
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            file << board[i][j];
        }
        file << "\n";
    }
    file.close();
}

// Main CLI menu
int main() {
    int choice;
    string puzzleFile = "puzzles.txt";
    string solutionFile = "solved.txt";

    while (true) {
        cout << "\n=== Sudoku Solver CLI ===\n";
        cout << "1. Load Puzzle from File\n";
        cout << "2. Solve Puzzle\n";
        cout << "3. Save Solution to File\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                loadPuzzleFromFile(puzzleFile);
                cout << "Puzzle loaded successfully.\n";
                printBoard(board);
                break;

            case 2:
                if (solveSudoku(board)) {
                    cout << "Puzzle solved successfully.\n";
                    printBoard(board);
                } else {
                    cout << "No solution exists.\n";
                }
                break;

            case 3:
                saveSolutionToFile(solutionFile);
                cout << "Solution saved to " << solutionFile << "\n";
                break;

            case 4:
                cout << "Exiting...\n";
                return 0;

            default:
                cout << "Invalid choice.\n";
        }
    }

    return 0;
}
