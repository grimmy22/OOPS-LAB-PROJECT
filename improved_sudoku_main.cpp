#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <fstream>
#include "sudoku.h"

using namespace std;

void displayTitle() {
    cout << "\n==============================================" << endl;
    cout << "***************  SUDOKI GAME  ***************" << endl;
    cout << "==============================================" << endl;
    cout << "                                             " << endl;
    cout << "  DEVELOPED BY:                              " << endl;
    cout << "  * JAIVARDHAN SINGH CHAUHAN (24BIT0239)     " << endl;
    cout << "  * ATHARVA JAY PHALAK (24BIT0244)           " << endl;
    cout << "  * ARAHAT NARESH GAIKWAD (24BYB0182)        " << endl;
    cout << "                                             " << endl;
    cout << "==============================================" << endl;
}

void displayMenu() {
    cout << "\n==============================================" << endl;
    cout << "                 MAIN MENU                   " << endl;
    cout << "==============================================" << endl;
    cout << "  1. > Start New Game                        " << endl;
    cout << "  2. > Load Saved Game                       " << endl;
    cout << "  3. > How to Play                           " << endl;
    cout << "  4. > Exit                                  " << endl;
    cout << "==============================================" << endl;
    cout << "Enter your choice: ";
}

void displayGameMenu() {
    cout << "\n==============================================" << endl;
    cout << "                 GAME MENU                   " << endl;
    cout << "==============================================" << endl;
    cout << "  1. > Make a Move                           " << endl;
    cout << "  2. > Undo Last Move                        " << endl;
    cout << "  3. > Hints Menu                            " << endl;
    cout << "  4. > Show Statistics                       " << endl;
    cout << "  5. > Save Game                             " << endl;
    cout << "  6. > Reset Puzzle                          " << endl;
    cout << "  7. > Show Board with Hints                 " << endl;
    cout << "  8. > Return to Main Menu                   " << endl;
    cout << "==============================================" << endl;
    cout << "Enter your choice: ";
}

void displayHintMenu() {
    cout << "\n==============================================" << endl;
    cout << "                 HINT MENU                   " << endl;
    cout << "==============================================" << endl;
    cout << "  1. > Random Cell Hint (-5 points)          " << endl;
    cout << "  2. > Targeted Cell Hint (-5 points)        " << endl;
    cout << "  3. > Show Possible Values (-3 points)      " << endl;
    cout << "  4. > Show Next Logical Move (-7 points)    " << endl;
    cout << "  5. > Return to Game Menu                   " << endl;
    cout << "==============================================" << endl;
    cout << "Enter your choice: ";
}

void displayHowToPlay() {
    cout << "\n==============================================" << endl;
    cout << "               HOW TO PLAY                   " << endl;
    cout << "==============================================" << endl;
    cout << " * The goal is to fill the 9x9 grid so that each" << endl;
    cout << "   row, column, and 3x3 box contains digits 1-9" << endl;
    cout << "   without repetition." << endl;
    cout << "                                             " << endl;
    cout << " * You will be scored based on correct placements." << endl;
    cout << "                                             " << endl;
    cout << " * Incorrect placements won't be penalized, but" << endl;
    cout << "   using hints will reduce your score." << endl;
    cout << "                                             " << endl;
    cout << " * Original cells (marked with *) cannot be modified." << endl;
    cout << "                                             " << endl;
    cout << " * You can save your game and continue later." << endl;
    cout << "                                             " << endl;
    cout << " * The game is complete when all cells are filled" << endl;
    cout << "   correctly." << endl;
    cout << "==============================================" << endl;
    cout << "               HINT SYSTEM                   " << endl;
    cout << "==============================================" << endl;
    cout << " * Available hints based on difficulty:" << endl;
    cout << "   Easy: 5 hints" << endl;
    cout << "   Medium: 4 hints" << endl;
    cout << "   Hard: 3 hints" << endl;
    cout << "   Expert: 2 hints" << endl;
    cout << "                                             " << endl;
    cout << " * Types of Hints:" << endl;
    cout << "   1. Random Cell Hint (-5 points)" << endl;
    cout << "   2. Targeted Cell Hint (-5 points)" << endl;
    cout << "   3. Possible Values (-3 points)" << endl;
    cout << "   4. Logical Move (-7 points)" << endl;
    cout << "==============================================" << endl;
    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();
}

