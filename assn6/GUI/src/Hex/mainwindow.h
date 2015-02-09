#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include "board.h"
#include "ai.h"

// Board supports up to a size of 100x100
const int MAX_SIZE = 100;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QWidget *myWidget;
    QPushButton *button[MAX_SIZE][MAX_SIZE];
    friend class AI;

private slots:
    void on_pushButton_clicked(QString);
    void do_ai_move();


private:
    Ui::MainWindow *ui;
    QString player;
    QLabel *labelCurrent;
    QLabel *message;

    Board board;
    int size;

};

#endif // MAINWINDOW_H
