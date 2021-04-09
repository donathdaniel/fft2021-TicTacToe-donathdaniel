#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <QMainWindow>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class TicTacToe; }
QT_END_NAMESPACE

class TicTacToe : public QMainWindow
{
    Q_OBJECT

public:
    TicTacToe(QWidget *parent = nullptr);
    ~TicTacToe();

private slots:
    void on_reset_clicked();
    void whichButton();
    int playerTurn(int buttonIndex);
    void winner();
    void finalMessage(int player);
    void finalMessageTie();
    bool weHaveWinner(int player);

signals:
    void gameChanged();

private:
    Ui::TicTacToe *ui;
    QMessageBox msg;
    QPushButton* buttonArray[9];
    int clickCounter=0;
    int clickedButtons[9]={0,0,0,0,0,0,0,0,0};

    //winCombinations stores all the possibilities for victory
    int winCombinations[8][3]={{0,1,2},
                               {3,4,5},
                               {6,7,8},
                               {0,3,6},
                               {1,4,7},
                               {2,5,8},
                               {0,4,8},
                               {2,4,6}
    };
};
#endif // TICTACTOE_H

