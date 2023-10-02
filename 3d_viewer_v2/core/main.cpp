#include "../view/mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    setlocale(LC_NUMERIC, "C");
    return a.exec();
}
