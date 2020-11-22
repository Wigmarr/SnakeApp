#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "datamap.h"
#include "map.h"
#include "databasehandle.h"
#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPushButton>
#include <QComboBox>
#include <QTimer>
#include <QtSql>

class MainWindow : public QWidget
{
    Q_OBJECT
    DataMap*  dataMap = nullptr;
    Map* map = nullptr;
    QGraphicsView* view = nullptr;
    QGraphicsScene* scene = nullptr;
    QSlider *slider = nullptr;
    QPushButton* executeButton = nullptr;
    QPushButton* saveButton = nullptr;
    QPushButton* startButton = nullptr;
    QPushButton* stopButton = nullptr;
    QComboBox* mapSizeBox = nullptr;
    QTimer* timer = nullptr;
    DataBaseHandle* dataBaseHandle = nullptr;
    void updateDataMap();
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void execution();
    void startTimer();
    void resetTimer();
    void stopTimer();
    void saveData();
    void finishGame();
};

#endif // MAINWINDOW_H
