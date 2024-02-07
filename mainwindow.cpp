/*
 * Name: Samuel Michaels Rodriguez
 * Date: Feb. 6 2024
 * Main file of the app. This file includes all the functions used for the game logic and initializing the main window
*/
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {

    // this initiales all the buttons, variables, and pointers to their initial state, before the game begins.
    mineCount = 0;
    flagCount = 0;
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    gridLayout = new QGridLayout(centralWidget);
    buttons = new GameButton**[rows];   // creates the buttons used for the rows
    popup = new Dialog(this);
    initializeMineField();

    for (int i = 0; i < rows; i++) {
        buttons[i] = new GameButton*[cols];     // creates the col buttons used for each row
        for (int j = 0; j < cols; j++) {
            buttons[i][j] = new GameButton(centralWidget);  // adds the buttons to the main widget (Main window)
            buttons[i][j]->setFixedSize(35, 40);
            gridLayout->addWidget(buttons[i][j], i, j);
            connect(buttons[i][j], &GameButton::clicked, this, [this, i, j] { openSpace(i, j); });  // Handles left click functionality
            connect(buttons[i][j], &GameButton::rightClicked, this, [this, i, j] { toggleFlag(i, j); }); // Handles right clicked functionality
        }
    }
    connect(popup, &Dialog::closeApp, this, &MainWindow::closeApp);     // handles the exit button on popup
    connect(popup, &Dialog::restartApp, this, &MainWindow::resetBoard); // handles the try again button on popup

}

MainWindow::~MainWindow() {

    // deconstructor for the class that will delete all buttons which were dynamically allocated
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            delete buttons[i][j];
        }
        delete[] buttons[i];
    }
    delete[] buttons;

}

void MainWindow::openSpace(int row, int col) {

    // handles when a button is left clicked
    //revealMines(row, col);
    if (mineField[row][col]) {                      // checks if the mineField has a mine allocated to that row and col
        buttons[row][col] -> setIcon(QIcon(":/images/minesweeper_icons/bomb_explode_sm.png"));      // sets the button to the exploded image of the bomb
        buttons[row][col] ->setIconSize(QSize(35,40));
        revealed[row][col] = true;                  // space is checked as revealed
        revealMines(row, col);                      // will call a function that will reveal all the mines as the user has now lost

        popup -> exec();                            // popup will appear as the user has lost
    }
    else {
        if (flagged[row][col]) {                    // checks is the user selected a flagged space
            clearFlag(row, col);                    // calls a function that will handle clearing the selected flag
        }
        revealSpace(row, col);                      // handles recursively checking adjacent spots

        if (playerWin()) {                     // checks if player has won, will exit application if true
            QCoreApplication::quit();
        }
    }
}
void MainWindow::initializeMineField() {

    // function will initialize the minefield by randomly selecting 99 different spaces to place mines in
    while (mineCount < maxMines) {

        mineCol = arc4random() % 30;        // randomly selects a number between 0 and 29
        mineRow = arc4random() % 16;        // randomly selects a number between 0 and 15

        if (!mineField[mineRow][mineCol]) { // handles if the same random spot is selected 2 times
            mineField[mineRow][mineCol] = true; //indicates that a mine is present
            mineCount++;                        // keeps track of the number of mines
        }
    }
}
void MainWindow::revealMines(int row, int col) {

    // will reveal all mines when the game is lost
    for (int i = 0; i < rows; i ++) {
        for (int j = 0; j < cols; j ++) {
            if (mineField[i][j]) {      // checks if mine is present
                if (i == row && j == col) { // reveals the mine that was selected as the exploded image of a bomb
                    buttons[i][j] -> setIcon(QIcon(":/images/minesweeper_icons/bomb_explode_sm.png"));
                    buttons[i][j] ->setIconSize(QSize(35,40));
                }
                else {                 // reveals all other mines by setting an image of a bomb
                    buttons[i][j] -> setIcon(QIcon(":/images/minesweeper_icons/bomb.png"));
                    buttons[i][j] ->setIconSize(QSize(35,40));
                }
            }
        }

    }
}
int MainWindow::checkMines(int row, int col) {

    // function that will check the 3x3 box surround the space opened
    // returns the number of mines to be used later by setting the text

    int numMines = 0;

    for (int i = row - 1; i <= row + 1; i++) {
        for (int j = col - 1; j <= col + 1; j++) {
            if (isValidSpace(i, j)) {       // checks if the space is valid by calling the function with i and j as params
                if (mineField[i][j]) {
                    numMines++;             // increments number of mines if a mine is present in the 3x3 box
                }
            }
        }
    }

    return numMines;
}
bool MainWindow::isValidSpace(int row, int col) {

    // checks if the row is between 0 and 15 and cols 0 and 29, also checks if the space has not yet been revealed
    return (row >= 0 && row < 16 && col >= 0 && col < 30 && !revealed[row][col]);
}
void MainWindow::revealSpace(int row, int col) {

    // recursive function used to check all adjacent spaces of the opened space to see if the space is empty
    // if the space is not empty, it will go check a different adjacent space

    if (!isValidSpace(row, col)) {return;}      // spcace must be valid

    revealed[row][col] = true;                  // space is marked as revealed since the space has been opened and is valid
    markAllEmpty();                             // function used to set the text/ background colour of a button depending on their value of checkMines

    if (checkMines(row, col) > 0) {return;}     // returns since space is not empty

    for (int x = - 1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
            if (x == 0 && y == 0) {continue;}
            revealSpace(row + x, col + y);    // recursively calls the function with the adjacent spaces
        }
    }
}
void MainWindow::markAllEmpty() {

    for (int i = 0; i < rows; i ++) {
        for (int j = 0; j < cols; j++) {
            if (revealed[i][j] && buttons[i][j]->text().isEmpty()) {    // checks if the button has already been revealed and has not yet been set
                if (checkMines(i, j) == 0) {
                    buttons[i][j] -> setStyleSheet("background-color : black"); // sets the background colour to black if the space is empty and there are no adjacent mines
                }
                else {
                    if (mineField[i][j]) {continue;}                            // will continue if the space is a mine to avoid bugs
                    buttons[i][j] ->setText(QString::number(checkMines(i, j))); // sets the text of the button to number of adjacent mines

                }
            }
        }
    }
}
void MainWindow:: clearFlag(int row, int col) {

    // function used to handle clearing a flag off a button
    // This function is used when the user selects a flagged button or if right clicks a previously flagged button
    if (!flagged[row][col]) {return;}

    buttons[row][col] -> setIcon(QIcon());  // clears the image
    buttons[row][col] -> setText("");       // clears the flag
    flagged[row][col] = false;
    flagCount--;                            // decrements the number of flags so user can still select 99 spaces
}
void MainWindow::toggleFlag(int row, int col) {

    // this method handles when the user right clicks a button

    if (!isValidSpace(row, col)) {return;}

    if (flagCount == maxFlags) {return;}

    if (!flagged[row][col]) {
        buttons[row][col] -> setIcon(QIcon(":/images/minesweeper_icons/mine_flag.png"));        //sets the button to an image if the button has not yet been flagged
        buttons[row][col] ->setIconSize(QSize(35,40));
        flagged[row][col] = true;
        flagCount++;
    }
    else {
        if (buttons[row][col] -> text() == "?") {   // if the button has already been flagged twice, it will clear the flag
            clearFlag(row, col);
        }
        else {
            buttons[row][col] -> setIcon(QIcon());  // removes image and sets the text to ?
            buttons[row][col] -> setText("?");
        }
    }
}
void MainWindow::closeApp() {

    // handles when the user selects exit on the popup
    QCoreApplication::quit();                       // quits the application
}

