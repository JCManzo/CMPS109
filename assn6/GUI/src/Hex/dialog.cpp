#include "dialog.h"
#include "ui_dialog.h"
#include <QMessageBox>
#include <QString>
#include "mainwindow.h"
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::welcome() {
    QString welcomemsg = "Welcome to the game of Hex\n\nYou will be player BLACK\nAI is player WHITE.\n\n" \
                          "BLACK connects from top and bottom\nWHITE connects from side to side";
    QMessageBox::information(this, "Welcome", welcomemsg);
}

void Dialog::winning_player(QString player) {

    QMessageBox::information(this, "Winner", "Player " + player + " has won!\n\nRestart program to play again");

}
