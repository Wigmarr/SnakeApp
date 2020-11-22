#include "mainwindow.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)
{
    QGridLayout *mainLayout = new QGridLayout;
    QVBoxLayout *controlLayout = new QVBoxLayout;
    dataBaseHandle = new DataBaseHandle;
    executeButton = new QPushButton("Execute");
    startButton = new QPushButton("Start");
    stopButton = new QPushButton("Stop");
    saveButton = new QPushButton("Save");
    mapSizeBox = new QComboBox();
    slider = new QSlider(Qt::Horizontal);
    scene = new QGraphicsScene(0, 0, 600, 600, this);
    view = new QGraphicsView(scene);
    timer = new QTimer(this);

    stopButton->hide();
    slider->setRange(100,1000);
    slider->setValue(500);
    for (int i = 10; i < 21; i++) {
        mapSizeBox->addItem(QString::number(i));
    }

    QObject::connect(executeButton, SIGNAL(clicked()), this, SLOT(execution()));
    QObject::connect(startButton, SIGNAL(clicked()), this, SLOT(startTimer()));
    QObject::connect(stopButton, SIGNAL(clicked()), this, SLOT(stopTimer()));
    QObject::connect(saveButton, SIGNAL(clicked()), this, SLOT(saveData()));
    QObject::connect(slider, SIGNAL(valueChanged(int)), this, SLOT(resetTimer()));

    controlLayout->addWidget(mapSizeBox,Qt::AlignTop);
    controlLayout->addWidget(executeButton);
    controlLayout->addWidget(startButton);
    controlLayout->addWidget(stopButton);
    controlLayout->addWidget(saveButton);
    controlLayout->addStretch();
    mainLayout->addWidget(slider,0,0);
    mainLayout->addWidget(view,1,0);
    mainLayout->addLayout(controlLayout,1,1);
    setLayout(mainLayout);
}

void MainWindow::execution()
{
    srand(time(nullptr));
    emit stopTimer();
    if (dataMap != nullptr)
        delete dataMap;
    if (map != nullptr) {
        delete map;
    }
    startButton->setDisabled(false);
    dataMap = new DataMap(mapSizeBox->currentText().toInt());
    map = new Map(dataMap, scene->width()/dataMap->getSize(),scene->height()/dataMap->getSize());
    QObject::connect(timer, SIGNAL(timeout()), map, SLOT(moveSnakes()));
    QObject::connect(map, SIGNAL(finish()), this, SLOT(finishGame()));
    for (const auto &row : map->getMap()) {
        for (const auto &tile : row) {
            scene->addItem(tile);
        }
    }
    for (const auto &snake : map->getSnakes()) {
        for (const auto &tile : snake->getSnake()) {
            scene->addItem(tile);
            qDebug()<<tile->rect();
        }
    }
}

void MainWindow::startTimer()
{
    stopButton->setDisabled(false);
    timer->setInterval(1100 - slider->value());
    timer->start();
    startButton->hide();
    stopButton->show();
}

void MainWindow::resetTimer()
{
    timer->setInterval(1100 - slider->value());
}

void MainWindow::stopTimer()
{

    timer->stop();
    stopButton->hide();
    startButton->show();
}



void MainWindow::saveData()
{
    QString id = QString::number(dataMap->getId());
    QString sizeOfMap = QString::number(dataMap->getSize());
    QString mapStr;
    for (const auto &row : dataMap->getMap()) {
        for (const auto &tile : row) {
            mapStr.append(QString::number(tile));
            mapStr.append(" ");
        }
    }
    QString numberOfSnakes = QString::number(dataMap->getSnakes().size());
    QString sizeOfSnakes;
    for (const auto &snake : dataMap->getSnakes()) {
            sizeOfSnakes.append(QString::number(snake.size()));
            sizeOfSnakes.append(" ");
    }
    QString x;
    QString y;
    for (const auto &snake : map->getSnakes()) {
        for (const auto &tile : snake->getSnake()) {
            x.append(QString::number(int(tile->x())));
            x.append(" ");
            y.append(QString::number(int(tile->y())));
            y.append(" ");
        }
    }
    dataBaseHandle->addToDataBase(id, sizeOfMap, mapStr, numberOfSnakes, sizeOfSnakes, x, y);
}

void MainWindow::finishGame()
{
    timer->stop();
    startButton->setDisabled(true);
    stopButton->setDisabled(true);
    QMessageBox msgBox;
    msgBox.setText("The End");
    msgBox.exec();
}

MainWindow::~MainWindow()
{

}
