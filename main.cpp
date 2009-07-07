#include <QtGui/QApplication>
#include "rsrmainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RSRMainWindow w;
    QObject::connect(&w,SIGNAL(destroyed()),&a,SLOT(quit()) );
    a.connect(&a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()));
    w.show();
    return a.exec();
}













