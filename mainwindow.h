#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <vector>


class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:

    // std::vector<std::vector<bool>> mineField;
    bool mineField[30][16];
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QPushButton ***buttons; // 2D array of buttons

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
    void revealMines();
    void checkMines(int row, int col);

};
