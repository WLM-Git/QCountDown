#include <QApplication>
#include <QWidget>
#include "windowwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    WindowWidget window;
    window.show();

    return a.exec(); // 开启 GUI 事件循环
}
