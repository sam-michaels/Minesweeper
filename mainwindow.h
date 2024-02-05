#include <QMainWindow>
#include "GameButton.h"
#include <QGridLayout>


class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:

    bool mineField[16][30] = {false};
    bool revealed[16][30] = {false};
    bool flagged[16][30] = {false};
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    GameButton ***buttons; // 2D array of buttons

    const int rows = 16;
    const int cols = 30;
    const int maxMines = 99;


    int mineCol;
    int mineRow;
    int mineCount;          //will keep track of how many mines are selected

    void setupGrid();
    void openSpace(int row, int col); // function to handle space opening
    void toggleFlag(int row, int col); // function to handle flagging
    void initializeMineField();        // will mimic the mine field and carry data on if the space has a mine or not
    void revealMines(int row, int col);
    int checkMines(int row, int col);
    bool isValidSpace(int row, int col);
    void revealSpace(int row, int col);
    void markAllEmpty();

};
