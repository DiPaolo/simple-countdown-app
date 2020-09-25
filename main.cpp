#include "main_window.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOrganizationName("DiPaolo");
    a.setApplicationName("Simple Countdown");

    Widget w;
    w.show();
    return a.exec();
}
