#include "tictactoe.h"
#include "ui_tictactoe.h"

TicTacToe::TicTacToe(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TicTacToe)
{
    ui->setupUi(this);

    buttonArray[0]=ui->p0;
    buttonArray[1]=ui->p1;
    buttonArray[2]=ui->p2;
    buttonArray[3]=ui->p3;
    buttonArray[4]=ui->p4;
    buttonArray[5]=ui->p5;
    buttonArray[6]=ui->p6;
    buttonArray[7]=ui->p7;
    buttonArray[8]=ui->p8;
    for(int i=0;i<9;++i){
        connect(buttonArray[i],SIGNAL(clicked()),this,SLOT(whichButton()));;
    }

    msg.setStyleSheet("background-color: #1f4287;"
                        "color: #21E6C1;"
                        "font-size: 16px;"
                        "font-weight: bold;"
                        "font-style: italic;");

    connect(this,SIGNAL(gameChanged()),this,SLOT(winner()));

    //QAbstractButton *button;
    //connect(msg,SIGNAL(buttonClicked(button)),this,SLOT(on_reset_clicked()));
}

TicTacToe::~TicTacToe()
{
    delete ui;
}

void TicTacToe::on_reset_clicked()
{
    clickCounter=0;
   for(int i=0;i<9;++i){
        clickedButtons[i]=0;
        buttonArray[i]->setText("");
        buttonArray[i]->setEnabled(true);
    }
}

void TicTacToe::whichButton()
{
    QPushButton *qpushButton = (QPushButton *)sender();
    QString button=qpushButton->objectName();
    QString buttonInt=button.mid(1,button.length());

    int playerW=playerTurn(buttonInt.toInt());
    playerW==1 ? qpushButton->setText("X") : qpushButton->setText("O");
    qpushButton->setEnabled(false);
    emit gameChanged();
}

int TicTacToe::playerTurn(int buttonIndex)
{
    clickCounter++;
    if(clickCounter%2){
        clickedButtons[buttonIndex]=1;
        ui->label_turn->setText("Turn: Player O!");
        return 1;
    }
    else{
        clickedButtons[buttonIndex]=2;
        ui->label_turn->setText("Turn: Player X!");
        return 2;
    }
}

void TicTacToe::winner()
{
    if(weHaveWinner(1)){
        finalMessage(1);
    }
    else if(weHaveWinner(2)){
        finalMessage(2);
    }
    else{
        int counter=0;
        for(int i=0;i<9;++i){
            counter=clickedButtons[i] ? counter+1 : counter;
        }
        if(counter==9){
            finalMessageTie();
        }
    }
}

void TicTacToe::finalMessage(int player)
{
    msg.setIcon(QMessageBox::Information);
    msg.setWindowTitle("The winner!");
    player == 1 ? msg.setText("Player X!") : msg.setText("Player O!");
    msg.show();
    for(int i=0;i<9;++i){
         buttonArray[i]->setEnabled(false);
    }
}

void TicTacToe::finalMessageTie()
{
    msg.setIcon(QMessageBox::Information);
    msg.setWindowTitle("It's a draw!");
    msg.setText("Try again!");
    msg.show();
    for(int i=0;i<9;++i){
         buttonArray[i]->setEnabled(false);
    }
}

bool TicTacToe::weHaveWinner(int player)
{
    bool winingCombination=true;
    for(int i=0;i<8;++i){
        for(int j=0;j<3;++j){
            if(clickedButtons[winCombinations[i][j]]!=player){
                winingCombination=false;
                break;
            }
        }
        if(winingCombination){
            return true;
        }
        winingCombination=true;
    }
    return false;
}

