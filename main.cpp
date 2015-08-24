#include "widget.h"
#include <QApplication>
#include <QFont>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFont b;
    b.setPixelSize(30);
    a.setFont(b);

    Widget w;
    w.setFixedSize(QSize(280,320));

    w.show();

    return a.exec();
}
