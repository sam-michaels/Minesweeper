/*
 * Name: Samuel Michaels Rodriguez
 * Date: Feb. 6 2024
 * This is a header file used for the mainwindow cpp file. It stores all the variables, and functions used
 * for the code to function properly.
 * It includes various 'include' statements, that give the class the ability to implement the task.
*/

#include <QMainWindow>
#include <QApplication>
#include "GameButton.h" //handles the buttons used as the spaces
#include "dialog.h"     //handles the popup window
#include <QGridLayout>
#include <QMessageBox>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);  //constructor
    ~MainWindow();                          //deconstructor

private:

    bool mineField[16][30] = {false};   // array that will store true if a mine is present
    bool revealed[16][30] = {false};    // array that will store true if the space ahs already been revealed
    bool flagged[16][30] = {false};     // array that will store true if the space has been flagged

    QWidget *centralWidget;             // creates the main window where all the buttons will be added
    QGridLayout *gridLayout;            // helps layout the buttons that will be added to the widget
    GameButton ***buttons;              // 2D array of buttons
    Dialog *popup;                      // the popup used when a bomb is selected

    const int rows = 16;                // max rows of the board
    const int cols = 30;                // max cols of the board
    const int maxMines = 99;            // max mines for the board
    const int maxFlags = 99;            // max flags for the board

    int mineCol;            // used to pick a space on the grid
    int mineRow;
    int mineCount;          //will keep track of how many mines are selected
    int flagCount;          // keep track of how many flags have been placed

    void openSpace(int row, int col);       // function to handle space opening
    void toggleFlag(int row, int col);      // function to handle flagging
    void initializeMineField();             // will mimic the mine field and carry data on if the space has a mine or not
    void revealMines(int row, int col);     // will reveal the mine field
    int checkMines(int row, int col);       // handles checking how many mines are in adjacent spaces
    bool isValidSpace(int row, int col);    // checks to see if the space is valid
    void revealSpace(int row, int col);     // recursively checks space and nearby spaces
    void markAllEmpty();                    // sets the number of mines surrounding as a text item on the button
    void clearFlag(int row, int col);       // handles when a flag is flagged again
    void closeApp();                        // exits the app
    void resetBoard();                      // resets the board to restart the game

    void resetFlagged();                    // reinitializes the flagged array
    void resetRevealed();                   // reinitializes the revealed array
    void resetMineField();                  // reinitializes the mineField array

    bool playerWin();                       // function to let the player know they won, and will close the app automatically
};
