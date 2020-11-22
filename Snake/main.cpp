#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include "datamap.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
//    DataMap* dataMap = new DataMap(10);
//    for (int i = 0; i < dataMap->getSize(); ++i) {
//        for (int j = 0;j < dataMap->getSize(); ++j) {
//            std::cout<<dataMap->getMap()[i][j];
//        }
//        std::cout<<std::endl;
//    }
    return a.exec();

}
