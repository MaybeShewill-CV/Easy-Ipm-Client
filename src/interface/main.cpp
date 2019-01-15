#include "mainwindow.h"
#include <QApplication>
#include <QSplashScreen>
#include <QDateTime>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon("../images/app_icon.png"));

    QPixmap pixmap("../images/app_splash.png");
    QSplashScreen screen(pixmap);
    screen.show();

    QDateTime n = QDateTime::currentDateTime();
    QDateTime now;
    do {
        now = QDateTime::currentDateTime();
        a.processEvents();
    } while (n.secsTo(now) <= 2); // 2s为需要延时的秒数

    MainWindow w;
    w.setWindowTitle("MaybeShewill Ipm Platform");
    w.show();

    screen.finish(&w);

    return a.exec();
}
