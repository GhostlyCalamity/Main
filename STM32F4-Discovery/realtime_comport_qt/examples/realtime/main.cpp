#include <qapplication.h>
#include "mainwindow.h"
int g_size=1000;
int main( int argc, char **argv )
{
    QApplication a( argc, argv );

    MainWindow w;
    w.show();

    return a.exec();
}
