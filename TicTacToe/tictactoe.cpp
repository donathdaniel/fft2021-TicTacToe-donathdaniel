#include "tictactoe.h"
#include "ui_tictactoe.h"

TicTacToe::TicTacToe(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TicTacToe)
{
    ui->setupUi(this);

    //structure and design made in the XML
    //make connection every button of the grid layout
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

    //design for the message box, this pop out when the gam is over
    msg.setStyleSheet("background-color: #1f4287;"
                        "color: #21E6C1;"
                        "font-size: 16px;"
                        "font-weight: bold;"
                        "font-style: italic;");

    connect(this,SIGNAL(gameChanged()),this,SLOT(winner()));

}

TicTacToe::~TicTacToe()
{
    delete ui;
}

void TicTacToe::on_reset_clicked()
{
    //setting the game in default condition(when we press the reset button)
    clickCounter=0;
   for(int i=0;i<9;++i){
        clickedButtons[i]=0;
        buttonArray[i]->setText("");
        buttonArray[i]->setEnabled(true);
    }
}

void TicTacToe::whichButton()
{
    //defining which button sent the signal
    QPushButton *qpushButton = (QPushButton *)sender();
    QString button=qpushButton->objectName();
    QString buttonInt=button.mid(1,button.length());

    //choosing the player turn
    int playerW=playerTurn(buttonInt.toInt());

    //setting the symbol for the button
    playerW==1 ? qpushButton->setText("X") : qpushButton->setText("O");
    qpushButton->setEnabled(false);

    //every time we check that the game is over
    emit gameChanged();
}

int TicTacToe::playerTurn(int buttonIndex)
{
    clickCounter++;

    //defining that which player is coming
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
    if(weHaveWinner(1)){//checking that the first player win the game
        finalMessage(1);
    }
    else if(weHaveWinner(2)){//checking that the second player win the game
        finalMessage(2);
    }
    else{//checking that the game is finished with tie
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
    //setting the properties of the messagebox in case of victory
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
    //setting the properties of the messagebox in case of draw
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
    //the logic of the game
    //checking all the possibiliy for the victory
    bool winningCombination=true;
    for(int i=0;i<8;++i){
        for(int j=0;j<3;++j){
            if(clickedButtons[winCombinations[i][j]]!=player){
                winningCombination=false;
                break;
            }
        }
        if(winningCombination){
            return true;
        }
        winningCombination=true;
    }
    return false;
}

