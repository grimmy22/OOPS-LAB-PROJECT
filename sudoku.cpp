#include "sudoku.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cstring>
#include <string>

using namespace std;

Sudoku::Sudoku() {
    cout << "Sudoki Game constructor called" << endl;

    gridSize = 9;
    moveCount = 0;
    score = 0;
    hintsUsed = 0;
    hintsRemaining = 3; 
    strcpy(playerName, "Player");

    
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            board[i][j] = 0;
            originalBoard[i][j] = 0;
        }
    }

    
    for (int i = 0; i < MAX_MOVES; i++) {
        moveRow[i] = -1;
        moveCol[i] = -1;
        moveValue[i] = -1;
    }

    srand(time(0));

    cout << "Sudoki Game constructor finished" << endl;
}

bool Sudoku::isValidPlacement(int row, int col, int num) {
    
    for (int j = 0; j < gridSize; j++) {
        if (board[row][j] == num) {
            return false;
        }
    }

    
    for (int i = 0; i < gridSize; i++) {
        if (board[i][col] == num) {
            return false;
        }
    }

    
    int boxSize = sqrt(gridSize);
    int boxRow = row - row % boxSize;
    int boxCol = col - col % boxSize;

    for (int i = boxRow; i < boxRow + boxSize; i++) {
        for (int j = boxCol; j < boxCol + boxSize; j++) {
            if (board[i][j] == num) {
                return false;
            }
        }
    }

    return true;
}

void Sudoku::fillDiagonal() {
    int boxSize = sqrt(gridSize);
    for (int box = 0; box < gridSize; box += boxSize) {
        fillBox(box, box);
    }
}

void Sudoku::fillBox(int row, int col) {
    int num;
    int boxSize = sqrt(gridSize);
    for (int i = 0; i < boxSize; i++) {
        for (int j = 0; j < boxSize; j++) {
            do {
                num = rand() % gridSize + 1;
            } while (!isValidPlacement(row + i, col + j, num));

            board[row + i][col + j] = num;
        }
    }
}

bool Sudoku::fillRemaining(int row, int col) {
    int boxSize = sqrt(gridSize);

    if (col >= gridSize && row < gridSize - 1) {
        row++;
        col = 0;
    }

    if (row >= gridSize && col >= gridSize) {
        return true;
    }

    if (row < boxSize) {
        if (col < boxSize) {
            col = boxSize;
        }
    } else if (row < gridSize - boxSize) {
        if (col == (row / boxSize) * boxSize) {
            col += boxSize;
        }
    } else {
        if (col == gridSize - boxSize) {
            row++;
            col = 0;
            if (row >= gridSize) {
                return true;
            }
        }
    }

    for (int num = 1; num <= gridSize; num++) {
        if (isValidPlacement(row, col, num)) {
            board[row][col] = num;

            if (fillRemaining(row, col + 1)) {
                return true;
            }

            board[row][col] = 0;
        }
    }

    return false;
}

void Sudoku::removeDigits(int difficulty) {
    int removeCount;

    switch (difficulty) {
        case 1:
            removeCount = 30; 
            break;
        case 2:
            removeCount = 40; 
            break;
        case 3:
            removeCount = 50; 
            break;
        case 4:
            removeCount = 60; 
            break;
        default:
            removeCount = 30;
    }

    cout << "Removing " << removeCount << " digits..." << endl;

    while (removeCount > 0) {
        int row = rand() % gridSize;
        int col = rand() % gridSize;

        if (board[row][col] != 0) {
            board[row][col] = 0;
            removeCount--;
        }
    }
}

bool Sudoku::solveSudoku() {
    for (int row = 0; row < gridSize; row++) {
        for (int col = 0; col < gridSize; col++) {
            if (board[row][col] == 0) {
                for (int num = 1; num <= gridSize; num++) {
                    if (isValidPlacement(row, col, num)) {
                        board[row][col] = num;

                        if (solveSudoku()) {
                            return true;
                        }

                        board[row][col] = 0;
                    }
                }
                return false;
            }
        }
    }
    return true;
}

