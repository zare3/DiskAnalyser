#include "fileexplorer.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FileExplorer w;
    w.show();

    return a.exec();
}
