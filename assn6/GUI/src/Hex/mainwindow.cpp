#include <QSignalMapper>
#include <QGridLayout>
#include <QTimer>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"

MainWindow::MainWindow(QWidget *parent) :  QMainWindow(parent), ui(new Ui::MainWindow), board(11) {
    ui->setupUi(this);

    // Player always goes first.
    player = "BLACK";

    QSignalMapper *signalMapper = new QSignalMapper(this);

    QWidget *mainWidget = new QWidget(this);
    QWidget *boardWidget = new QWidget(mainWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(mainWidget);
    setCentralWidget(mainWidget);

    QWidget *topWidget = new QWidget(mainWidget);
    mainLayout->addWidget(topWidget);
    QHBoxLayout *topLayout = new QHBoxLayout(topWidget);
    topLayout->setSpacing(0);

    labelCurrent = new QLabel(topWidget);
    labelCurrent->setText("Current player: " + player);
    labelCurrent->setMaximumSize(250,20);
    labelCurrent->setAlignment(Qt::AlignCenter);
    labelCurrent->setStyleSheet("QLabel { background-color : #4f5049; color : #ffffff; }");
    topLayout->addWidget(labelCurrent);

    QGridLayout *boardLayout = new QGridLayout(boardWidget);
    mainLayout->addWidget(boardWidget);

    QString state = "x";
    MainWindow::size = 11;

    boardLayout->setSpacing(0);
    boardLayout->setContentsMargins(50,50,50,50);
    boardWidget->setFixedHeight(350);

    // Creates 2D array of buttons determined by the size var.
    for(int i = 0; i < size; ++i) {
        for(int j= 0; j < size; ++j) {
            // Creates a new flat button with the specificed size.
            button[i][j] = new QPushButton(state, this);
            button[i][j]->setMaximumSize(20, 20);
            button[i][j]->setFlat(true);
            QString cell = QString::number(i + 1) + ", " +  QString::number(j + 1);
            boardLayout->addWidget(button[i][j],i,j);

            signalMapper->setMapping(button[i][j], cell);
            // Maps the signal to map slot.
            connect(button[i][j], SIGNAL(clicked()), signalMapper, SLOT(map()));
        }
    }
    QWidget *bottomWidget = new QWidget(mainWidget);
    mainLayout->addWidget(bottomWidget);

    QHBoxLayout *bottomLayout = new QHBoxLayout(bottomWidget);
    bottomWidget->setContentsMargins(20, 20,20,20);

    message = new QLabel(bottomWidget);
    message->setText("Please wait while AI calculates best move...");
    message->setStyleSheet("QLabel { background-color : #4f5049; color : #E97F02; }");
    message->setAlignment(Qt::AlignCenter);

    bottomLayout->addWidget(message);
    message->hide();
    // Connects the QSignalMapper map() signal to the method on_pushButton_clicked()
    connect(signalMapper, SIGNAL(mapped(QString)), this, SLOT(on_pushButton_clicked(QString)) );

    setLayout(mainLayout);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::do_ai_move() {

    // Ai's turn
    AI ai(board);
    int ai_move = ai.getBestMove();
    int ai_row = ai_move / 11;
    int ai_col = ai_move % 11;
    board.is_valid_entry(ai_row, ai_col, player.toStdString().c_str());

    // Change chosen button to white image.
    this->button[ai_row][ai_col]->setIcon(QIcon(":/images/white.png"));
    this->button[ai_row][ai_col]->setIconSize(QSize(15,15));
    this->button[ai_row][ai_col]->setText("");

    // Disables the button after it has been clicked.
    this->button[ai_row][ai_col]->setEnabled(false);
    if(board.get_winner() != "") {
        Dialog *won = new Dialog(this);
        won->winning_player(player);
    }
    player = (player == "BLACK") ? "WHITE" : "BLACK";
    labelCurrent->setText("Current player: " + player);
    message->hide();
}

void MainWindow::on_pushButton_clicked(QString cell) {
    // Cell contains index for this button (row,col). Splits the string into
    // a list of strings and finally converted to integers to be used
    // to mark the node in the graph representation.
    QStringList index = cell.split(",");
    int row = index.at(0).toInt() - 1;
    int col = index.at(1).toInt() - 1;

    // Player's turn
    board.is_valid_entry(row, col, player.toStdString().c_str());
    // Change the button to a black image.
    this->button[row][col]->setIcon(QIcon(":/images/black.png"));
    this->button[row][col]->setIconSize(QSize(15,15));
    this->button[row][col]->setText("");

    // Disables the button the Player chose after it has been clicked.
    this->button[row][col]->setEnabled(false);
    if(board.get_winner() != "") {
        Dialog *won = new Dialog(this);
        won->winning_player(player);
     }
     // Switch to player AI
     player = (player == "BLACK") ? "WHITE" : "BLACK";

    // Wait before executing AI move in order to allow the button clicked to be
    // updated first.
    labelCurrent->setText("Current player: " + player);
    message->show();
    QTimer::singleShot(50, this, SLOT(do_ai_move()));
}