void Sudoku::generatePuzzle(int difficulty) {
    cout << "Generating puzzle with difficulty level " << difficulty << endl;

    
    fillDiagonal();

    
    int boxSize = sqrt(gridSize);
    fillRemaining(0, boxSize);

    
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            originalBoard[i][j] = board[i][j];
        }
    }

    
    removeDigits(difficulty);
    
    
    resetHints(difficulty);

    cout << "Puzzle generation complete" << endl;
}

void Sudoku::printBoard() {
    cout << "\nSudoku Board:" << endl << endl;

    int boxSize = sqrt(gridSize);

    
    cout << "   ";
    for (int j = 0; j < gridSize; j++) {
        cout << (j + 1) << " ";
        if ((j + 1) % boxSize == 0 && j < gridSize - 1) {
            cout << "| ";
        }
    }
    cout << endl;

    
    cout << "  ";
    cout << "+";
    for (int box = 0; box < boxSize; box++) {
        for (int j = 0; j < boxSize * 2 + 1; j++) {
            cout << "-";
        }
        cout << "+";
    }
    cout << endl;

    
    for (int i = 0; i < gridSize; i++) {
        
        cout << (i + 1) << " |";

        
        for (int j = 0; j < gridSize; j++) {
            if (board[i][j] == 0) {
                cout << " .";
            } else {
                cout << " " << board[i][j];
            }

            if ((j + 1) % boxSize == 0 && j < gridSize - 1) {
                cout << " |";
            }
        }
        cout << " |";
        cout << endl;

        
        if ((i + 1) % boxSize == 0 && i < gridSize - 1) {
            cout << "  +";
            for (int box = 0; box < boxSize; box++) {
                for (int j = 0; j < boxSize * 2 + 1; j++) {
                    cout << "-";
                }
                cout << "+";
            }
            cout << endl;
        }
    }

    
    cout << "  +";
    for (int box = 0; box < boxSize; box++) {
        for (int j = 0; j < boxSize * 2 + 1; j++) {
            cout << "-";
        }
        cout << "+";
    }
    cout << endl << endl;
}

void Sudoku::printBoardWithHints() {
    cout << "\nSudoku Board (With Hints):" << endl << endl;

    int boxSize = sqrt(gridSize);

    
    cout << "   ";
    for (int j = 0; j < gridSize; j++) {
        cout << (j + 1) << " ";
        if ((j + 1) % boxSize == 0 && j < gridSize - 1) {
            cout << "| ";
        }
    }
    cout << endl;

    
    cout << "  ";
    cout << "+";
    for (int box = 0; box < boxSize; box++) {
        for (int j = 0; j < boxSize * 2 + 1; j++) {
            cout << "-";
        }
        cout << "+";
    }
    cout << endl;

    
    for (int i = 0; i < gridSize; i++) {
        
        cout << (i + 1) << " |";

        
        for (int j = 0; j < gridSize; j++) {
            if (board[i][j] == 0) {
                cout << " .";
            } else {
                
                if (isOriginalCell(i, j)) {
                    cout << "*" << board[i][j];  
                } else {
                    cout << " " << board[i][j];  
                }
            }

            if ((j + 1) % boxSize == 0 && j < gridSize - 1) {
                cout << " |";
            }
        }
        cout << " |";
        cout << endl;

        
        if ((i + 1) % boxSize == 0 && i < gridSize - 1) {
            cout << "  +";
            for (int box = 0; box < boxSize; box++) {
                for (int j = 0; j < boxSize * 2 + 1; j++) {
                    cout << "-";
                }
                cout << "+";
            }
            cout << endl;
        }
    }

    
    cout << "  +";
    for (int box = 0; box < boxSize; box++) {
        for (int j = 0; j < boxSize * 2 + 1; j++) {
            cout << "-";
        }
        cout << "+";
    }
    cout << endl << endl;
    cout << "Note: '*' indicates original cells (fixed numbers)" << endl << endl;
}

