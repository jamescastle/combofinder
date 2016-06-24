#include <QApplication>
#include "dsofinder.h"

//THIS FILE CONTAINS main()

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DsoFinder w(argc,argv);
    w.show();

    return a.exec();
}
