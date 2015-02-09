#include "mainwindow.h"
#include <QApplication>
#include "dialog.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.move(300,300);
    a.processEvents(QEventLoop::ExcludeUserInputEvents);
    w.setFixedSize(500,500);
    w.setWindowTitle(QString::fromUtf8("Game of Hex"));
    w.show();

    // Welcome dialog box
    Dialog *welcomeMsg = new Dialog();
    welcomeMsg->welcome();
    return a.exec();
}