void Sudoku::setCellValue(int row, int col, int value) {
    if (row >= 0 && row < gridSize && col >= 0 && col < gridSize) {
        if (!isOriginalCell(row, col)) {
            
            if (moveCount < MAX_MOVES) {
                moveRow[moveCount] = row;
                moveCol[moveCount] = col;
                moveValue[moveCount] = board[row][col];
                moveCount++;
            }
            
            
            board[row][col] = value;
            
            
            if (value == originalBoard[row][col]) {
                updateScore(10); 
                cout << "Correct placement! +10 points" << endl;
            }
        } else {
            cout << "Cannot modify an original cell!" << endl;
        }
    }
}

bool Sudoku::isSolved() {
    
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            if (board[i][j] == 0) {
                return false;
            }
        }
    }

    
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            int num = board[i][j];

            
            board[i][j] = 0;
            if (!isValidPlacement(i, j, num)) {
                board[i][j] = num;
                return false;
            }
            board[i][j] = num;
        }
    }

    return true;
}

bool Sudoku::isValidMove(int row, int col, int num) {
    return isValidPlacement(row, col, num);
}

bool Sudoku::isOriginalCell(int row, int col) {
    
    
    return originalBoard[row][col] != 0 && board[row][col] == originalBoard[row][col];
}



void Sudoku::undoMove() {
    if (moveCount > 0) {
        moveCount--;
        int row = moveRow[moveCount];
        int col = moveCol[moveCount];
        int value = moveValue[moveCount];
        
        board[row][col] = value;
        cout << "Move undone. Cell at row " << (row+1) << ", column " << (col+1) 
             << " reverted to " << (value == 0 ? "empty" : to_string(value)) << endl;
    } else {
        cout << "No moves to undo!" << endl;
    }
}

void Sudoku::saveGame(const char* filename) {
    ofstream file(filename, ios::binary);
    
    if (!file.is_open()) {
        cout << "Error: Could not open file for saving" << endl;
        return;
    }
    
    
    file.write((char*)&gridSize, sizeof(gridSize));
    
    
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            file.write((char*)&board[i][j], sizeof(board[i][j]));
        }
    }
    
    
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            file.write((char*)&originalBoard[i][j], sizeof(originalBoard[i][j]));
        }
    }
    
    
    file.write((char*)&moveCount, sizeof(moveCount));
    for (int i = 0; i < moveCount; i++) {
        file.write((char*)&moveRow[i], sizeof(moveRow[i]));
        file.write((char*)&moveCol[i], sizeof(moveCol[i]));
        file.write((char*)&moveValue[i], sizeof(moveValue[i]));
    }
    
    
    file.write((char*)&playerName, sizeof(playerName));
    file.write((char*)&score, sizeof(score));
    
    
    file.write((char*)&hintsUsed, sizeof(hintsUsed));
    file.write((char*)&hintsRemaining, sizeof(hintsRemaining));
    
    file.close();
    cout << "Game saved successfully to " << filename << endl;
}

bool Sudoku::loadGame(const char* filename) {
    ifstream file(filename, ios::binary);
    
    if (!file.is_open()) {
        cout << "Error: Could not open file for loading" << endl;
        return false;
    }
    
    
    file.read((char*)&gridSize, sizeof(gridSize));
    
    
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            file.read((char*)&board[i][j], sizeof(board[i][j]));
        }
    }
    
    
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            file.read((char*)&originalBoard[i][j], sizeof(originalBoard[i][j]));
        }
    }
    
    
    file.read((char*)&moveCount, sizeof(moveCount));
    for (int i = 0; i < moveCount; i++) {
        file.read((char*)&moveRow[i], sizeof(moveRow[i]));
        file.read((char*)&moveCol[i], sizeof(moveCol[i]));
        file.read((char*)&moveValue[i], sizeof(moveValue[i]));
    }
    
    
    file.read((char*)&playerName, sizeof(playerName));
    file.read((char*)&score, sizeof(score));
    
    
    file.read((char*)&hintsUsed, sizeof(hintsUsed));
    file.read((char*)&hintsRemaining, sizeof(hintsRemaining));
    
    file.close();
    cout << "Game loaded successfully from " << filename << endl;
    return true;
}

