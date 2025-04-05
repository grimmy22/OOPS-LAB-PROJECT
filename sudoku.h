#ifndef SUDOKU_H
#define SUDOKU_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <fstream>

#define MAX_SIZE 9
#define MAX_MOVES 100 // Maximum number of moves to store

class Sudoku {
private:
    int gridSize;
    int board[MAX_SIZE][MAX_SIZE];
    int originalBoard[MAX_SIZE][MAX_SIZE]; // Store original puzzle
    
    // Move history using arrays instead of vector
    int moveRow[MAX_MOVES];
    int moveCol[MAX_MOVES];
    int moveValue[MAX_MOVES];
    int moveCount;
    
    char playerName[50];
    int score;
    int hintsUsed;
    int hintsRemaining;
    
    bool isValidPlacement(int row, int col, int num);
    bool solveSudoku();
    void fillDiagonal();
    void fillBox(int row, int col);
    bool fillRemaining(int row, int col);
    void removeDigits(int difficulty);
    
    // New hint system related private methods
    bool getSingleCellCandidates(int row, int col, bool candidates[MAX_SIZE+1]);
    void findNakedSingles(int& row, int& col, int& value);
    void findHiddenSingles(int& row, int& col, int& value);

public:
    Sudoku();
    void generatePuzzle(int difficulty);
    void printBoard();
    void printBoardWithHints();
    int getGridSize() { return gridSize; }
    void setCellValue(int row, int col, int value);
    bool isSolved();
    bool isValidMove(int row, int col, int num);
    bool isOriginalCell(int row, int col);
    
    // Improved features
    void undoMove();
    void saveGame(const char* filename);
    bool loadGame(const char* filename);
    void showHint();
    void resetPuzzle();
    void setPlayerName(const char* name);
    const char* getPlayerName() const;
    void updateScore(int points);
    int getScore() const;
    void showGameStats();
    
    // New hint system methods
    void showTargetedHint();
    void showCellCandidates(int row, int col);
    void showNextLogicalMove();
    int getHintsRemaining() const;
    int getHintsUsed() const;
    void resetHints(int difficulty);
};

#endif 