void playGame(Sudoku& game) {
    bool exitGame = false;
    
    while (!exitGame) {
        
        system("cls");
        displayTitle();
        game.printBoard();
        
        
        if (game.isSolved()) {
            cout << "\n==============================================" << endl;
            cout << "                                             " << endl;
            cout << "     *** CONGRATULATIONS! PUZZLE SOLVED! ***  " << endl;
            cout << "                                             " << endl;
            cout << "==============================================" << endl;
            
            
            game.updateScore(100);
            game.showGameStats();
            
            cout << "\nPress Enter to return to main menu...";
            cin.ignore();
            cin.get();
            return;
        }
        
        displayGameMenu();
        int choice;
        cin >> choice;
        
        switch (choice) {
            case 1: {  
                int row, col, value;
                cout << "Enter row (1-9): ";
                cin >> row;
                cout << "Enter column (1-9): ";
                cin >> col;
                cout << "Enter value (1-9): ";
                cin >> value;
                
                
                row--;
                col--;
                
                if (row < 0 || row >= game.getGridSize() || col < 0 || col >= game.getGridSize() || 
                    value < 1 || value > game.getGridSize()) {
                    cout << "Invalid input! Row and column must be between 1 and 9, value between 1 and 9." << endl;
                    cout << "Press Enter to continue...";
                    cin.ignore();
                    cin.get();
                    continue;
                }
                
                if (!game.isValidMove(row, col, value)) {
                    cout << "This move violates Sudoku rules! The number already exists in the row, column, or 3x3 box." << endl;
                    cout << "Press Enter to continue...";
                    cin.ignore();
                    cin.get();
                    continue;
                }
                
                game.setCellValue(row, col, value);
                break;
            }
            case 2:  
                game.undoMove();
                cout << "Press Enter to continue...";
                cin.ignore();
                cin.get();
                break;
            case 3: {  
                bool exitHintMenu = false;
                
                while (!exitHintMenu) {
                    system("cls");
                    displayTitle();
                    game.printBoard();
                    
                    displayHintMenu();
                    int hintChoice;
                    cin >> hintChoice;
                    
                    switch (hintChoice) {
                        case 1:  
                            game.showHint();
                            cout << "Press Enter to continue...";
                            cin.ignore();
                            cin.get();
                            break;
                        case 2:  
                            game.showTargetedHint();
                            cout << "Press Enter to continue...";
                            cin.ignore();
                            cin.get();
                            break;
                        case 3: { 
                            int row, col;
                            cout << "Enter row (1-9): ";
                            cin >> row;
                            cout << "Enter column (1-9): ";
                            cin >> col;
                            
                            
                            row--;
                            col--;
                            
                            game.showCellCandidates(row, col);
                            cout << "Press Enter to continue...";
                            cin.ignore();
                            cin.get();
                            break;
                        }
                        case 4:  
                            game.showNextLogicalMove();
                            cout << "Press Enter to continue...";
                            cin.ignore();
                            cin.get();
                            break;
                        case 5:  
                            exitHintMenu = true;
                            break;
                        default:
                            cout << "Invalid choice! Please try again." << endl;
                            cout << "Press Enter to continue...";
                            cin.ignore();
                            cin.get();
                    }
                }
                break;
            }
            case 4:  
                game.showGameStats();
                cout << "Press Enter to continue...";
                cin.ignore();
                cin.get();
                break;
            case 5: {  
                char filename[100];
                cout << "Enter filename to save (without extension): ";
                cin >> filename;
                strcat(filename, ".sav");
                game.saveGame(filename);
                cout << "Press Enter to continue...";
                cin.ignore();
                cin.get();
                break;
            }
            case 6:  
                game.resetPuzzle();
                cout << "Press Enter to continue...";
                cin.ignore();
                cin.get();
                break;
            case 7:  
                system("cls");
                displayTitle();
                game.printBoardWithHints();
                cout << "Press Enter to continue...";
                cin.ignore();
                cin.get();
                break;
            case 8:  
                exitGame = true;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
                cout << "Press Enter to continue...";
                cin.ignore();
                cin.get();
        }
    }
}

int main() {
    srand(time(0));
    
    bool exitProgram = false;
    Sudoku game;
    
    while (!exitProgram) {
        system("cls");
        displayTitle();
        displayMenu();
        
        int choice;
        cin >> choice;
        
        switch (choice) {
            case 1: {  
                system("cls");
                displayTitle();
                
                char name[50];
                cout << "Enter your name: ";
                cin.ignore();
                cin.getline(name, 50);
                game.setPlayerName(name);
                
                int difficulty;
                cout << "\nSelect difficulty level:" << endl;
                cout << "1 - Easy" << endl;
                cout << "2 - Medium" << endl;
                cout << "3 - Hard" << endl;
                cout << "4 - Expert" << endl;
                cout << "Enter your choice (1-4): ";
                cin >> difficulty;
                
                if (difficulty < 1 || difficulty > 4) {
                    cout << "Invalid choice! Defaulting to Easy difficulty." << endl;
                    difficulty = 1;
                }
                
                string difficultyText;
                switch (difficulty) {
                    case 1: difficultyText = "Easy"; break;
                    case 2: difficultyText = "Medium"; break;
                    case 3: difficultyText = "Hard"; break;
                    case 4: difficultyText = "Expert"; break;
                }
                
                cout << "\nGenerating " << difficultyText << " puzzle..." << endl;
                game.generatePuzzle(difficulty);
                
                playGame(game);
                break;
            }
            case 2: {  
                char filename[100];
                cout << "Enter filename to load (without extension): ";
                cin >> filename;
                strcat(filename, ".sav");
                
                if (game.loadGame(filename)) {
                    playGame(game);
                } else {
                    cout << "Press Enter to continue...";
                    cin.ignore();
                    cin.get();
                }
                break;
            }
            case 3:  
                displayHowToPlay();
                break;
            case 4:  
                exitProgram = true;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
                cout << "Press Enter to continue...";
                cin.ignore();
                cin.get();
        }
    }
    
    cout << "\n==============================================" << endl;
    cout << "                                             " << endl;
    cout << "               GAME FINISHED                 " << endl;
    cout << "                                             " << endl;
    cout << "==============================================" << endl;
    cout << "     Thank you for playing Sudoki Game!      " << endl;
    cout << "                                             " << endl;
    cout << "==============================================" << endl;
    
    return 0;
} 