void Sudoku::showHint() {
    if (hintsRemaining <= 0) {
        cout << "You have no hints remaining!" << endl;
        return;
    }

    
    int emptyCount = 0;
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            if (board[i][j] == 0) {
                emptyCount++;
            }
        }
    }
    
    if (emptyCount == 0) {
        cout << "No empty cells to give a hint for!" << endl;
        return;
    }
    
    int targetCell = rand() % emptyCount;
    int row = -1, col = -1;
    
    
    int count = 0;
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            if (board[i][j] == 0) {
                if (count == targetCell) {
                    row = i;
                    col = j;
                    break;
                }
                count++;
            }
        }
        if (row != -1) break;
    }
    
    
    cout << "Hint: The cell at row " << (row+1) << ", column " << (col+1) << " should contain " 
         << originalBoard[row][col] << endl;
    
    
    updateScore(-5);
    hintsUsed++;
    hintsRemaining--;
    cout << "Using a hint costs 5 points. Hints remaining: " << hintsRemaining << endl;
}

void Sudoku::resetPuzzle() {
    
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            if (originalBoard[i][j] == 0) {
                board[i][j] = 0;
            } else {
                board[i][j] = originalBoard[i][j];
            }
        }
    }
    
    
    moveCount = 0;
    
    
    score = 0;
    
    
    int emptyCells = 0;
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            if (originalBoard[i][j] == 0) {
                emptyCells++;
            }
        }
    }
    
    int difficulty;
    if (emptyCells <= 30) difficulty = 1; 
    else if (emptyCells <= 40) difficulty = 2; 
    else if (emptyCells <= 50) difficulty = 3; 
    else difficulty = 4; 
    
    resetHints(difficulty);
    
    cout << "Puzzle has been reset to its initial state" << endl;
}

void Sudoku::setPlayerName(const char* name) {
    strncpy(playerName, name, sizeof(playerName) - 1);
    playerName[sizeof(playerName) - 1] = '\0'; 
}

const char* Sudoku::getPlayerName() const {
    return playerName;
}

void Sudoku::updateScore(int points) {
    score += points;
    if (score < 0) score = 0;
}

int Sudoku::getScore() const {
    return score;
}

void Sudoku::showGameStats() {
    cout << "\n===== Game Statistics =====" << endl;
    cout << "Player: " << playerName << endl;
    cout << "Score: " << score << " points" << endl;
    cout << "Moves made: " << moveCount << endl;
    cout << "Hints used: " << hintsUsed << endl;
    cout << "Hints remaining: " << hintsRemaining << endl;
    
    
    int filledCells = 0;
    int totalNonOriginalCells = 0;
    
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            if (originalBoard[i][j] == 0) {
                totalNonOriginalCells++;
                if (board[i][j] != 0) {
                    filledCells++;
                }
            }
        }
    }
    
    double completionPercentage = 0;
    if (totalNonOriginalCells > 0) {
        completionPercentage = (filledCells * 100.0) / totalNonOriginalCells;
    }
    
    cout << "Completion: " << completionPercentage << "%" << endl;
    cout << "===========================" << endl;
}



bool Sudoku::getSingleCellCandidates(int row, int col, bool candidates[MAX_SIZE+1]) {
    if (board[row][col] != 0) {
        
        for (int i = 1; i <= gridSize; i++) {
            candidates[i] = false;
        }
        return false;
    }
    
    
    for (int i = 1; i <= gridSize; i++) {
        candidates[i] = true;
    }
    
    
    for (int j = 0; j < gridSize; j++) {
        if (board[row][j] != 0) {
            candidates[board[row][j]] = false;
        }
    }
    
    
    for (int i = 0; i < gridSize; i++) {
        if (board[i][col] != 0) {
            candidates[board[i][col]] = false;
        }
    }
    
    
    int boxSize = sqrt(gridSize);
    int boxRow = row - row % boxSize;
    int boxCol = col - col % boxSize;
    
    for (int i = boxRow; i < boxRow + boxSize; i++) {
        for (int j = boxCol; j < boxCol + boxSize; j++) {
            if (board[i][j] != 0) {
                candidates[board[i][j]] = false;
            }
        }
    }
    
    
    int validCount = 0;
    for (int i = 1; i <= gridSize; i++) {
        if (candidates[i]) {
            validCount++;
        }
    }
    
    return (validCount > 0);
}