void MainWindow::resetBoard() {

    // handles when the user selects try again on the popup
    //deleting all instances of the board and resetting to initial state

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            delete buttons[i][j];
        }
        delete[] buttons[i];
    }
    delete[] buttons;

    mineCount = 0;
    flagCount = 0;
    resetFlagged();     // resets the flagged array
    resetRevealed();    // resets the revealed array
    resetMineField();   // resets the mineField array

    // reinitializing the board

    buttons = new GameButton**[rows];

    for (int i = 0; i < rows; i++) {
        buttons[i] = new GameButton*[cols];
        for (int j = 0; j < cols; j++) {
            buttons[i][j] = new GameButton(centralWidget);
            buttons[i][j]->setFixedSize(35, 40);
            gridLayout->addWidget(buttons[i][j], i, j);
            connect(buttons[i][j], &GameButton::clicked, this, [this, i, j] { openSpace(i, j); });  // Handles left click functionality
            connect(buttons[i][j], &GameButton::rightClicked, this, [this, i, j] { toggleFlag(i, j); }); // Handles right clicked functionality
        }
    }
    connect(popup, &Dialog::closeApp, this, &MainWindow::closeApp);     // handles the exit button on popup
    connect(popup, &Dialog::restartApp, this, &MainWindow::resetBoard); // handles the try again button on popup

    initializeMineField();      // reinitializes the mineField
    popup -> close();           // closes the popup

}
void MainWindow::resetFlagged() {

    // handles resetting the game by resetting the flagged array
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            flagged[i][j] = false;
        }
    }
}

void MainWindow::resetMineField() {

    // handles resetting the game by resetting the minefield array
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            mineField[i][j] = false;
        }
    }
}

void MainWindow::resetRevealed() {

    // handles resetting the game by resetting the revealed array
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            revealed[i][j] = false;
        }
    }
}

bool MainWindow::playerWin() {

    // function checks if the player has won, if not, game continues, if they have, a message will appear

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (!revealed[i][j] && !mineField[i][j]) {
                return false;
            }
        }
    }

    QMessageBox::information(this, "Congratulations!", "You've cleared the minefield!");
    return true;
}