void Sudoku::showCellCandidates(int row, int col) {
    if (hintsRemaining <= 0) {
        cout << "You have no hints remaining!" << endl;
        return;
    }
    
    if (row < 0 || row >= gridSize || col < 0 || col >= gridSize) {
        cout << "Invalid cell coordinates!" << endl;
        return;
    }
    
    if (board[row][col] != 0) {
        cout << "Cell at row " << (row+1) << ", column " << (col+1) 
             << " is already filled with " << board[row][col] << endl;
        return;
    }
    
    bool candidates[MAX_SIZE+1];
    bool hasCandidates = getSingleCellCandidates(row, col, candidates);
    
    if (!hasCandidates) {
        cout << "No valid candidates for cell at row " << (row+1) << ", column " << (col+1) << endl;
        return;
    }
    
    cout << "Possible values for cell at row " << (row+1) << ", column " << (col+1) << ": ";
    for (int i = 1; i <= gridSize; i++) {
        if (candidates[i]) {
            cout << i << " ";
        }
    }
    cout << endl;
    
    hintsUsed++;
    hintsRemaining--;
    updateScore(-3); 
    cout << "Using candidate hint costs 3 points. Hints remaining: " << hintsRemaining << endl;
}

void Sudoku::findNakedSingles(int& row, int& col, int& value) {
    row = col = value = -1;
    
    for (int i = 0; i < gridSize && row == -1; i++) {
        for (int j = 0; j < gridSize && row == -1; j++) {
            if (board[i][j] == 0) {
                bool candidates[MAX_SIZE+1];
                getSingleCellCandidates(i, j, candidates);
                
                int singleValue = -1;
                int candidateCount = 0;
                
                for (int v = 1; v <= gridSize; v++) {
                    if (candidates[v]) {
                        singleValue = v;
                        candidateCount++;
                    }
                }
                
                if (candidateCount == 1) {
                    row = i;
                    col = j;
                    value = singleValue;
                }
            }
        }
    }
}

void Sudoku::findHiddenSingles(int& row, int& col, int& value) {
    row = col = value = -1;
    
    
    for (int i = 0; i < gridSize && row == -1; i++) {
        int valueCounts[MAX_SIZE+1] = {0}; 
        int valuePositions[MAX_SIZE+1][2]; 
        
        for (int j = 0; j < gridSize; j++) {
            if (board[i][j] == 0) {
                bool candidates[MAX_SIZE+1];
                getSingleCellCandidates(i, j, candidates);
                
                for (int v = 1; v <= gridSize; v++) {
                    if (candidates[v]) {
                        valueCounts[v]++;
                        valuePositions[v][0] = i;
                        valuePositions[v][1] = j;
                    }
                }
            }
        }
        
        
        for (int v = 1; v <= gridSize; v++) {
            if (valueCounts[v] == 1) {
                row = valuePositions[v][0];
                col = valuePositions[v][1];
                value = v;
                return;
            }
        }
    }
    
    
    for (int j = 0; j < gridSize && row == -1; j++) {
        int valueCounts[MAX_SIZE+1] = {0};
        int valuePositions[MAX_SIZE+1][2];
        
        for (int i = 0; i < gridSize; i++) {
            if (board[i][j] == 0) {
                bool candidates[MAX_SIZE+1];
                getSingleCellCandidates(i, j, candidates);
                
                for (int v = 1; v <= gridSize; v++) {
                    if (candidates[v]) {
                        valueCounts[v]++;
                        valuePositions[v][0] = i;
                        valuePositions[v][1] = j;
                    }
                }
            }
        }
        
        for (int v = 1; v <= gridSize; v++) {
            if (valueCounts[v] == 1) {
                row = valuePositions[v][0];
                col = valuePositions[v][1];
                value = v;
                return;
            }
        }
    }
    
    
    int boxSize = sqrt(gridSize);
    for (int boxRow = 0; boxRow < gridSize && row == -1; boxRow += boxSize) {
        for (int boxCol = 0; boxCol < gridSize && row == -1; boxCol += boxSize) {
            int valueCounts[MAX_SIZE+1] = {0};
            int valuePositions[MAX_SIZE+1][2];
            
            for (int i = boxRow; i < boxRow + boxSize; i++) {
                for (int j = boxCol; j < boxCol + boxSize; j++) {
                    if (board[i][j] == 0) {
                        bool candidates[MAX_SIZE+1];
                        getSingleCellCandidates(i, j, candidates);
                        
                        for (int v = 1; v <= gridSize; v++) {
                            if (candidates[v]) {
                                valueCounts[v]++;
                                valuePositions[v][0] = i;
                                valuePositions[v][1] = j;
                            }
                        }
                    }
                }
            }
            
            for (int v = 1; v <= gridSize; v++) {
                if (valueCounts[v] == 1) {
                    row = valuePositions[v][0];
                    col = valuePositions[v][1];
                    value = v;
                    return;
                }
            }
        }
    }
}

void Sudoku::showNextLogicalMove() {
    if (hintsRemaining <= 0) {
        cout << "You have no hints remaining!" << endl;
        return;
    }
    
    int row, col, value;
    
    
    findNakedSingles(row, col, value);
    
    
    if (row == -1) {
        findHiddenSingles(row, col, value);
    }
    
    if (row != -1) {
        cout << "Logical move: Place " << value << " at row " << (row+1) << ", column " << (col+1) << endl;
        cout << "Reasoning: This is the only valid placement based on Sudoku rules." << endl;
    } else {
        
        showHint();
        return;
    }
    
    hintsUsed++;
    hintsRemaining--;
    updateScore(-7); 
    cout << "Using logical move hint costs 7 points. Hints remaining: " << hintsRemaining << endl;
}

void Sudoku::showTargetedHint() {
    if (hintsRemaining <= 0) {
        cout << "You have no hints remaining!" << endl;
        return;
    }
    
    cout << "Enter the row and column for the cell you want a hint for:" << endl;
    int row, col;
    cout << "Row (1-9): ";
    cin >> row;
    cout << "Column (1-9): ";
    cin >> col;
    
    
    row--;
    col--;
    
    if (row < 0 || row >= gridSize || col < 0 || col >= gridSize) {
        cout << "Invalid cell coordinates!" << endl;
        return;
    }
    
    if (board[row][col] != 0) {
        cout << "Cell already contains " << board[row][col] << endl;
        return;
    }
    
    
    cout << "Hint: The cell at row " << (row+1) << ", column " << (col+1) 
         << " should contain " << originalBoard[row][col] << endl;
    
    hintsUsed++;
    hintsRemaining--;
    updateScore(-5);
    cout << "Using targeted hint costs 5 points. Hints remaining: " << hintsRemaining << endl;
}

int Sudoku::getHintsRemaining() const {
    return hintsRemaining;
}

int Sudoku::getHintsUsed() const {
    return hintsUsed;
}

void Sudoku::resetHints(int difficulty) {
    
    switch (difficulty) {
        case 1: 
            hintsRemaining = 5;
            break;
        case 2: 
            hintsRemaining = 4;
            break;
        case 3: 
            hintsRemaining = 3;
            break;
        case 4: 
            hintsRemaining = 2;
            break;
        default:
            hintsRemaining = 3;
    }
    
    hintsUsed = 0;
} 
